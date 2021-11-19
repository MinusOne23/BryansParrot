#pragma once
#ifndef STORY_H
#define STORY_H

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
class Story : public Item
{
public:

	Story(string name, string value);

	inline string getStoryValue() { return storyValue; }

	string getDisplay() const;

protected:
	string storyValue;
};

#endif // KEY_H
