#include <iostream>
#include <string>

#include "Room.h"
#include "Key.h"
#include "Enemy.h"

using namespace std;

//Displays Items / doors / and enemies in curent room
void Room::displayContents() const
{
	if (doors[0] != nullptr)
	{
		cout << "\t===========================================\n";
		cout << "\t         Inside the room you see:          \n";
		cout << "\t-------------------------------------------\n";
		displayItems();
		displayDoors();
		displayEnemies();
		cout << "\t===========================================\n";
	};
}

//adds a new item to items vector
void Room::addItem(Item* newItem)
{
	items.push_back(newItem);
}

//adds enemy drops to items vector
void Room::addItems(vector<Item*> newItems)
{
	for (unsigned int i = 0; i < newItems.size(); i++)
	{
		items.push_back(newItems[i]);
	}
}

//creates a new door with a index coresponding to direction
void Room::setDoor(RoomDoorIndex index, Door* newDoor)
{
	doors[(int)index] = newDoor;
}

//adds an enemy to the enemies vector
void Room::addEnemy(Enemy* newEnemy)
{
	enemies.push_back(newEnemy);
}

//Displays all items in Items vector
void Room::displayItems() const
{
	for (unsigned int i = 0; i < items.size(); i++) 
	{
		cout << "\t - A " << items[i]->getDisplay() << "." << endl;
	}
}

//Displays all doors in doors vector
//calls DisplayDoor to corespon index to direction
void Room::displayDoors() const
{
	for (int i = 0; i < 4; i++)
	{
		if (doors[i] != nullptr)
			displayDoor((RoomDoorIndex)i, doors[i]);
	}
}

//Displays all Enemies in Enemies vector
void Room::displayEnemies() const
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		cout << "\t - A " << enemies[i]->getName() << "." << endl;
	}
}

//door index switched to direction
//displays door with direction and weither or not it has a lock
void Room::displayDoor(RoomDoorIndex index, Door* door) const
{
	string direction;

	switch(index)
	{
	case RoomDoorIndex::NORTH_DOOR:
		direction = "North";
		break;
	case RoomDoorIndex::SOUTH_DOOR:
		direction = "South";
		break;
	case RoomDoorIndex::EAST_DOOR:
		direction = "East";
		break;
	case RoomDoorIndex::WEST_DOOR:
		direction = "West";
		break;
	}

	if (door->isLocked())
	{
		cout << "\t - A " << direction << " Door with " << door->getLocksLeft() << " lock" << (door->getLocksLeft() > 1 ? "s." : ".") << endl;
	}
	else
	{
		cout << "\t - A " << direction << " Door." << endl;
	}
}

// IF there is a key in the items vector of the room. 
// Then erase that key from the room and return the key to be added to
// the players inventory
Item* Room::takeItem(string objectName)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items[i]->getName() == objectName)
		{
			Item* item = items[i];
			items.erase(items.begin() + i);
			return item;
		}
	}

	cout << "This item is not in the room." << endl;

	return nullptr;
}

//If the door is locked then you cant open the door
//else move the player to the next room
Room* Room::openDoor(RoomDoorIndex index)
{
	int i = (int)index;

	if (doors[i] != nullptr)
	{
		if (doors[i]->isLocked())
		{
			cout << "This door is locked and can not be opened yet." << endl;
			return nullptr;
		}
		else if(doors[i]->getNextRoom() != nullptr)
		{
			cout << "You opened the door and went to the next room" << endl;
			return doors[i]->getNextRoom();
		}
	}

	cout << "There is no door in this direction." << endl;

	return nullptr;
}

//If the door does not have any locks then you cant unlock door
//if the door is locked and you have a keys
//	then you can unlock the one of the locks on the door
//
void Room::unlockDoor(RoomDoorIndex index, Player* player)
{
	if (doors[(int)index] == nullptr)
	{
		cout << "There is no door in that direction." << endl;
		return;
	}

	Door* door = doors[(int)index];

	if (!door->isLocked())
	{
		cout << "Door is already unlocked!" << endl;
		return;
	}

	vector<Key*> keys = player->findKeys(door);
	for (unsigned int i = 0; i < keys.size() && door->isLocked(); i++)
	{
		door->unlock();
		player->removeItem(keys[i]);
	}

	if (door->isLocked())
	{
		cout << "Door still has " << door->getLocksLeft() << " lock" << (door->getLocksLeft() > 1 ? "s " : " ") << "left" << endl;
	}
	else
	{
		cout << "Door is unlocked!" << endl;
	}
}

bool Room::attack(string enemyName, int amt)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy* enemy = enemies[i];

		if (enemy->getName() == enemyName)
		{
			enemy->damage(amt);
			cout << "You dealt " << amt << " damage to " << enemy->getName() << "." << endl;

			if (enemy->isDead())
			{
				killEnemy(enemy);
				enemies.erase(enemies.begin() + i);
			}
			else
			{
				cout << enemy->getName() << " has " << enemy->getCurrentHealth() << " health left." << endl;
			}

			return true;
		}
	}

	cout << "That is not a valid target to attack." << endl;
	return false;
}

void Room::updateTurn(Player* player)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << endl;

		Enemy* enemy = enemies[i];
		Character::DamageResult damageResult = enemy->getDamage();

		if (damageResult.critical)
			cout << "Critical Hit!" << endl;

		cout << enemy->getName() << " hurt you for " << damageResult.damage << " damage!" << endl;

		player->damage(damageResult.damage);

		cout << "You have " << player->getCurrentHealth() << " health left." << endl;
	}
}

void Room::killEnemy(Enemy* enemy)
{
	cout << enemy->getName() << " died!" << endl;
	vector<Item*> drops = enemy->getDrops();

	if (drops.size() > 0)
	{
		cout << "\t===========================================\n";
		cout << "\t                  Drops:                   \n";
		cout << "\t-------------------------------------------\n";

		for (int i = 0; i < drops.size(); i++)
		{
			cout << "\t - " << drops[i]->getDisplay() << endl;
		}

		cout << "\t===========================================\n";

		addItems(drops);
	}
}
