#include "Equippable.h"

string Equippable::getDisplay() const
{
	return (isEquipped ? "(E) " : "") + name;
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
