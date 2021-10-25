#include <iostream>

#include "Player.h"

using namespace std;

Player::Player()
{
	inventory = Inventory();
}

void Player::takeItem(Item* item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
}

void Player::removeItem(Item* item)
{
	inventory.removeItem(item);
}

vector<Key*> Player::findKeys(Door* door)
{
	vector<Key*> keys;

	//for (int i = 0; i < inventory.items.size(); i++) 
	for(int i = 0; i < inventory.items.size(); i++)
	{
		//Key* curKey = dynamic_cast<Key*>(inventory.items[i]);
		Key* curKey = dynamic_cast<Key*>(inventory.items[i]);
		if (curKey != nullptr && curKey->getDoor() == door)
		{
			keys.push_back(curKey);
		}
	}

	return keys;
}

void Player::displayInventory() const
{
	cout << "\t---------- Player Inventory ----------" << endl;
	inventory.display();
	cout << "\t--------------------------------------" << endl;
}
