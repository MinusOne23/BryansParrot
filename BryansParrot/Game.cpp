#include <string>
#include <iostream>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
using namespace std;

//Helper Enums used for room ineraction

enum class Interactions
{
	QUIT = 0,
	INVENTORY = 1,
	TAKE_KEY = 2,
	OPEN_DOOR = 3,
	UNLOCK_DOOR = 4,
	KILL_GOBLIN = 5,
	MOVE_BACK = 6,
	LOOK = 7,
	ERROR = 99
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
	if (inputStr == "q") { return Interaction::QUIT; }
	else if (inputStr == "i") { return Interaction::INVENTORY; }
	else if (inputStr == "take key") { return Interaction::TAKE_KEY; }
	else if (inputStr == "open door") { return Interaction::OPEN_DOOR; }
	else if (inputStr == "move back") { return Interaction::MOVE_BACK; }
	else if (inputStr == "kill goblin") { return Interaction::KILL_GOBLIN; }
	else if (inputStr == "unlock door") { return Interaction::UNLOCK_DOOR; }
	else if (inputStr == "look") { return Interaction::LOOK; }
	else { return Interaction::ERROR; }
}
void Game::gameInteract()
{
	Interaction input;
	char userinput[256];

	cin.getline(userinput, 256);
	string inputStr(userinput);

	input = enumInputChecker(inputStr);
	Room* newRoom;
	Key* key;
	vector<Item*> drops;

	//Interact
	switch (input)
	{
	case Interaction::QUIT:
		exit(0);
	case Interaction::INVENTORY:
		player.displayInventory();
		break;
	case Interaction::TAKE_KEY:
		key = currentRoom->takeKey();

		if (key != nullptr)
		{
			player.takeItem(key);
		}

		break;
	case Interaction::OPEN_DOOR:
		newRoom = currentRoom->openDoor(RoomDoorIndex::NORTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		break;
	case Interaction::MOVE_BACK:
		newRoom = currentRoom->openDoor(RoomDoorIndex::SOUTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		break;
	case Interaction::UNLOCK_DOOR:
		currentRoom->unlockDoor(RoomDoorIndex::NORTH_DOOR, &player);
		break;
	case Interaction::KILL_GOBLIN:

		drops = currentRoom->killGoblin();
		currentRoom->addItems(drops);

		break;
	case Interaction::LOOK:
		currentRoom->displayContents();
		break;
	case Interaction::ERROR:
	default:
		cout << "Sorry, that input is not recognized." << endl;
		break;
	}

	cout << endl;
};
