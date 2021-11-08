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

const string VERSION = "1.3.4";

const map<string, int> Game::roomNameToIndex = {
	{"first_room",0},
	{"second_room",1},
	{"third_room",2},
	{"forth_room",3}
};

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
	Weapon playerFists("Fists", { 10, 20, 0.9f }, { 15, 25, 0.6f }, 0.2f, 1.5f);
	player = Player(100, playerFists);
	gameState = GameState::PLAY;

	allRooms = DungeonBuilder::buildDungeon();

	//Current Room player is in. Will change when player enters new room
	currentRoom = &allRooms[0];

	//When player enters winRoom, game is over
	winRoom = &allRooms[allRooms.size() - 1];
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
	enterNewRoom(nextRoom);
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


void Game::encounterInteract(Interaction::InteractionResult& inputResult)
{
	EnemyEncounter& encounter = currentRoom->currentEncounter();
	if (isDevMode == true)
	{
		switch (inputResult.devActionType)
		{
		case Interaction::DevActionType::KILL:
		{
			inputResult.succeeded = encounter.killEnemy(inputResult.objectName);
			break;
		}
		}
	}
	switch (inputResult.actionType)
	{
	case Interaction::ActionType::ATTACK:
	{
		if (!encounter.enemyExists(inputResult.target))
		{
			cout << "That enemy does not exist" << endl;
			inputResult.succeeded = false;
			break;
		}

		Weapon activeWeapon = player.getActiveWeapon();
		Weapon::Damage lightDmg = activeWeapon.getLightDmg();
		Weapon::Damage heavyDmg = activeWeapon.getHeavyDmg();

		cout << "\t===========================================\n";
		cout << "\t\tAttack Types:" << endl;
		cout << "\t------------------------------------------\n";
		cout << "\t - 0 = Cancel Attack: " << endl;
		cout << "\t - 1 = Light Attack: " << lightDmg.display() << endl;
		cout << "\t - 2 = Heavy Attack: " << heavyDmg.display() << endl;
		cout << "\t===========================================\n";

		int choice = -1;
		Weapon::AttackType attackType;

		bool valid = false;
		while (!valid)
		{
			string input = Utils::inputValidator();

			if (Utils::isNumber(input))
			{
				choice = stoi(input);

				if (choice == 0)
				{
					valid = true;
				}
				if (choice > 0 && choice <= (int)Weapon::AttackType::HEAVY)
				{
					//cout << flush;
					system("CLS");
					attackType = (Weapon::AttackType)choice;
					valid = true;
				}
			}

			if (!valid)
			{
				cout << "Invalid input" << endl;
			}
		}

		if (choice == 0)
		{
			cout << "You've canceled your Attack" << endl;
			inputResult.succeeded = false;
		}
		else
		{
			inputResult.succeeded = encounter.attackEnemy(player, (Weapon::AttackType)choice, inputResult.target);
		}
	
		break;
	}
	case Interaction::ActionType::KILL:
	{
		inputResult.succeeded = encounter.killEnemy(inputResult.target);
		break;
	}
	case Interaction::ActionType::STUDY:
	{
		inputResult.succeeded = encounter.studyEnemy(inputResult.target);
		break;
	}
	case Interaction::ActionType::RETREAT:
	{
		currentRoom = encounter.getLastRoom();
		currentRoom->displayContents();
		return;
	}
	}

	if (encounter.getCurrentState() == EnemyEncounter::EncounterState::WIN)
		currentRoom->completeEncounter();
	else if (inputResult.succeeded && inputResult.isActiveAction)
	{
		cout << endl;
		encounter.enemyTurn(player);
		cout << endl;

		encounter.displayEnemies();

		cout << endl;
		cout << "\tPlayer Health: " << player.healthDisplay() << endl;
		cout << "\t===========================================";
	}
}

void Game::enterNewRoom(Room* nextRoom)
{
	if (nextRoom->encounterCount() == 0)
	{
		currentRoom = nextRoom;
		currentRoom->displayContents();
		return;
	}

	EnemyEncounter& encounter = nextRoom->currentEncounter();

	bool startEncounter = encounter.startEncounter();

	if (!startEncounter)
	{
		cout << "You have retreated back to the previous room" << endl;
    currentRoom->displayContents();
		return;
	}

	encounter.setLastRoom(currentRoom);
	encounter.displayEnemies();
	currentRoom = nextRoom;
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
	string inputStr = Utils::inputValidator();

	Interaction::InteractionResult inputResult = Interaction::parseInput(inputStr, isDevMode);

	bool inEncounter = currentRoom->encounterCount() > 0;
  
  if (inputResult.actionType == Interaction::ActionType::ENABLE_DEV_MODE)
	{
		isDevMode = !isDevMode;

		if(isDevMode)
			cout << "DevMode: Activated" << endl;
		else
			cout << "DevMode: Deactivated" << endl;

		return;
	}

	if (inEncounter)
	{
		if (isDevMode)
		{
			if (!EnemyEncounter::canUseDevAction(inputResult.devActionType) && !EnemyEncounter::canUseAction(inputResult.actionType))
			{
				cout << "Sorry you can't do that within an enemy encounter." << endl;
				return;
			}
		}
		else if (!EnemyEncounter::canUseAction(inputResult.actionType))
		{
			cout << "Sorry you can't do that within an enemy encounter." << endl;
			return;
		}
	}
	
	if (isDevMode)
	{
		switch (inputResult.devActionType)
		{
		case Interaction::DevActionType::TP:
		{

			int roomIndex;
			Room* nextRoom;
			string room_name = inputResult.objectName;

			if (roomNameToIndex.find(room_name) != roomNameToIndex.end())
			{
				cout << "Room Found" << endl;

				roomIndex = roomNameToIndex.find(room_name)->second;
				nextRoom = &allRooms[roomIndex];
				//To Do: if next Room is an encounter room, display enter encounter or not
				enterNewRoom(nextRoom);
				return;
			}
			else {
				cout << "Room Not Found" << endl;
			}
			break;
		}
		}
	}
	//Actions
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
		inputResult.succeeded = player.findAndEquip(inputResult.target);
		break;
	}
	case Interaction::ActionType::CHARACTER:
	{
		player.displayStats();
		break;
	}
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
	case Interaction::ActionType::USE:
	{
		inputResult.succeeded = player.useItem(inputResult.target);
		break;
	}
	case Interaction::ActionType::DRINK:
	{
		inputResult.succeeded = player.findAndDrink(inputResult.target);
		break;
	}
	case Interaction::ActionType::OPEN:
	{
		Room::DoorIndex index = getDoorIndex(inputResult.target);

		if (index == Room::DoorIndex::NONE)
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
		Room::DoorIndex index = getDoorIndex(inputResult.target);

		if (index == Room::DoorIndex::NONE)
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
	case Interaction::ActionType::HELP:
	{
		helperDisplay();
		break;
	}
	case Interaction::ActionType::ERROR:
	{
		cout << "Sorry, that input is not recognized." << endl;
		return;
	}
	default:
	{
		if (!inEncounter && EnemyEncounter::canUseAction(inputResult.actionType))
		{
			cout << "Sorry, you can not do that right now." << endl;
			return;
		}
	}
	}

	if (inEncounter)
	{
		encounterInteract(inputResult);
	}

	actionsUsed.insert(inputResult.actionStr);

	cout << endl;
};
