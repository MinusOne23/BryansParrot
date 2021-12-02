#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <iomanip>

#include "Game.h"
#include "Door.h"
#include "Player.h"
#include "Room.h"
#include "Potion.h"
#include "EnemyEncounter.h"
#include "Utils.h"
#include "Interaction.h"
#include "Weapon.h"
#include "DungeonBuilder.h"
#include "Story.h"

using namespace std;

const string VERSION = "1.4.3";

const string START_MESSAGE = "\n\tIn the middle of the night, Bryan the poacher comes home one night to find that his one-of-a-kind\n"
"\tgreen/blue feather parrot was missing, but a note was left behind in his cage. The note instructed\n"
"\tyou to head to a building near the docks that have been abandoned for years. When you got to the\n"
"\tdocks it was eerily quiet and baron of life, but you had to press on to find your prized parrot. \n"
"\tAfter finding and entering the building it became pitch black with only the smell of bird poo to \n"
"\tguide you. You find a closed door and begin to open it only for the floor to disappear beneath you.\n"
"\tAs you fall into a lower chamber you see a blue and green feather before you blackout from the impact.\n"
"\tYou wake up in a jail cell, with a faint squawk of your parrot in the distance. You don’t recognize \n"
"\tthe room you are trapped in and all you see is a jail cell door with a chicken outside of it clad in\n"
"\tarmor and a dead body beside yours with a key in his hand. What will Bryan do? \n\n\n";

/// STARTS THE GAME:
/// Game will continue untill:
///		-Player is Dead
///		or
///		-Player enters winning room
/// 
void Game::start()
{
	cout << "Bryan's Parrot v" << VERSION << endl << endl;
	string inputGameStart = "0";
	while (inputGameStart != "1") {
		//Main Menu
		cout << "\t===================================\n";
		cout << "\t - Start Game Press: 1" << "\n";
		cout << "\t - Instructions Press: 2" << "\n";
		cout << "\t - To Quit Press: 0" << "\n";
		cout << "\t===================================\n";

		inputGameStart = Utils::inputValidator();

		if (inputGameStart == "2") {
			//Help Instructions
			cout << "\tHey there and welcome to our game called Bryan's Parrot! We're very thankful that you can\n"
				"\tspend some time trying our game out and letting us know how it went. Our Game is a Text \n"
				"\tbased RPG run through console and built using C++. This game uses commands in the format of \n"
				"\t(Action) space (Object), an example would be (take) space (drink) if you wanted to pick \n"
				"\tup a drink that was seen in the room. Also, (i) is inventory, (c) is for character stats, and if\n"
				"\tyou forget a word used you can always press (h) for a refresher.I think I've given you enough \n"
				"\tinformation to start the game, but be on the lookout for more action words and also let us know if \n"
				"\tthere are words that you believe would be better implemented in the game. Thank you and we hope you \n"
				"\tenjoy our game! \n\n";
		}
		else if (inputGameStart == "0") {
			exit(0);
		}


	}

	system("CLS");

	//Start of Game Dialogue
	cout << START_MESSAGE;

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

void Game::initializeGameTest() {
	initializeGame();
}

void Game::initializeGame()
{
	srand(time(NULL));

	Weapon playerFists("Fists", 0.2f, 1.5f);
	playerFists.addAttackMove(AttackMove("Punch", 10, 15, 1, 0.9f));

	//				health	speed	baseStamina	dodgeChance	baseWeapon
	player = Player(100,	10,		1,			0.4f,		playerFists);
	player.refreshStamina();

	miniMap = MiniMap();

	gameState = GameState::PLAY;

	allRooms = DungeonBuilder::buildDungeon();

	//Current Room player is in. Will change when player enters new room
	currentRoom = &allRooms.at("Jail Cell");
	miniMap.discoverRoom(currentRoom);
	currentRoom->setHasPlayer(true);

	//When player enters winRoom, game is over
	winRoom = &allRooms.at("Emergence");
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
		system("CLS");

		cout << START_MESSAGE;
		currentRoom->displayContents();
	}
}

/// Opens door in room specified by direction
///Input: DOOR DIRECTOM
///Updates: NEW ROOM
void Game::openDoor(Room::Direction index)
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

	Room* nextRoom = currentRoom->getRoom(index);

	enterNewRoom(nextRoom);
}

/// Door Index = Door Direction
///Input: user input Door name
/// Returns: Specific door direction enum
Room::Direction Game::getDoorIndex(string doorName)
{
	if (Utils::equalsCI(doorName, "north door"))
		return Room::Direction::NORTH;
	else if (Utils::equalsCI(doorName, "south door"))
		return Room::Direction::SOUTH;
	else if (Utils::equalsCI(doorName, "east door"))
		return Room::Direction::EAST;
	else if (Utils::equalsCI(doorName, "west door"))
		return Room::Direction::WEST;

	return Room::Direction::NONE;
}

Room* Game::findRoom(string roomName)
{
	for (map<string, Room>::iterator it = allRooms.begin(); it != allRooms.end(); it++)
	{
		if (Utils::equalsCI(it->first, roomName))
			return &it->second;
	}

	return nullptr;
}

void Game::enterNewRoom(Room* nextRoom)
{
	miniMap.discoverRoom(nextRoom);

	currentRoom->setHasPlayer(false);
	nextRoom->setHasPlayer(true);

	while (nextRoom->encounterCount() > 0)
	{
		EnemyEncounter& encounter = nextRoom->currentEncounter();
		encounter.setLastRoom(currentRoom);

		EnemyEncounter::EncounterResult encResult = encounter.startEncounter(player, miniMap);

		if (!encResult.encounterComplete)
		{
			if (encounter.getCurrentState() == EnemyEncounter::EncounterState::RETREAT)
			{
				if (encResult.tpRoomName != "")
				{
					nextRoom->setHasPlayer(false);

					nextRoom = findRoom(encResult.tpRoomName);
					nextRoom->setHasPlayer(true);
				}
				else
				{
					nextRoom->setHasPlayer(false);
					currentRoom->setHasPlayer(true);

					currentRoom->displayContents();
					return;
				}
			}
			else if (!player.isDead())
			{
				nextRoom->setHasPlayer(false);
				currentRoom->setHasPlayer(true);

				currentRoom->displayContents();
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			nextRoom->completeEncounter();
		}
	}

	currentRoom = nextRoom;

	if (currentRoom != winRoom)
		currentRoom->displayContents();
}

/// Game Loop: Takes in user input ant turns input into actions
/// Calls different functions for Interaction enums
///		QUIT -- exits program
///		INVENTORY -- displays uers inventory
///		EQUIP -- equips the piece of equipment from the player's inventory
///		CHARACTER -- displays the player's stats
///		TAKE -- adds key from room and adds to inventory
///		USE -- uses the item with its intended purpose
///		DRINK -- drinks the specified item in player inventory
///		OPEN -- opens current rooms door and moves to next room
///		DROP -- drops item into current room
///		UNLOCK -- unlocks any locked door
///		LOOK -- displays what is in the room
///		HELP -- displays all commands the player has already discovered
void Game::gameInteract()
{
	Interaction::InteractionResult inputResult = Interaction::universalInput(player, miniMap);

	if (!Interaction::canUseInRoom(inputResult.actionType))
	{
		cout << "Sorry you can't do that right now" << endl;
		return;
	}

	//Actions
	switch (inputResult.actionType)
	{
	case Interaction::ActionType::TAKE:
	{
		shared_ptr<Item> item = currentRoom->takeItem(inputResult.target);

		if (item == nullptr)
		{
			cout << "This item is not in the room." << endl;
			inputResult.succeeded = false;
		}
		else
		{
			player.takeItem(item);
		}

		break;
	}
	case Interaction::ActionType::OPEN:
	{
		Room::Direction index = getDoorIndex(inputResult.target);

		if (index == Room::Direction::NONE)
		{
			cout << "That is not a valid object to open." << endl;
			inputResult.succeeded = false;
		}
		else
			openDoor(index);
		break;
	}
	case Interaction::ActionType::DROP:
	{
		shared_ptr<Item>item = player.dropItem(inputResult.target);
		if (item != nullptr)
		{
			currentRoom->addItem(item);
			inputResult.succeeded = true;
		}
		else
		{
			inputResult.succeeded = false;
		}
		break;
	}
	case Interaction::ActionType::UNLOCK:
	{
		Room::Direction index = getDoorIndex(inputResult.target);

		if (index == Room::Direction::NONE)
		{
			cout << "That is not a valid object to unlock." << endl;
			inputResult.succeeded = false;
		}
		else
			currentRoom->unlockDoor(index, player);

		break;
	}
	case Interaction::ActionType::LOOK:
	{
		currentRoom->displayContents();
		break;
	}
	case Interaction::ActionType::TP:
	{
		if (inputResult.succeeded)
		{
			enterNewRoom(findRoom(inputResult.tpRoomName));
		}
	}
	}

	cout << endl;
};
