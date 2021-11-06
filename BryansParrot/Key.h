#pragma once
#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "Door.h"

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Key class which can either be a generalized key to open up general locks, or can be
* designated to a specific door to only be able to open that lock
*
* --------------------------------------------------------------------------------------
* Methods
* -------------------------------------------------------------------------------------
* getDisplay()
*	returns the name of the key as its display
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* door
*	the door that the key is designated to. If null then the key is a general key
* 
* --------------------------------------------------------------------------------------
*/
class Key : public Item
{
public:
	Key();
	Key(shared_ptr<Door> _door);
	Key(string _name, shared_ptr<Door> _door);
	string getDisplay() const;

	inline shared_ptr<Door> getDoor() { return door; }
private:
	shared_ptr<Door> door;
};

#endif // KEY_H
