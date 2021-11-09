#include <iostream>
#include <memory>

#include "Player.h"
#include "Item.h"
#include "Utils.h"
#include "Potion.h"

using namespace std;

///PLAYER CONSTRUCTOR
///		-Default
///PLAYER OVERLOADED CONSTRCTOR
///		-Changes max health, max damage, min damage, and crit chance
///TAKE ITEM:
///		-Input: Specific Item obj Name
///		-Adds that item to the inventory
///	USE ITEM:
///		-Input item string name
///		-If item is a potion then add potion amount to health
/// DROP ITEM:
///		-removes item from players inventory and adds to current room
/// FIND KEYS:
///		-Adds a key to the key vector 
/// DISPLAY INVENTORY
///		-Displays all individual item from Items vector 

// Stats for the player constructor
Player::Player()
	: Character{ Health(100), "Player", Weapon("Fists", {10, 20, 0.9f}, {15, 25, 0.6f}, 0.2f, 1.5f), 0.75f } {}

Player::Player(int maxHealth, Weapon _baseWeapon, float dodgeChance)
	: Character{ Health(maxHealth), "Player", _baseWeapon, dodgeChance } {}


//Takes a Item form the room and adds it into your inventory
void Player::takeItem(shared_ptr<Item> item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
}

//uses an item from your inventory 
bool Player::useItem(string itemName)
{
	int index = inventory.find(itemName);
	
	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(inventory[index]);
	if (potion != nullptr)
	{
		inventory.remove(index);
		drinkPotion(potion);
		return true;
	}

	shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(inventory[index]);
	if (weapon != nullptr)
	{
		inventory.remove(index);
		equipWeapon(weapon);
		return true;
	}

	cout << "You can not use that item." << endl;
	return false;
}

shared_ptr<Item> Player::dropItem(string itemName)
{
	int index = inventory.find(itemName);
	
	if (index == -1)
		return nullptr;

	cout << "You dropped " << inventory[index]->getName() << endl;
	shared_ptr<Item>item = inventory[index];
	inventory.remove(index);
	return item;
}

void Player::removeItem(shared_ptr<Item> item)
{
	inventory.remove(item);

	cout << item->getName() << " has been removed from your inventory." << endl;
}

vector<shared_ptr<Key>> Player::findKeys(shared_ptr<Door> door)
{
	vector<shared_ptr<Key>> keys;

	for(int i = 0; i < inventory.numItems(); i++)
	{
		shared_ptr<Key> curKey = dynamic_pointer_cast<Key>(inventory[i]);

		if (curKey != nullptr && curKey->getDoor() == door)
		{
			keys.push_back(curKey);
		}
	}

	return keys;
}

//Displays only the items that the player has in his inventory
void Player::displayInventory() const
{
	cout << "\t===========================================\n";
	cout << "\t            Player Inventory:              \n";
	cout << "\t-------------------------------------------\n";
	inventory.display();
	cout << "\t===========================================\n";
}

bool Player::findAndDrink(string itemName)
{
	int index = inventory.find(itemName);

	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(inventory[index]);

	if (potion != nullptr)
	{
		inventory.remove(index);
		drinkPotion(potion);

		return true;
	}

	cout << "You can not drink that item." << endl;
}

bool Player::findAndEquip(string itemName)
{
	int index = inventory.find(itemName);

	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(inventory[index]);

	if (weapon != nullptr)
	{
		inventory.remove(index);
		equipWeapon(weapon);

		return true;
	}

	cout << "You can not equip that item." << endl;
}

void Player::equipWeapon(shared_ptr<Weapon> weapon)
{
	Character::equipWeapon(weapon);

	cout << "You equipped " << weapon->getName() << "." << endl;
}

void Player::drinkPotion(shared_ptr<Potion> potion)
{
	Character::drinkPotion(potion);

	cout << "You drank " << potion->getName() << "." << endl;
	cout << "Your health has been raised by " << potion->getPotionSize() << endl;
}
