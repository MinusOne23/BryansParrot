#include "Equippable.h"

string Equippable::getDisplay() const
{
	return (isEquipped ? "(E) " : "") + name;
}

void Equippable::setStaminaBoost(int boost)
{
	if (boost < 0)
		boost = 0;

	staminaBoost = boost;
	staminaGiven = staminaBoost;
}

void Equippable::setSpeedBoost(int boost)
{
	speedBoost = boost;
}

void Equippable::setStaminaGiven(int stam)
{
	staminaGiven = stam;

	if (staminaGiven > staminaBoost)
		staminaGiven = staminaBoost;
	else if (staminaGiven < 0)
		staminaGiven = 0;
}

int Equippable::getStaminaBoost() const
{
	return staminaBoost;
}

int Equippable::getSpeedBoost() const
{
	return speedBoost;
}

int Equippable::getStaminaGiven() const
{
	return staminaGiven;
}

Equippable::Equippable(string _name)
	: Item{ _name } {}
