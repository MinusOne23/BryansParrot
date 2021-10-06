#include <iostream>

#include "Room.h"
#include "Key.h"
#include "Enemy.h"

using namespace std;

void Room::displayContents() const
{
	cout << "Inside the room you see:" << endl;
	displayItems();
	displayDoors();
	displayEnemies();
}

void Room::addItem(Item* newItem)
{
	items.push_back(newItem);
}

void Room::addDoor(Door* newDoor)
{
	doors.push_back(newDoor);
}

void Room::addEnemy(Enemy* newEnemy)
{
	enemies.push_back(newEnemy);
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

void Room::displayEnemies() const
{
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "A " << enemies[i]->getEnemyName() << " is in the room." << endl;
	}
}



void Room::roomInteract(Player* player1,Door door)
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
			player1->displayInventory();
		}
		else if (inputStr == "take key")
		{
			for (int i = 0; i < items.size(); i++)
			{
				Key* key = dynamic_cast<Key*>(items[i]);
				if (key != nullptr)
				{
					cout << "Key Added to inventory" << endl;
					player1->takeItem(items[i]);
					items.erase(items.begin() + i);
					break;

				}
			}
		}
		else if (inputStr == "open door")
		{
			for (int i = 0; i < doors.size(); i++)
			{
				Door* door = dynamic_cast<Door*>(doors[i]);
				if (door != nullptr)
				{
					cout << "Your opened the door and went to the next room" << endl;
					
				}
			}
			break;
		}
		
		else
		{
			cout << "Sorry, that input is not recognized." << endl;
		}
	}
}