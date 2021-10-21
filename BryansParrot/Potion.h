#pragma once
#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "Door.h"

/*
* 
*/
class Potion : public Item
{
public:
	Potion(int amount);

	inline shared_ptr<Item> getPotion() { return potion; }
	//void usePotion(shared_ptr<item> item);
};

#endif // KEY_H
