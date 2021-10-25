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
	enum class WorldItems
	{
		POTION,
		KEY
	};

	inline string getName() const { return name; } // gets name if item

	virtual string getDisplay() const = 0; //displays item in room

protected:
	Item(string _name) : name(_name) {};
	string name;

};

#endif // ITEM_H

