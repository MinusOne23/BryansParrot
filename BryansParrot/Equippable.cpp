#include "Equippable.h"

string Equippable::getDisplay() const
{
	return (isEquipped ? "(E) " : "") + name;
}

Equippable::Equippable(string _name)
	: Item{ _name } {}
