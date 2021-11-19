#pragma once
#ifndef STORY_H
#define STORY_H

#include "Item.h"

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Story class for the player to find and be able to read notes
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* getDisplay()
*	returns the stories name as its display
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* StoryValue
*	string that story will contain value
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
