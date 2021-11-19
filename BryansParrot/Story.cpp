#include "Story.h"

Story::Story(string _name, string _storyValue)
	: Item{ _name }, storyValue(_storyValue) {}

string Story::getDisplay() const
{
	return name;
}
