#include <iostream>
#include <memory>

#include "Player.h"
#include "Utils.h"

using namespace std;

Player::Player()
	: Character{ Health(100), "Player", Weapon("Fists", {10, 20}, 0.2f, {20,40})} {}

Player::Player(int maxHealth, Weapon _baseWeapon)
	: Character{ Health(maxHealth), "Player", _baseWeapon } {}

void Player::takeItem(shared_ptr<Item> item)
{
	inventory.addItem(item);

	cout << item->getName() << " has been added to your inventory." << endl;
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
