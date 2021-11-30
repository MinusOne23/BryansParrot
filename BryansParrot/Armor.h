#pragma once
#ifndef ARMOR_H
#define ARMOR_H

#include "Equippable.h"

class Armor : public Equippable
{
public:
	static const int NUM_TYPES = 5;
	static const string TYPE_NAMES[NUM_TYPES];

	enum class ArmorType
	{
		HEAD = 0,
		CHEST,
		HANDS,
		LEGS,
		FEET
	};

	Armor(string _name, ArmorType _armorType, int _defense);

	ArmorType getArmorType() const;
	int getDefense() const;
	int getHealthBoost() const;

	void setDefense(int newDefense);
	void setHealthBoost(int newHealthBoost);
	string equipmentDisplay(string title, string linePrefix) const override;

private:

	ArmorType armorType;
	int defense;

	int healthBoost = 0;
};

#endif // ARMOR_H