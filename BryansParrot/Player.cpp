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
	: Character{ Health(100), "Player", Weapon("Fists", {10, 20}, 0.2f, {20,40})} {}

Player::Player(int maxHealth, Weapon _baseWeapon)
	: Character{ Health(maxHealth), "Player", _baseWeapon } {}


//Takes a Item form the room and adds it into your inventory
void Player::takeItem(shared_ptr<Item> item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
}

//uses an item from your inventory 
void Player::useItem(string item)
{
	for (int i = 0; i < inventory.numItems(); i++)
	{
		if (Utils::equalsCI(item,inventory[i]->getName()))
		{
			cout << "you used " << inventory[i]->getName() << "." << endl;
			shared_ptr<Potion>potion = dynamic_pointer_cast<Potion>(inventory[i]);
			if (potion != nullptr)
			{
				heal(potion->getPotionSize());
				inventory.removeItem(potion);
				cout << "Your health has been raised by " << potion->getPotionSize() << endl;
			}
			return ;
		}
	
	}
	cout << "Item is not in your Inventory" << endl;
}

shared_ptr<Item> Player::dropItem(string item)
{
	for (int i = 0;i < inventory.numItems(); i++)
	{
		if (Utils::equalsCI(item, inventory[i]->getName()))
		{
			cout << "You dropped " << inventory[i]->getName() << endl;
			shared_ptr<Item>item = inventory[i];
			inventory.removeItem(item);
			return item;
		}
	}
	return nullptr;
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

void Player::equipWeapon(string weaponName)
{
	for (int i = 0; i < inventory.numItems(); i++)
	{
		shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(inventory[i]);

		if (weapon != nullptr && Utils::equalsCI(weapon->getName(), weaponName))
		{
			equipment.mainWeapon = weapon;
			inventory.remove(i);

			cout << "You equipped " << weapon->getName() << "." << endl;
			return;
		}
	}

	cout << "That equipment is not in your inventory." << endl;
}
