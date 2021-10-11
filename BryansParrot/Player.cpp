#include <iostream>

#include "Player.h"

using namespace std;


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

	for (int i = 0; i < inventory.items.size(); i++) 
	{
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
/*
void Player::roomInteract(Item* key, Door door)
{
	char input[256];
	while (true)
	{
		cin.getline(input, 256);

		string inputStr(input);

		if (inputStr == "q")
		{
			exit(0);
		}
		else if (inputStr == "i")
		{
			displayInventory();
		}
		else if (inputStr == "take key")
		{
			takeItem(key);
		}
		else if (door.isLocked() == false && inputStr == "open door")
		{
			cout << "Your opened the door and went to the next room" << endl;
			break;
		}
		else
		{
			cout << "Sorry, that input is not recognized." << endl;
		}
	}
}
*/
