#include <iostream>
#include <list>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
using namespace std;

const map<string, Game::Interaction> Game::actions = {
	{"q", Interaction::QUIT},
	{"i", Interaction::INVENTORY},
	{"inventory", Interaction::INVENTORY},
	{"take key", Interaction::TAKE_KEY},
	{"grab key", Interaction::TAKE_KEY},
	{"open door", Interaction::OPEN_DOOR},
	{"unlock door", Interaction::UNLOCK_DOOR},
	{"kill goblin", Interaction::KILL_GOBLIN},
	{"move back", Interaction::MOVE_BACK},
	{"l", Interaction::LOOK},
	{"look", Interaction::LOOK},
	{"h", Interaction::HELP}
};


void Game::start()
{
	Room firstRoom, secondRoom, thirdRoom;
	Door door(&secondRoom), door2(&thirdRoom, 2), door3(&firstRoom);
	Key key(&door2), key2(&door2);
	Enemy enemy("goblin");
	enemy.addDrop(&key2);

	//Room 1: Initialization
	firstRoom.addItem(&key);
	firstRoom.setDoor(RoomDoorIndex::NORTH_DOOR, &door);

	//Room 2: Initialization
	secondRoom.setDoor(RoomDoorIndex::NORTH_DOOR, &door2);
	secondRoom.setDoor(RoomDoorIndex::SOUTH_DOOR, &door3);
	secondRoom.addEnemy(&enemy);

	currentRoom = &firstRoom;

	currentRoom->displayContents();

	bool gameWin = false;
	while (!gameWin)
	{
		gameInteract();

		if (currentRoom == &thirdRoom)
			gameWin = true;
	}

	cout << "Congratulations you have navigated through all the rooms and beat the game!" << endl;
}

Game::Interaction Game::enumInputChecker(string inputStr)
{
	if (actions.find(inputStr) != actions.end())
	{
		return actions.at(inputStr);
	}

	return Interaction::ERROR;
}

void Game::addHelper(string input)
{
	if (find(helper.begin(), helper.end(), input) == helper.end())
	{
		helper.push_back(input);
	}
}

void Game::helperDisplay()
{
	cout << "\t===========================================\n";
	cout << "\t\t\tKnownCommands\n";
	cout << "\t-------------------------------------------\n";
	for (unsigned int i = 0; i < helper.size(); i++)
	{
		cout << "\t- " << helper[i] << endl;
	}
	cout << "\t===========================================\n";
}
//user input turns into action
void Game::gameInteract()
{
	//Obj and Varable creation
	Interaction input;
	Room* newRoom;
	Key* key;
	vector<Item*> drops;
	char userinput[256];

	// user actioni input
	cin.getline(userinput, 256);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string inputStr(userinput);

	//Calls enumInputChecker and returns correct enum
	input = enumInputChecker(inputStr);

	/// Calls different functions for Interaction enums
	/// QUIT -- exits program
	/// INVENTORY -- displays uers inventory
	/// TAKE_KEY -- adds key from room and adds to inventory
	/// OPEN_DOOR -- opens current rooms door and moves to next room
	/// MOVE_BACK -- moves to previous room
	/// UNLOCK_DOOR -- unlocks any locked door
	/// KILL_GOBLIN -- kills enemy in room and drops key for player to pick up
	/// LOOK -- displays what is in the room
	switch (input)
	{
	case Interaction::QUIT: 
		exit(0);
	case Interaction::INVENTORY:
		addHelper("i: Displays Inventory");
		addHelper("Inventory: Displays Inventory");
		player.displayInventory();
		break;
	case Interaction::TAKE_KEY:
		addHelper("take: Take an Item ");
		addHelper("grab: Take an Item ");
		key = currentRoom->takeKey();

		if (key != nullptr)
		{
			player.takeItem(key);
		}

		break;
	case Interaction::OPEN_DOOR:
		addHelper("open: Opens unlocked door");
		newRoom = currentRoom->openDoor(RoomDoorIndex::NORTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		break;
	case Interaction::MOVE_BACK:
		addHelper("move back: move to previous room");
		newRoom = currentRoom->openDoor(RoomDoorIndex::SOUTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		break;
	case Interaction::UNLOCK_DOOR:
		addHelper("unlock: unlocks locked door");
		currentRoom->unlockDoor(RoomDoorIndex::NORTH_DOOR, &player);
		break;
	case Interaction::KILL_GOBLIN:
		addHelper("kill: kills enemy");
		drops = currentRoom->killGoblin();
		currentRoom->addItems(drops);
		break;
	case Interaction::LOOK:
		addHelper("l: displays room");
		addHelper("look: displays room");
		currentRoom->displayContents();
		break;
	case Interaction::HELP:
		helperDisplay();
		break;
	case Interaction::ERROR:
	default:
		cout << "Sorry, that input is not recognized." << endl;
		break;
	}

	cout << endl;
};
