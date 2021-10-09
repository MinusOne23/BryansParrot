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

 //add input validation after
void Room::roomInteract(Player* player)
{
	char input[256];
	bool stayInRoom = true;

	while (stayInRoom)
	{
		cin.getline(input, 256);

		string inputStr(input);

		if (inputStr == "q")
		{
			exit(0);
		}
		else if (inputStr == "i")
		{
			player->displayInventory();
		}
		else if (inputStr == "take key")
		{
			bool foundKey = false;

			for (int i = 0; i < items.size(); i++)
			{
				Key* key = dynamic_cast<Key*>(items[i]);
				if (key != nullptr)
				{
					foundKey = true;
					player->takeItem(items[i]);
					items.erase(items.begin() + i);
					break;
				}
			}

			if (!foundKey)
			{
				cout << "There is no key in the room." << endl;
			}
		}
		else if (inputStr == "open door")
		{
			bool foundDoor = false;
			for (int i = 0; i < doors.size(); i++)
			{
				foundDoor = true;
				if (doors[i]->isLocked())
				{
					cout << "This door is locked and can not be opened yet." << endl;
					break;
				}
				else
				{
					cout << "Your opened the door and went to the next room" << endl;
					stayInRoom = false;
					break;
				}
			}

			if (!foundDoor)
			{
				cout << "There is no door to be opened." << endl;
			}
		}
		else if (inputStr == "kill goblin")
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				cout << "Oh my! You've killed the Goblin!" << endl << "It appears that they have dropped a key.\n";
				enemies.erase(enemies.begin() + i);
				break;
			}
			stayInRoom = false;
		}
		else if (inputStr == "unlock door")
		{
			bool foundDoor = false;

			for (int i = 0; i < doors.size(); i++)
			{
				Door* door = doors[i];

				if (door->isLocked())
				{
					foundDoor = true;
					vector<Key*> keys = player->findKeys(door);

					for (int j = 0; j < keys.size() && door->isLocked(); j++)
					{
						door->unlock();
						player->removeItem(keys[j]);
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
			}

			if (!foundDoor)
			{
				cout << "There is no door to unlock." << endl;
			}
		}
		else
		{
			cout << "Sorry, that input is not recognized." << endl;
		}

	}
}