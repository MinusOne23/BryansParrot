#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"

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
	void displayContents() const;
	void addItem(Item* newItem);
	void addDoor(Door* newDoor);
	void addEnemy(Enemy* newEnemy);
	void roomInteract(Player* player, Door door);
	void killEnemy();
private:
	vector<Item*> items;
	vector<Door*> doors;
	vector<Enemy*> enemies;

	void displayItems() const;
	void displayDoors() const;
	void displayEnemies() const;
};

#endif // ROOM_H