#include <iostream>
#include <string>

#include "Room.h"
#include "Key.h"
#include "Enemy.h"

using namespace std;

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

void Room::addItem(Item* newItem)
{
	items.push_back(newItem);
}

void Room::addItems(vector<Item*> newItems)
{
	for (unsigned int i = 0; i < newItems.size(); i++)
	{
		items.push_back(newItems[i]);
	}
}

void Room::setDoor(RoomDoorIndex index, Door* newDoor)
{
	doors[(int)index] = newDoor;
}

void Room::addEnemy(Enemy* newEnemy)
{
	enemies.push_back(newEnemy);
}

void Room::displayItems() const
{
	for (unsigned int i = 0; i < items.size(); i++) 
	{
		cout << "\t - A " << items[i]->getDisplay() << "." << endl;
	}
}

void Room::displayDoors() const
{
	for (int i = 0; i < 4; i++)
	{
		if (doors[i] != nullptr)
			displayDoor((RoomDoorIndex)i, doors[i]);
	}
}

void Room::displayEnemies() const
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		cout << "\t - A " << enemies[i]->getEnemyName() << "." << endl;
	}
}


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


Key* Room::takeKey()
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		Key* key = dynamic_cast<Key*>(items[i]);
		if (key != nullptr)
		{
			items.erase(items.begin() + i);
			return key;
		}
	}

	cout << "There is no key in the room." << endl;

	return nullptr;
}

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

vector<Item*> Room::killGoblin()
{
	vector<Item*> result;
	if (enemies.size() > 0)
	{
		cout << "Oh my! You've killed the Goblin!" << endl << "It appears that they have dropped a key." << endl;
		result = enemies[0]->getDrops();
		enemies.erase(enemies.begin());
	}
	else
	{
		cout << "There is no Goblin to kill." << endl;
	}

	return result;
}
