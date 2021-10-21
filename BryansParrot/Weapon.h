#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:

	struct Damage
	{
		int min;
		int max;
	};

	struct Stats
	{
		Damage base;
		float critChance;
		Damage critDamage;
	};

	struct DamageResult
	{
		bool critical;
		int damage;
	};

	Weapon(string _name, Damage _baseDamage, float _critChance, Damage _critDamage);

	DamageResult getDamage();
	Stats getStats();

	virtual string getDisplay() const;

private:
	Damage baseDamage;
	float critChance;
	Damage critDamage;
};

#endif // WEAPON_H