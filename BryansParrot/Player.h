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

class Player : public Character 
{
public:
	Player();
	Player(int maxHealth, Weapon _baseWeapon);

	void takeItem(shared_ptr<Item> item);
	void removeItem(shared_ptr<Item> item);
	vector<shared_ptr<Key>> findKeys(shared_ptr<Door> door);
	void displayInventory() const;
	void equipWeapon(string weaponName);
private:
	Inventory inventory;
};
#endif // !PLAYER.H
