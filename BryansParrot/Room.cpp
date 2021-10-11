#include <iostream>

#include "Room.h"
#include "Key.h"
#include "Enemy.h"

using namespace std;

void Room::displayContents() const
{
	cout << "\t===========================================\n";
	cout << "\t         Inside the room you see:          \n";
	cout << "\t-------------------------------------------\n";
	displayItems();
	displayDoors();
	displayEnemies();
	cout << "\t===========================================\n";
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
		cout << "\t - A " << items[i]->getDisplay() << "." << endl;
	}
}


void Room::displayDoors() const
{
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors[i]->isLocked())
		{
			cout << "\t - A door with " << doors[i]->getLocksLeft() << " locks." << endl;
		}
		else
		{
			cout << "\t - A door." << endl;
		}
	}
}


void Room::displayEnemies() const
{
	for (int i = 0; i < enemies.size(); i++)
	{
		cout << "\t - A " << enemies[i]->getEnemyName() << " is in the room." << endl;
	}
}

//Helper Enums used for room ineraction
enum interact
{
	quit = 0,
	inventory = 1,
	takeKey = 2,
	openDoor = 3,
	unlockDoor = 4,
	killGoblin = 5,
	error = 99
};

 //add input validation after

void Room::roomInteract(Player* player)
{
	interact input;

	char userinput[256];
	bool stayInRoom = true;

	while (stayInRoom)
	{
		cin.getline(userinput, 256);
		string inputStr(userinput);

		if (inputStr == "q")
		{
			input = quit;
		}
		else if (inputStr == "i")
		{
			input = inventory;
		}
		else if (inputStr == "take key")
		{
			input = takeKey;
		}
		else if (inputStr == "open door")
		{
			input = openDoor;
		}
		
		else if (inputStr == "kill goblin")
		{
			input = killGoblin;
		}
		else if (inputStr == "unlock door")
		{
			input = unlockDoor;
		}
		else
		{
			input = error;
		}

		bool foundKey = false;
		bool foundDoor = false;

		//Interact
		switch (input)
			{
			case quit:
				exit(0);
			case inventory:
				player->displayInventory();
				break;
			case takeKey:
				//bool foundKey = false;

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
				break;
			case openDoor:
				//bool foundDoor = false;
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
				};
				break;
			case unlockDoor:
				//bool foundDoor = false;

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
				};
				break;
			case killGoblin:
				for (int i = 0; i < enemies.size(); i++)
				{
					cout << "Oh my! You've killed the Goblin!" << endl << "It appears that they have dropped a key.\n";
					enemies.erase(enemies.begin() + i);
					break;
				}
				stayInRoom = false;
				break;
			case error:
				cout << "Sorry, that input is not recognized." << endl;
				break;
			}
	}
}
