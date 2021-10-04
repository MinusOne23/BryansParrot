#include <iostream>

#include "Room.h"

using namespace std;

void Room::displayContents() const
{
	cout << "Inside the room you see:" << endl;
	displayItems();
	displayDoors();
}

void Room::addItem(Item* newItem)
{
	items.push_back(newItem);
}

void Room::addDoor(Door* newDoor)
{
	doors.push_back(newDoor);
}

void Room::displayItems() const
{
	for (int i = 0; i < items.size(); i++) 
	{
		cout << "A " << items[i]->getDisplay() << "." << endl;
	}
}

void Room::displayDoors() const
{
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors[i]->isLocked())
		{
			cout << "A door with " << doors[i]->getLocksLeft() << " locks." << endl;
		}
		else
		{
			cout << "A door." << endl;
		}
	}
}
