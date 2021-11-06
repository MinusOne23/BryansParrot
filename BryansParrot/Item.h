#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Abstract Item class to be inherited by all types of items in the game. Holds the name
* of the item which will be how the player interacts with it
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* getDisplay()
*	gets the actual display string for the item which will be how it is displayed in
*	a room and an inventory - must be implemented by every child class
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* name
*	the name of the item - how players will refer to it in game
* --------------------------------------------------------------------------------------
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

