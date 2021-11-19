#include <sstream>

#include "Equippable.h"

string Equippable::getDisplay() const
{
	return (isEquipped ? "(E) " : "") + name;
}

string Equippable::equipmentDisplay(string title, string linePrefix) const
{
	stringstream ss;

	if(title == "")
		ss << linePrefix << getName() << endl;
	else
		ss << linePrefix << title << ": " << getName() << endl;

	if (speedBoost)
		ss << linePrefix << "   Speed +" << speedBoost << endl;
	if (staminaBoost)
		ss << linePrefix << "   Stamina +" << staminaBoost << endl;

	return ss.str();
}

string Equippable::inspectDisplay() const
{
	return equipmentDisplay();
}

void Equippable::setStaminaBoost(int boost)
{
	staminaBoost = boost;
}

void Equippable::setSpeedBoost(int boost)
{
	speedBoost = boost;
}

int Equippable::getStaminaBoost() const
{
	return staminaBoost;
}

int Equippable::getSpeedBoost() const
{
	return speedBoost;
}

Equippable::Equippable(string _name)
	: Item{ _name } {}
