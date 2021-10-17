#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
using namespace std;

const int Game::MAX_ACTION_WORDS = 2;

const map<string, Game::Interaction> Game::actions = {
	{"q", Interaction::QUIT},
	{"i", Interaction::INVENTORY},
	{"inventory", Interaction::INVENTORY},
	{"take key", Interaction::TAKE_KEY},
	{"grab key", Interaction::TAKE_KEY},
	{"open door", Interaction::OPEN_DOOR},
	{"unlock door", Interaction::UNLOCK_DOOR},
	{"move back", Interaction::MOVE_BACK},
	{"l", Interaction::LOOK},
	{"look", Interaction::LOOK},
	{"attack", Interaction::ATTACK},
	{"c", Interaction::CHARACTER},
	{"character", Interaction::CHARACTER}
};


vector<string> Game::tokenize(string str)
{
	stringstream stream(str);

	vector<string> tokens;
	string tok;

	while (stream >> tok)
	{
		tokens.push_back(tok);
	}

	return tokens;
}

Game::Game()
{
	currentRoom = nullptr;
	player = Player();

	srand(time(NULL));
}

void Game::start()
{
	Room firstRoom, secondRoom, thirdRoom;
	Door door(&secondRoom), door2(&thirdRoom, 2), door3(&firstRoom);
	Key key(&door2), key2(&door2);
	Enemy enemy("goblin", 100, 5, 10, 0.1f);
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

Game::InputCheckerResult Game::enumInputChecker(string inputStr)
{
	InputCheckerResult result;
	vector<string> tokens = tokenize(inputStr);

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
		exit(0);
	case Interaction::INVENTORY:
		player.displayInventory();
		shouldUpdate = false;
		break;
	case Interaction::CHARACTER:
		player.displayStats();
		shouldUpdate = false;
		break;
	case Interaction::TAKE_KEY:
		key = currentRoom->takeKey();

		if (key != nullptr)
		{
			player.takeItem(key);
		}

		shouldUpdate = false;

		break;
	case Interaction::OPEN_DOOR:
		newRoom = currentRoom->openDoor(RoomDoorIndex::NORTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		shouldUpdate = false;

		break;
	case Interaction::MOVE_BACK:
		newRoom = currentRoom->openDoor(RoomDoorIndex::SOUTH_DOOR);
		if (newRoom != nullptr)
		{
			currentRoom = newRoom;
			currentRoom->displayContents();
		}

		shouldUpdate = false;

		break;
	case Interaction::UNLOCK_DOOR:
		currentRoom->unlockDoor(RoomDoorIndex::NORTH_DOOR, &player);
		break;
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
		currentRoom->displayContents();
		shouldUpdate = false;
		break;
	case Interaction::ERROR:
	default:
		cout << "Sorry, that input is not recognized." << endl;
		shouldUpdate = false;
		break;
	}

	if(shouldUpdate)
		currentRoom->updateTurn(&player);

	cout << endl;
};
