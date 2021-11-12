#pragma once
#ifndef EQUIPPABLE_H
#define EQUIPPABLE_H

#include <string>

#include "Item.h"

using namespace std;

class Equippable: public Item
{
public:
	int speedBoost = 0;
	int staminaBoost = 0;
	bool isEquipped = false;

	virtual string getDisplay() const;

protected:
	Equippable(string _name);
};

#endif // EQUIPPABLE_H