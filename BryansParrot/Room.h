#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"

using namespace std;

enum class RoomDoorIndex
{
	NORTH_DOOR = 0,
	SOUTH_DOOR = 1,
	EAST_DOOR = 2,
	WEST_DOOR = 3
};

/*
* Room class that stores all the contents of a room
* 
* items -- list of all the items within the room
* doors -- list of all the doors within the room
*/
class Room
{
public:
	void displayContents() const;
	void addItem(Item* newItem);
	void addItems(vector<Item*> newItems);
	void setDoor(RoomDoorIndex index, Door* newDoor);
	void addEnemy(Enemy* newEnemy);

	Key* takeKey();
	Room* openDoor(RoomDoorIndex index);
	void unlockDoor(RoomDoorIndex index, Player* player);
	void attack(string enemyName, int amt);

	inline Door* getDoor(RoomDoorIndex index) { return doors[(int)index]; }

private:
	Door* doors[4];

	vector<Item*> items;
	vector<Enemy*> enemies;

	void displayDoor(RoomDoorIndex index, Door* door) const;

	void displayItems() const;
	void displayDoors() const;
	void displayEnemies() const;

	void killEnemy(Enemy* enemy);
};

#endif // ROOM_H