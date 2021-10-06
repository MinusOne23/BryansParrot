#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

/*
*Inventory class to hold items of a player 
* 
* addItem -- Adds the item to the inventory and holds it
*/
class Inventory {
public:

	void addItem(Item* item);
private:
	vector <Item*>  item;
	void display() const;
};
#endif // !INVENTORY_H

