#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "EnemyEncounter.h"
#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Room class that stores all the information about a room. This includes any
* collectibles, enemies, doors, etc held within the room. Also handles the logic for
* interacting with the room
*
* --------------------------------------------------------------------------------------
* Enums and Structures
* --------------------------------------------------------------------------------------
* DoorIndex
*	enum for what index within the doors array corresponds to what door in the room
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* displayContents()
*	displays the contents of the room to the console. If the room currently has an enemy
*	encounter then it displays the list of enemies in that encounter instead
* 
* addItem(Item newItem)
*	adds newItem to the items vector
* 
* addItems(vector<Item> newItems)
*	adds all of the items in newItems to the items vector
* 
* setDoor(DoorIndex index, Door newDoor)
*	sets the door in the doors array at index to newDoor
* 
* addEnemyEncounter(EnemyEncounter encounter)
*	adds encounter to the encounters vector
* 
* takeItem(string objectName)
*	attempts to find and return the item with the given name in the room. If found the
*	item is removed from the room and returned. If not found, retuns nullptr
* 
* unlockDoor(DoorIndex index, Player& player)
*	attemps to find all keys for the door from the given index within the player's
*	inventory. Uses as all the keys from the player's inventory that are designated to
*	the door. Any used keys are removed from the player's inventory and destroyed
* 
* getDoor(DoorIndex index)
*	returns the door at the given index in the doors array
* 
* currentEncounter()
*	returns a reference to the enemyEnounter in the first spot of the enemyEncounters
*	vector
* 
* completEncounter()
*	removes the first encounter from the encounters vector and adds all of its drops to
*	the room
* 
* encounterCount()
*	returns the number of encounters left in the room
* 
* displayDoor()
*	used as a helper for the displayDoors function to display an individual door to the
*	console.
* 
* displayItems()
*	displays all items in the room to the console, using their getDisplay() function
* 
* displayDoors()
*	displays all doors in the room from the doors array that are not null
* 
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* doors
*	all the doors in the room that lead to other rooms. If a spot is null, that means
*	there is no door in that direction
* 
* items
*	list of all the items in the room that the player can pick up
* 
* encounters
*	list of all the enemy encounters in the room
* --------------------------------------------------------------------------------------
*/
class Room
{
public:
	enum class Direction
	{
		NONE = -1,
		NORTH = 0,
		SOUTH = 1,
		EAST = 2,
		WEST = 3
	};

	void displayContents() const;
	void addItem(shared_ptr<Item> newItem);
	void addItems(vector<shared_ptr<Item>> newItems);
	void setRoom(Direction index, Room* room, int locks = 0, bool bothWays = true);
	void addEnemyEncounter(EnemyEncounter encounter);
	void setDescription(string desc) { description = desc; }

	shared_ptr<Item> takeItem(string objectName);
	void unlockDoor(Direction index, Player& player);

	inline shared_ptr<Door> getDoor(Direction index) { return doors[(int)index]; }
	inline Room* getRoom(Direction index) { return rooms[(int)index]; }

	EnemyEncounter& currentEncounter();
	void completeEncounter();

	int encounterCount();

private:

	shared_ptr<Door> doors[4];
	Room* rooms[4];
	string description = "";

	const static Direction oppDirection[4];

	vector<shared_ptr<Item>> items;
	vector<EnemyEncounter> encounters;

	void displayDoor(Direction index) const;
	void displayItems() const;
	void displayDoors() const;
};

#endif // ROOM_H