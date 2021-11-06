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

using namespace std;

const string VERSION = "1.3.1";

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
/// CREATE NEW WEAPON
///		- create weapon object
///			Weapon [WEAPON_NAME]("[NAME]", baseDamage{min, max}, critChance, critDamage{min, max})
/// 
/// CREATE NEW ENEMY
///		- create enemy object
///			Enemy [ENEMY_NAME]("[NAME]", maxHealth, weapon)
/// 
/// CREATING AN ENEMYY ENCOUNTER
///		- create enemy encounter object
///			EnemyEncounter [ROOM_NAME]Encounter[ENCOUNTER_NUMBER]
///				ex) controlRoomEncounter1
///		- add enemies to the encounter
///			encounter.addEnemy([ENEMY_NAME])
///		- add encounter to the room
///			controlRoom.addEnemyEncounter(controlRoomEncounter1)
/// 
/// ** WHEN ADDING ROOM, ALWAYS UPDATE THE WINROOM OBJ IF NESSESARY **
void Game::initializeGame()
{
	srand(time(NULL));
	Weapon playerFists("Fists", { 10, 20, 0.9f}, { 15, 25, 0.6f}, 0.2f, 1.5f); // Name - Light: Min/Max/Acceracy -Heavy: Min/Max/Acceracy, critchance, critMulti
	Weapon goblinFists("Goblin Fists", { 5, 10, 0.9f }, { 12, 18, 0.6f }, 0.1f, 1.5f);
	Weapon sword("Sword", { 20, 30, 0.95f }, { 35, 50, 0.7f }, 0.25f, 1.65f);

	Enemy goblin("Goblin", 100, goblinFists);

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

	EnemyEncounter secondRoomEncounter1;
	secondRoomEncounter1.addEnemy(goblin);

	//Add drops to specific Enemy Object 
	secondRoomEncounter1.addDrop(shared_ptr<Item>(new Key(secondNorthDoor)));

	//Room 1: Initialization
	firstRoom.setDoor(Room::DoorIndex::NORTH_DOOR, firstNorthDoor);
	firstRoom.addItem(shared_ptr<Item>(new Key(secondNorthDoor)));
	firstRoom.addItem(make_shared<Weapon>(sword));

	//Room 2: Initialization
	secondRoom.setDoor(Room::DoorIndex::NORTH_DOOR, secondNorthDoor);
	secondRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, secondSouthDoor);
	secondRoom.addEnemyEncounter(secondRoomEncounter1);

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

	EnemyEncounter& encounter = nextRoom->currentEncounter();

	bool startEncounter = encounter.startEncounter();
	
	if (!startEncounter)
	{
		cout << "You have retreated back to the previous room" << endl;
		return;
	}

	encounter.setLastRoom(currentRoom);
	encounter.displayEnemies();
	currentRoom = nextRoom;
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

		cout << "Attack Types:" << endl;
		cout << "=============" << endl;
		cout << "0 = Cancel Attack: " << endl;
		cout << "1 = Light Attack: " << lightDmg.display() << endl;
		cout << "2 = Heavy Attack: " << heavyDmg.display() << endl;

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
		cout << "Player Health: " << player.healthDisplay() << endl;
	}
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
	Interaction::InteractionResult inputResult = Interaction::parseInput(inputStr);

	bool inEncounter = currentRoom->encounterCount() > 0;

	if (inEncounter && !EnemyEncounter::canUseAction(inputResult.actionType))
	{
		cout << "Sorry you can't do that within an enemy encounter." << endl;
		return;
	}

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
