#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Inventory.h"
#include "Item.h"
#include "Door.h"
#include "Key.h"
#include "Character.h"

using namespace std;

/// PLAYER CLASS
/// 
/// -defines player stats
///	-interacts with items from the current room
/// 
class Player : public Character 
{
public:
	Player();
	Player(int maxHealth, int minDamage, int maxDamage, float critChance);
	void takeItem(shared_ptr<Item> item);
	void useItem(string item);
	shared_ptr<Item> dropItem(string item);
	void removeItem(shared_ptr<Item> item);
	vector<shared_ptr<Key>> findKeys(shared_ptr<Door> door);
	void displayInventory() const;
private:
	Inventory inventory;
};
#endif // !PLAYER.H
