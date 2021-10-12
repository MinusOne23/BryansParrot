#include <iostream>

#include "Inventory.h"
#include "Key.h"

using namespace std;

void Inventory::addItem(Item* item)
{
	items.push_back(item);
}

void Inventory::removeItem(Item* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			items.erase(items.begin() + i);
			return;
		}
	}
}

void Inventory::display() const 
{
	for (int i = 0; i < items.size(); i++)
	{
		cout <<"\t - " << items[i]->getDisplay() << endl;
	}
}
