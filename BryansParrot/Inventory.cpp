#include <iostream>

#include "Inventory.h"
#include "Key.h"

using namespace std;

Inventory::~Inventory()
{
	for (Item* item : items)
		delete item;
	items.clear();
}

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
	if (items.size() == 0)
		cout << "\t Empty" << endl;

	for (int i = 0; i < items.size(); i++)
	{
		cout <<"\t - " << items[i]->getDisplay() << endl;
	}
}

Item* Inventory::operator[](int i)
{
	return items[i];
}

int Inventory::numItems()
{
	return items.size();
}
