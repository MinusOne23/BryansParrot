#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Item.h"

using namespace std;

/*
*Inventory class to hold items of a player 
* 
* addItem -- Adds the item to the inventory and holds it
*/
class Inventory {
private:
	vector<Item*> items;

public:
	void addItem(Item* item);
	void removeItem(Item* item);
	void display() const;

	Item* operator[] (int i);
	int numItems();
};
#endif // !INVENTORY_H

