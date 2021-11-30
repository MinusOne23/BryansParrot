#include <iostream>
#include <memory>

#include "Player.h"
#include "Item.h"
#include "Utils.h"
#include "Potion.h"
#include "Story.h"

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
	: Character{ Health(100), "Player", 1, 1, 0.75f, Weapon("None", 0.0f, 0.0f) } {}

Player::Player(int maxHealth, int _baseSpeed, int _baseStamina, float _dodgeChance, Weapon _baseWeapon)
	: Character{ Health(maxHealth), "Player", _baseSpeed, _baseStamina, _dodgeChance, _baseWeapon } {}

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

	shared_ptr<Story> story = dynamic_pointer_cast<Story>(inventory[index]);
	if (story != nullptr)
	{
		inventory.remove(index);
		readStory(story);
		return true;
	}

	shared_ptr<Equippable> equippable = dynamic_pointer_cast<Equippable>(inventory[index]);
	if (equippable != nullptr)
	{
		equip(equippable);
		return true;
	}

	cout << "You can not use that item." << endl;
	return false;
}

shared_ptr<Item> Player::dropItem(string itemName)
{
	int index = inventory.find(itemName);
	
	if (index == -1)
	{
		cout << "That item is not in your inventory" << endl;
		return nullptr;
	}

	shared_ptr<Equippable> equippable = dynamic_pointer_cast<Equippable>(inventory[index]);

	if (equippable->isEquipped)
	{
		cout << "You must unequip that item before it can be dropped" << endl;
		return nullptr;
	}

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

bool Player::findAndDrink(const string& itemName)
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

bool Player::findAndRead(const string& itemName)
{
	int index = inventory.find(itemName);

	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	shared_ptr<Story> story = dynamic_pointer_cast<Story>(inventory[index]);

	if (story != nullptr)
	{

		readStory(story);
		inventory.remove(index);
		

		return true;
	}

	cout << "You can not read that item." << endl;
}

bool Player::findAndEquip(const string& itemName)
{
	int index = inventory.find(itemName);

	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	shared_ptr<Equippable> equippable = dynamic_pointer_cast<Equippable>(inventory[index]);

	if (equippable != nullptr)
	{
		equip(equippable);
		return true;
	}

	cout << "You can not equip that item." << endl;
	return false;
}

bool Player::findAndUnequip(const string& itemName)
{
	shared_ptr<Equippable> unequipped = equipment.unequip(itemName);

	if (unequipped != nullptr)
	{
		cout << "You unequipped " << unequipped->getName() << endl;
		calcNewHealth();

		return true;
	}

	cout << "That item is not equipped." << endl;
	return false;
}

bool Player::findAndInspect(const string& itemName)
{
	int index = inventory.find(itemName);

	if (index == -1)
	{
		cout << "That item is not in your inventory." << endl;
		return false;
	}

	cout << endl;
	cout << "===========================================" << endl;
	cout << inventory[index]->inspectDisplay();
	cout << "===========================================" << endl;

	return true;
}

bool Player::isDev()
{
	return m_isDev;
}

void Player::setIsDev(bool _isDev)
{
	m_isDev = _isDev;
}

void Player::drinkPotion(shared_ptr<Potion> potion)
{
	Character::drinkPotion(potion);

	cout << "You drank " << potion->getName() << "." << endl;
	cout << "Your health has been raised by " << potion->getPotionSize() << endl;
}

void Player::readStory(shared_ptr<Story> story)
{
	

	cout << "You are reading " << story->getName() << ":" << endl;
	cout << story->getStoryValue() << endl;
}

void Player::equip(shared_ptr<Equippable> equippable)
{
	if (equippable->isEquipped)
	{
		cout << equippable->getName() << " is already equipped." << endl;
		return;
	}

	Character::equip(equippable);
	cout << "You equipped " << equippable->getName() << "." << endl;
	equippable->isEquipped = true;
}
