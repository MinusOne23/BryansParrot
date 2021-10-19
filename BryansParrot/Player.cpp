#include <iostream>

#include "Player.h"

using namespace std;

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

void Player::takeItem(Item* item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
}

void Player::removeItem(Item* item)
{
	inventory.removeItem(item);

	cout << item->getName() << " has been removed from your inventory." << endl;
}

vector<Key*> Player::findKeys(Door* door)
{
	vector<Key*> keys;

	for(int i = 0; i < inventory.numItems(); i++)
	{
		Key* curKey = dynamic_cast<Key*>(inventory[i]);

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
