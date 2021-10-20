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
	vector<shared_ptr<Item>> items;

public:
	void addItem(shared_ptr<Item> item);
	void removeItem(shared_ptr<Item> item);
	void display() const;

	shared_ptr<Item> operator[] (int i);
	int numItems();
};
#endif // !INVENTORY_H

