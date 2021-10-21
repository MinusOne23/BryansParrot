#include <iostream>

#include "Inventory.h"
#include "Key.h"

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

shared_ptr<Item> Inventory::operator[](int i)
{
	return items[i];
}

int Inventory::numItems()
{
	return items.size();
}
