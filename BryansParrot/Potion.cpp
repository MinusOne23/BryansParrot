#include "Potion.h"

Potion::Potion(string _name, int _potionSize)
{
	name = _name;
	potionSize = _potionSize;
}

string Potion::getDisplay() const
{
	return name;
}
