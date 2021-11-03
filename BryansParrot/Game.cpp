#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <memory>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
#include "Potion.h"
#include "EnemyEncounter.h"
#include "Utils.h"
#include "Interaction.h"

using namespace std;

const string VERSION = "1.3.0";
const int Game::MAX_ACTION_WORDS = 1;

/// STARTS THE GAME:
/// Game will continue untill:
///		-Player is Dead
///		or
///		-Player enters winning room
/// 
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

/// HOW TO CREATE NEW ROOM:
///		-Add Room() to the allRooms array
///		- create the new room object linking it to the index of the room you added in addRooms
///			Room& [ROOMNAME] = allRooms[INDEX]
/// 
///	ADDING A DOOR TO A ROOM:
///		-shared_ptr<Door>DOOR_NAME(new Door(NEXT ROOM, LOCKS AMOUNT)); 
///			DOOR_NAME: firstNorthDoor
///			NEXT_ROOM: secondRoom
///			LOCKS: INT <-If no locks then only have Next Room in ( )
/// 
///		-ROOM_OBJ.setDoor(Room::DoorIndex::[CARDNAL_DIRECTION_DOOR, DOOR_NAME_FORM_ABOVE);
/// 
/// ADDING ITEMS TO A ROOM:
///		-create object for item
///			Potion sPotion
///		-add item to specific room
///			ROOM_OBJ.addItem(make_shared<ITEM_CLASS>(OBJ_NAME))
///				- ITEM_CLASS: Potion
///				- OBJ_NAME: sPotion
/// 
/// ADDING AN ENEMY TO A ROOM:
///		-create enemy object
///			Enemy ENEMY_NAME("DETAILED_NAME", INT MAX_HEALTH, INT MIN_DAMAGE, INT MAX_DAMAGE, FLOAT CRITICAL_CHANCE)
///				EX: Enemy goblin("Goblin", 100, 5, 10, 0.1f);
///		-add enemy to specific room
///			ROOM_NAME.addEnemy(ENEMY_OBJ);
/// 
/// ** WHEN ADDING ROOM, ALWAYS UPDATE THE WINROOM OBJ IF NESSESARY **
void Game::initializeGame()
{
	srand(time(NULL));

	Weapon playerFists("Fists", { 10, 20 }, 0.2f, { 20, 30 });
	Weapon goblinFists("Goblin Fists", { 5, 10 }, 0.1f, { 10, 20 });
	Weapon ironSword("Sword", { 15, 30 }, 0.25f, { 35, 45 });

	player = Player(100, playerFists);
	gameState = GameState::PLAY;

	allRooms = {
		Room(),
		Room(),
		Room(),
		Room()
	};

	//Create room object that will set it to array of all all rooms
	Room& firstRoom = allRooms[0];
	Room& secondRoom = allRooms[1];
	Room& thirdRoom = allRooms[2];
	Room& forthRoom = allRooms[3];

	//create new doors that will be added to doors vector
	shared_ptr<Door> firstNorthDoor(new Door(secondRoom));
	shared_ptr<Door> secondNorthDoor(new Door(thirdRoom, 2));
	shared_ptr<Door> secondSouthDoor(new Door(firstRoom));
	shared_ptr<Door> thirdNorthDoor(new Door(forthRoom));
	shared_ptr<Door> thirdSouthDoor(new Door(secondRoom));

	//create new items that will be added to Inventory
	Potion sPotion("Small Potion", 25);
	Potion mPotion("Medium Potion", 50);
	Potion lPotion("Large Potion", 100);

	EnemyEncounter secondRoomEncounter;
	secondRoomEncounter.addEnemy(Enemy("Goblin", 100, goblinFists));

	//Add drops to specific Enemy Object 
	secondRoomEncounter.addDrop(shared_ptr<Item>(new Key(secondNorthDoor)));

	//Room 1: Initialization
	firstRoom.setDoor(Room::DoorIndex::NORTH_DOOR, firstNorthDoor);
	firstRoom.addItem(shared_ptr<Item>(new Key(secondNorthDoor)));
	firstRoom.addItem(make_shared<Weapon>(ironSword));

	//Room 2: Initialization
	secondRoom.setDoor(Room::DoorIndex::NORTH_DOOR, secondNorthDoor);
	secondRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, secondSouthDoor);
	secondRoom.addEnemyEncounter(secondRoomEncounter);

	//Room3: Initialization
	thirdRoom.setDoor(Room::DoorIndex::NORTH_DOOR, thirdNorthDoor);
	thirdRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, thirdSouthDoor);
	thirdRoom.addItem(make_shared<Potion>(sPotion)); // make_shared: makes smart prt with contents of sPotion

	//Current Room player is in. Will change when player enters new room
	currentRoom = &firstRoom;

	//When player enters winRoom, game is over
	winRoom = &forthRoom;
}

/// PlayerDied(): Health reaches 0
void Game::playerDied()
{
	gameState = GameState::DIED;
	cout << "Oh no! It appears you have died!" << endl;

	promptReplay();
}

/// PlayerWin(): PLayer enters winRoom
void Game::playerWin()
{
	gameState = GameState::WIN;
	cout << "Congratulations you have navigated through all the rooms and beat the game!" << endl;

	promptReplay();
}

/// PromptReplay(): game has ended and asks to play again
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

void Game::helperDisplay()
{
	cout << "\t===========================================\n";
	cout << "\t\t\tKnownCommands\n";
	cout << "\t-------------------------------------------\n";
	for (string act : actionsUsed)
	{
		string helpStr = Interaction::getHelpText(act);

		if(helpStr != "")
			cout << "\t- " << act << ": " << helpStr << endl;
	}
	cout << "\t===========================================\n";
}

/// Opens door in room specified by direction
///Input: DOOR DIRECTOM
///Updates: NEW ROOM
void Game::openDoor(Room::DoorIndex index)
{
	shared_ptr<Door> door = currentRoom->getDoor(index);

	if (door == nullptr)
	{
		cout << "There is no door in this direction." << endl;
		return;
	}

	if (door->isLocked())
	{
		cout << "This door is locked and can not be opend yet." << endl;
		return;
	}

	Room* nextRoom = &door->getNextRoom();

	if (nextRoom->encounterCount() == 0)
	{
		currentRoom = nextRoom;
		currentRoom->displayContents();
		return;
	}

	EnemyEncounter& encounter = nextRoom->nextEncounter();

	bool startEncounter = encounter.startEncounter();
	
	if (!startEncounter)
	{
		cout << "You have retreated back to the previous room" << endl;
	}
	else
	{
		nextRoom->completeEncounter();
		currentRoom = nextRoom;

		currentRoom->displayContents();
	}
}

/// Door Index = Door Direction
///Input: user input Door name
/// Returns: Specific door direction enum
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

/// Game Loop: Takes in user input ant turns input into actions
/// Calls different functions for Interaction enums
///		QUIT -- exits program
///		INVENTORY -- displays uers inventory
///		EQUIP -- equips the piece of equipment from the player's inventory
///		CHARACTER -- displays the player's stats
///		TAKE -- adds key from room and adds to inventory
///		USE -- uses the item with its intended purpose
///		OPEN -- opens current rooms door and moves to next room
///		DROP -- drops item into current room
///		UNLOCK -- unlocks any locked door
///		ATTACK -- kills enemy in room and drops key for player to pick up
///		LOOK -- displays what is in the room
///		HELP -- displays all commands the player has already discovered
void Game::gameInteract()
{
	string inputStr = Utils::inputValidator();
	Interaction::InteractionResult inputResult = Interaction::parseInput(inputStr);

	switch (inputResult.actionType)
	{
	case Interaction::ActionType::QUIT:
	{
		exit(0);
	}
	case Interaction::ActionType::INVENTORY:
	{
		player.displayInventory();
		break;
	}
	case Interaction::ActionType::EQUIP:
	{
		player.equipWeapon(inputResult.objectName);
		break;
	}
	case Interaction::ActionType::CHARACTER:
	{
		player.displayStats();
		break;
	}
	case Interaction::ActionType::TAKE:
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

		break;
	}
	case Interaction::ActionType::USE:
	{
		player.useItem(inputResult.objectName);
		break;
	}
	case Interaction::ActionType::OPEN:
	{
		Room::DoorIndex index = getDoorIndex(inputResult.objectName);

		if (index == Room::DoorIndex::NONE)
			cout << "That is not a valid object to open." << endl;
		else
			openDoor(index);
		break;
	}
	case Interaction::ActionType::DROP:
	{
		shared_ptr<Item>item = player.dropItem(inputResult.objectName);
		if (item != nullptr)
		{
			currentRoom->addItem(item);
		}
		else
		{
			cout << "Invalid item to drop" << endl;
		}
		break;
	}
	case Interaction::ActionType::UNLOCK:
	{
		Room::DoorIndex index = getDoorIndex(inputResult.objectName);

		if (index == Room::DoorIndex::NONE)
			cout << "That is not a valid object to unlock." << endl;
		else
			currentRoom->unlockDoor(index, player);

		break;
	}
	case Interaction::ActionType::LOOK:
	{
		currentRoom->displayContents();
		break;
	}
	case Interaction::ActionType::HELP:
	{
		helperDisplay();
		break;
	}
	case Interaction::ActionType::ERROR:
	default:
	{
		cout << "Sorry, that input is not recognized." << endl;
		break;
	}
	}


	if (inputResult.actionType != Interaction::ActionType::ERROR)
		actionsUsed.insert(inputResult.actionStr);

	cout << endl;
};
