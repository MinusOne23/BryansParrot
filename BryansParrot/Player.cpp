#include <iostream>

#include "Player.h"

using namespace std;


void Player::takeItem(Item* item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
}

void Player::displayInventory() const
{
	cout << "---------- Player Inventory ----------" << endl;
	inventory.display();
	cout << "--------------------------------------" << endl;
}
