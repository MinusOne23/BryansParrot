#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

/*
* Abstract Item class that all items in the game will
* inherit from
* 
* getDisplay() -- function that returns what the item should
* display to the user when in the inventory or in a room
* 
* name -- the name of the item for shorthand display
*/
class Item
{
public:
	inline string getName() const { return name; }

	virtual string getDisplay() const = 0;

protected:
	Item(string _name) : name(_name) {};
	string name;
};

#endif // ITEM_H

