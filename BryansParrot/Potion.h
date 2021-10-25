#pragma once
#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item
{
public:

	Potion(string name, int amount);

	inline int getPotionSize() { return potionSize; }

	string getDisplay() const;

protected:
	int potionSize;
};

#endif // KEY_H
