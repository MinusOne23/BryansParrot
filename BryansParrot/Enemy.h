#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

#include "Item.h"
#include "Character.h"

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
class Enemy : public Character
{
public:
	~Enemy();
	Enemy(string _name, int maxHealth, int minDamage, int maxDamage, float critChance);

	vector<Item*> removeDrops();
	void addDrop(Item* item);

protected:
	vector<Item*> drops;
};

#endif // Enemy_H

