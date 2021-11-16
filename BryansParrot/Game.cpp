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

using namespace std;

const string VERSION = "1.3.7";

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

void Game::initializeGameTest() {
	initializeGame();
}

void Game::initializeGame()
{
	srand(time(NULL));

	Weapon playerFists("Fists", 0.2f, 1.5f);
	playerFists.addAttackMove(AttackMove("Punch", 10, 15, 1, 0.9f));

	//					health	speed	baseStamina	dodgeChance	baseWeapon
	player = Player(	100,	10,		1,			0.4f,		playerFists);
	player.refreshStamina();

	gameState = GameState::PLAY;

	allRooms = DungeonBuilder::buildDungeon();

	//Current Room player is in. Will change when player enters new room
	currentRoom = &allRooms.at("first_room");

	//When player enters winRoom, game is over
	winRoom = &allRooms.at("fifthRoom");
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

void Game::enterNewRoom(Room* nextRoom)
{

	while (nextRoom->encounterCount() > 0)
	{
		EnemyEncounter& encounter = nextRoom->currentEncounter();
		encounter.setLastRoom(currentRoom);

		EnemyEncounter::EncounterResult encResult = encounter.startEncounter(player);

		if (!encResult.encounterComplete)
		{
			if (encounter.getCurrentState() == EnemyEncounter::EncounterState::RETREAT)
			{
				if (encResult.tpRoomName != "")
				{
					nextRoom = &allRooms.at(encResult.tpRoomName);
				}
				else
				{
					currentRoom->displayContents();
					return;
				}
			}
			else if (!player.isDead())
			{
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
	Interaction::InteractionResult inputResult = Interaction::universalInput(player);

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
		}
		else
		{
			cout << "Invalid item to drop" << endl;
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
			enterNewRoom(&allRooms.at(inputResult.tpRoomName));
		}
	}
	}

	cout << endl;
};
