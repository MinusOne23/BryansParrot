#pragma once
#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "Door.h"

/*
* Key class that inherits from the Item class that allows
* players to unlock locks on doors
* 
* door -- the door that this key is able to unlock
*/
class Key : public Item
{
public:
	Key(Door* _door);
	Key(string _name, Door* _door);
	string getDisplay() const;
private:
	Door* door;
};

#endif // KEY_H
