#include <iostream>

#include "Inventory.h"

using namespace std;

void Inventory::addItem(Item* item) 
{
	items.push_back(item);
}

void Inventory::display() const 
{
	for (int i = 0; i < items.size(); i++)
	{
		cout << items[i]->getDisplay() << endl;
	}
}
