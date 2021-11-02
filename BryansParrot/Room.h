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
* Room class that stores all the contents of a room
* 
* items -- list of all the items within the room
* doors -- list of all the doors within the room
*/
class Room
{
public:
	enum class DoorIndex
	{
		NONE = -1,
		NORTH_DOOR = 0,
		SOUTH_DOOR = 1,
		EAST_DOOR = 2,
		WEST_DOOR = 3
	};

	void displayContents() const;
	void addItem(shared_ptr<Item> newItem);
	void addItems(vector<shared_ptr<Item>> newItems);
	void setDoor(DoorIndex index, shared_ptr<Door> newDoor);
	void addEnemy(Enemy newEnemy, int waveIndex = 0);

	shared_ptr<Item> takeItem(string objectName);
	void unlockDoor(DoorIndex index, Player& player);
	bool attack(string enemyName, int amt, bool critical);

	inline shared_ptr<Door> getDoor(DoorIndex index) { return doors[(int)index]; }

	void updateTurn(Player& player);
	EnemyEncounter::EncounterState startEncounter(Player& player);

private:
	shared_ptr<Door> doors[4];

	vector<shared_ptr<Item>> items;
	vector<Enemy> enemies;
	vector<vector<Enemy*>> waves;

	void displayDoor(DoorIndex index) const;

	void displayItems() const;
	void displayDoors() const;
	void displayEnemies() const;

	void killEnemy(Enemy& enemy);
};

#endif // ROOM_H