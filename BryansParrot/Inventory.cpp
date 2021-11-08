#include <iostream>

#include "Inventory.h"
#include "Key.h"
#include "Utils.h"

using namespace std;

void Inventory::addItem(shared_ptr<Item> item)
{
	items.push_back(item);
}

void Inventory::remove(shared_ptr<Item> item)
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

void Inventory::remove(int index)
{
	items.erase(items.begin() + index);
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

int Inventory::find(string itemName)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (Utils::equalsCI(items[i]->getName(), itemName))
			return i;
	}

	return -1;
}

shared_ptr<Item> Inventory::operator[](int i)
{
	return items[i];
}

int Inventory::numItems()
{
	return items.size();
}
