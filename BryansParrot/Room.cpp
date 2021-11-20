#include <iostream>
#include <string>

#include "Room.h"
#include "Key.h"
#include "Enemy.h"
#include "Utils.h"

#include "EnemyEncounter.h"

using namespace std;

const Room::Direction Room::oppDirection[] = {
	Room::Direction::SOUTH,
	Room::Direction::NORTH,
	Room::Direction::WEST,
	Room::Direction::EAST
};

//Displays Items / doors / and enemies in curent room
void Room::displayContents() const
{
	if (encounters.size() > 0)
	{
		encounters[0].displayEnemies();
		return;
	}
	cout << "\t\t\t" <<description << "\n";
	cout << "\t===========================================\n";
	cout << "\t         Inside the room you see:          \n";
	cout << "\t-------------------------------------------\n";
	displayItems();
	displayDoors();
	cout << "\t===========================================\n";
}

//adds a new item to items vector
void Room::addItem(shared_ptr<Item> newItem)
{
	items.push_back(newItem);
}

//adds enemy drops to items vector
void Room::addItems(vector<shared_ptr<Item>> newItems)
{
	for (unsigned int i = 0; i < newItems.size(); i++)
	{
		addItem(newItems[i]);
	}
}

//creates a new door with a index coresponding to direction
void Room::setRoom(Direction direction, Room* room, int locks, bool bothWays)
{
	int index = (int)direction;
	int oppIndex = (int)oppDirection[index];

	doors[index] = shared_ptr<Door>(new Door(locks));
	rooms[index] = room;

	if (bothWays)
	{
		room->doors[oppIndex] = doors[index];
		room->rooms[oppIndex] = this;
	}
}

void Room::addEnemyEncounter(EnemyEncounter encounter)
{
	encounters.push_back(encounter);
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
		displayDoor((Direction)i);
	}
}

//door index switched to direction
//displays door with direction and weither or not it has a lock
void Room::displayDoor(Direction index) const
{
	shared_ptr<Door> door = doors[(int)index];

	if (door == nullptr)
		return;

	string direction;

	switch(index)
	{
	case Direction::NORTH:
		direction = "North";
		break;
	case Direction::SOUTH:
		direction = "South";
		break;
	case Direction::EAST:
		direction = "East";
		break;
	case Direction::WEST:
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
shared_ptr<Item> Room::takeItem(string objectName)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (Utils::equalsCI(items[i]->getName(), objectName))
		{
			shared_ptr<Item> item = items[i];
			items.erase(items.begin() + i);

			return item;
		}
	}

	return nullptr;
}

//If the door does not have any locks then you cant unlock door
//if the door is locked and you have a keys
//	then you can unlock the one of the locks on the door
//
void Room::unlockDoor(Direction index, Player& player)
{
	if (doors[(int)index] == nullptr)
	{
		cout << "There is no door in that direction." << endl;
		return;
	}

	shared_ptr<Door> door = doors[(int)index];

	if (!door->isLocked())
	{
		cout << "Door is already unlocked!" << endl;
		return;
	}

	vector<shared_ptr<Key>> keys = player.findKeys(door);
	if (keys.size() == 0)
	{
		cout << player.getName() << " has no keys for that door" << endl;
		return;
	}

	for (unsigned int i = 0; i < keys.size() && door->isLocked(); i++)
	{
		door->unlock();
		player.removeItem(keys[i]);
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

EnemyEncounter& Room::currentEncounter()
{
	return encounters[0];
}

void Room::completeEncounter()
{
	if (encounters.size() == 0)
		return;
	
	vector<shared_ptr<Item>> drops = encounters[0].removeDrops();

	cout << "You've completed the encounter!" << endl;

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

	encounters.erase(encounters.begin());
}

int Room::encounterCount()
{
	return encounters.size();
}
