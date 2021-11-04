#pragma once
#ifndef POTION_H
#define POTION_H

#include "Item.h"

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Potion class for the player to find and be able to use to restore health
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* getDisplay()
*	returns the potion's name as its display
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* potionSize
*	the amount of health the potion restores
* 
* --------------------------------------------------------------------------------------
*/
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
