#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>

#include "Item.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Inventory class that holds a list of items currently in the player's possession
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* display()
*	displays the inventory to the user on the console
* 
* numItems()
*	returns the size of the items vector
* 
* remove(int index)
*	removes the item at the specified index
* 
* find(string itemName)
*	finds the item in the inventory with the given name and returns the index of the
*	item. If not found, returns -1
* 
* operator[]
*	faster way to access the items in the inventory by just using the hard brackets
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* items
*	list of all the items currently in the inventory
* --------------------------------------------------------------------------------------
*/
class Inventory {
private:
	vector<shared_ptr<Item>> items;

public:
	void addItem(shared_ptr<Item> item);
	void remove(shared_ptr<Item> item);
	void remove(int index);
	void display() const;
	int find(string itemName);

	shared_ptr<Item> operator[] (int i);
	int numItems();
};
#endif // !INVENTORY_H

