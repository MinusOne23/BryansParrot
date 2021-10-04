#pragma once
#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "Door.h"

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
