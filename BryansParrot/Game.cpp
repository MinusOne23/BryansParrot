#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <memory>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
#include "Utils.h"
#include "Potion.h"

using namespace std;

const string VERSION = "1.2.1";

const int Game::MAX_ACTION_WORDS = 2;

const map<string, Game::Interaction> Game::actions = {
	{"q", Interaction::QUIT},
	{"i", Interaction::INVENTORY},
	{"inventory", Interaction::INVENTORY},
	{"take", Interaction::TAKE},
	{"grab", Interaction::TAKE},
	{"use", Interaction::USE},
	{"open", Interaction::OPEN},
	{"unlock", Interaction::UNLOCK},
	{"l", Interaction::LOOK},
	{"look", Interaction::LOOK},
	{"attack", Interaction::ATTACK},
	{"c", Interaction::CHARACTER},
	{"character", Interaction::CHARACTER}
};

void Game::start()
{
	cout << "Bryan's Parrot v" << VERSION << endl << endl;

	initializeGame();

	currentRoom->displayContents();

	while (gameState == GameState::PLAY)
	{
		gameInteract();

		if (player.isDead())
			playerDied();
		else if (currentRoom == winRoom)
			playerWin();
	}

}

void Game::initializeGame()
{
	srand(time(NULL));

	player = Player();
	gameState = GameState::PLAY;

	allRooms = {
		Room(),
		Room(),
		Room()
	};

	//Create room object that will set it to array of all all rooms
	Room& firstRoom = allRooms[0];
	Room& secondRoom = allRooms[1];
	Room& thirdRoom = allRooms[2];

	//create new doors that will be added to doors vector
	shared_ptr<Door> door1(new Door(secondRoom));
	shared_ptr<Door> door2(new Door(thirdRoom, 2));
	shared_ptr<Door> door3(new Door(firstRoom));

	//create new items that will be added to Inventory
	shared_ptr<Item> smallPotion(new Potion(50));

	//Create new Enemy that will be added to a room
	Enemy goblin("Goblin", 100, 5, 10, 0.1f);

	//Add drops to specific Enemy Object 
	goblin.addDrop(shared_ptr<Item>(new Key(door2)));

	//Room 1: Initialization
	firstRoom.setDoor(Room::DoorIndex::NORTH_DOOR, door1);
	firstRoom.addItem(shared_ptr<Item>(new Key(door2)));
	firstRoom.addItem(shared_ptr<Item>(new Potion(smallPotion)));

	//Room 2: Initialization
	secondRoom.setDoor(Room::DoorIndex::NORTH_DOOR, door2);
	secondRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, door3);
	secondRoom.addEnemy(goblin);


	//Current Room player is in. Will change when player enters new room
	currentRoom = &firstRoom;

	//When player enters winRoom, game is over
	winRoom = &thirdRoom;
}


/// Converts the player user input to the enum action + object the action is taking on
/// 
/// Inputs: User input string 
/// returns: specific Actions Enum
/// Returns: Object name

Game::InputCheckerResult Game::enumInputChecker(string inputStr)
{
	InputCheckerResult result;
	vector<string> tokens = Utils::tokenize(inputStr);

	for (int i = 1; i < tokens.size() + 1 && i <= MAX_ACTION_WORDS; i++)
	{
		string actionStr = tokens[0];

		for (int j = 1; j < i; j++)
		{
			actionStr += " " + tokens[j];
		}

		if (actions.find(actionStr) != actions.end())
		{
			result.interaction = actions.at(actionStr);

			if (i < tokens.size())
			{
				result.objectName = tokens[i];
				for (int j = i + 1; j < tokens.size(); j++)
				{
					result.objectName += " " + tokens[j];
				}
			}

			return result;
		}
	}

	result.interaction = Interaction::ERROR;
	return result;
}

/// PlayerDied(): Health reaches 0
/// PlayerWin(): PLayer enters winRoom
/// PromptReplay(): game has ended and asks to play again
void Game::playerDied()
{
	gameState = GameState::DIED;
	cout << "Oh no! It appears you have died!" << endl;

	promptReplay();
}

void Game::playerWin()
{
	gameState = GameState::WIN;
	cout << "Congratulations you have navigated through all the rooms and beat the game!" << endl;

	promptReplay();
}

void Game::promptReplay()
{
	cout << "Would you like to play again?" << endl;

	string in = Utils::inputValidator();

	while (in != "yes" && in != "y" && in != "no" && in != "n")
	{
		cout << "Please enter yes or no" << endl;
		in = Utils::inputValidator();
	}

	if (in == "yes" || in == "y")
	{
		gameState = GameState::PLAY;
		initializeGame();
		cout << endl;
		currentRoom->displayContents();
	}
}


/// Opens door in room specified by direction
void Game::openDoor(Room::DoorIndex index)
{
	shared_ptr<Door> door = currentRoom->getDoor(index);

	if (door == nullptr)
		cout << "There is no door in this direction." << endl;
	else
	{
		if (door->isLocked())
			cout << "This door is locked and can not be opend yet." << endl;
		else
		{
			cout << "You opened the door and went to the next room" << endl;
			currentRoom = &door->getNextRoom();

			currentRoom->displayContents();
		}
	}
}

/// Door Index = Door Direction
///
Room::DoorIndex Game::getDoorIndex(string doorName)
{
	if (Utils::equalsCI(doorName, "north door"))
		return Room::DoorIndex::NORTH_DOOR;
	else if (Utils::equalsCI(doorName, "south door"))
		return Room::DoorIndex::SOUTH_DOOR;
	else if (Utils::equalsCI(doorName, "east door"))
		return Room::DoorIndex::EAST_DOOR;
	else if (Utils::equalsCI(doorName, "west door"))
		return Room::DoorIndex::WEST_DOOR;

	return Room::DoorIndex::NONE;
}

//user input turns into action
void Game::gameInteract()
{
	Interaction input;
	string inputStr = Utils::inputValidator();
	InputCheckerResult inputResult = enumInputChecker(inputStr);

	bool shouldUpdate = true;
	/// Calls different functions for Interaction enums
	/// QUIT -- exits program
	/// INVENTORY -- displays uers inventory
	/// TAKE_KEY -- adds key from room and adds to inventory
	/// OPEN_DOOR -- opens current rooms door and moves to next room
	/// MOVE_BACK -- moves to previous room
	/// UNLOCK_DOOR -- unlocks any locked door
	/// KILL_GOBLIN -- kills enemy in room and drops key for player to pick up
	/// LOOK -- displays what is in the room
	switch (inputResult.interaction)
	{
	case Interaction::QUIT: 
	{
		exit(0);
	}
	case Interaction::INVENTORY:
	{
		player.displayInventory();
		shouldUpdate = false;
		break;
	}
	case Interaction::CHARACTER:
	{
		player.displayStats();
		shouldUpdate = false;
		break;
	}
	case Interaction::TAKE:
	{
		shared_ptr<Item> item = currentRoom->takeItem(inputResult.objectName);

		if (item == nullptr)
		{
			cout << "This item is not in the room." << endl;
		}
		else 
		{
			player.takeItem(item);
		}

		shouldUpdate = false;

		break;
	}
	case Interaction::OPEN:
	{
		Room::DoorIndex index = getDoorIndex(inputResult.objectName);

		if (index == Room::DoorIndex::NONE)
			cout << "That is not a valid object to open." << endl;
		else
			openDoor(index);

		shouldUpdate = false;
		break;
	}
	case Interaction::UNLOCK:
	{
		Room::DoorIndex index = getDoorIndex(inputResult.objectName);

		if (index == Room::DoorIndex::NONE)
			cout << "That is not a valid object to unlock." << endl;
		else
			currentRoom->unlockDoor(index, player);

		break;
	}
	case Interaction::ATTACK:
	{
		Character::DamageResult damageResult = player.getDamage();

		if (damageResult.critical)
			cout << "Critical hit!" << endl;

		bool foundEnemy = currentRoom->attack(inputResult.objectName, damageResult.damage);

		if (!foundEnemy)
			shouldUpdate = false;

		break;
	}
	case Interaction::LOOK:
	{
		currentRoom->displayContents();
		shouldUpdate = false;
		break;
	}
	case Interaction::ERROR:
	default:
	{
		cout << "Sorry, that input is not recognized." << endl;
		shouldUpdate = false;
		break;
	}
	}

	if (shouldUpdate)
		currentRoom->updateTurn(player);


	cout << endl;
};
