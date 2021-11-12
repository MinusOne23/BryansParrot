#pragma once
#ifndef EQUIPPABLE_H
#define EQUIPPABLE_H

#include <string>

#include "Item.h"

using namespace std;

class Equippable: public Item
{
public:
	bool isEquipped = false;

	virtual string getDisplay() const;

	void setStaminaBoost(int boost);
	void setSpeedBoost(int boost);
	void setStaminaGiven(int stam);

	int getStaminaBoost() const;
	int getSpeedBoost() const;
	int getStaminaGiven() const;

protected:
	Equippable(string _name);

private:
	int speedBoost = 0;
	int staminaBoost = 0;
	int staminaGiven = 0;
};

#endif // EQUIPPABLE_H