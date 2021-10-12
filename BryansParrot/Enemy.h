#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Player.h"
#include "Item.h"

using namespace std;

/*
* Abstract Item class that all items in the game will
* inherit from
*
* getDisplay() -- function that returns what the item should
* display to the user when in the inventory or in a room
*
* name -- the name of the item for shorthand display
*/
class Enemy
{
public:
	
	inline string getEnemyName() const { return name; }
	Enemy(string _name);

	void addDrop(Item* item);

	inline vector<Item*> getDrops() { return drops; }

protected:
	string name;
	vector<Item*> drops;
};

#endif // Enemy_H

