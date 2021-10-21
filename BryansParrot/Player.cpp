#include <iostream>
#include <memory>

#include "Player.h"
#include "Item.h"
#include "Utils.h"
#include "Potion.h"

using namespace std;

// Stats for the player constructor
Player::Player()
{
	name = "Player";
	health = Health(100);
	damageStats.min = 10;
	damageStats.max = 30;
	damageStats.critChance = 0.2f;
}

Player::Player(int maxHealth, int minDamage, int maxDamage, float critChance)
{
	name = "Player";
	health = Health(maxHealth);
	damageStats.min = minDamage;
	damageStats.max = maxDamage;
	damageStats.critChance = critChance;
}


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
	inventory.removeItem(item);

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


void Player::displayInventory() const
{
	cout << "\t===========================================\n";
	cout << "\t            Player Inventory:              \n";
	cout << "\t-------------------------------------------\n";
	inventory.display();
	cout << "\t===========================================\n";
}
