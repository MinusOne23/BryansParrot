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

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Player class to hold all information about the player of the game, including a name,
* health, and player inventory. Inherits from the Character class.
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* takeItem(shared_ptr<Item> item)
*	adds the given item to the player's inventory
* 
* useItem(string itemName)
*	attempts to find and use the item with the given name, if not found returns false
* 
* dropItem(string itemName)
*	removes the item from the player's inventory and returns it
* 
* removeItem(shared_ptr<Item> item)
*	removes the item from the player's inventory and destroys it
* 
* findKeys(shared_ptr<Door> door)
*	finds and returns all keys in the player's inventory that are designated to the
*	given door
* 
* displayInventory()
*	calls the display() function on the player's inventory
* 
* findAndEquip(string itemName)
*	attempts to find a weapon in the player's inventory with the given name and if
*	found, sets the player's main weapon to the found weapon and returns true. If not
*	found, returns false
* 
* findAndDrink(string itemName)
*	attempts to find a potion and then use it to heal the player. If found, returns
*	true, else false.
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* inventory
*	inventory object for the player that hold's all the items in the player's
*	possession
* --------------------------------------------------------------------------------------
*/
class Player : public Character 
{
public:
	Player();
	Player(int maxHealth, Weapon _baseWeapon);

	void takeItem(shared_ptr<Item> item);
	bool useItem(string itemName);
	shared_ptr<Item> dropItem(string itemName);
	void removeItem(shared_ptr<Item> item);
	vector<shared_ptr<Key>> findKeys(shared_ptr<Door> door);
	void displayInventory() const;

	bool findAndDrink(string itemName);
	bool findAndEquip(string itemName);

	virtual void equipWeapon(shared_ptr<Weapon> weapon);
	virtual void drinkPotion(shared_ptr<Potion> potion);
private:
	Inventory inventory;
};
#endif // !PLAYER.H
