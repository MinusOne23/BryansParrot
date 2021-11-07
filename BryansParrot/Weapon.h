#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Weapon class that can be owned by any character within the game to increase damage
* during combat
*
* --------------------------------------------------------------------------------------
* Enums and Structures
* --------------------------------------------------------------------------------------
* Damage
*	holds the minimum and maximum values for a range of damage
* 
* DamageResult
*	used as result for get damage function to return the amount of damage and whether 
*	or not it was a critical hit
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
*
* getDamage()
*	produces a randomized amount of damage for the weapon evenly distributed based off
*	of first the critChance, and if a critical hit the damage is randomized based off 
*	critDamage, otherwise based off baseDamage
* 
* getDisplay()
*	returns the weapon name as its display
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* baseDamage
*	structure outlining weapon damage range for a noncritical hit
* 
* critChance
*	float for the percent chance the weapon will have a critical hit
* 
* critDamage
*	structure outlining weapon damage range for a critical hit
* --------------------------------------------------------------------------------------
*/
class Weapon : public Item
{
public:

	struct Damage
	{
		int min;
		int max;
	};

	struct DamageResult
	{
		bool critical;
		int damage;
	};

	Weapon(string _name, Damage _baseDamage, float _critChance, Damage _critDamage);

	Damage getBaseDamage() const;
	float getCritChance() const;
	Damage getCritDamage() const;

	DamageResult getDamage() const;

	virtual string getDisplay() const;

private:
	Damage baseDamage;
	float critChance;
	Damage critDamage;
};

#endif // WEAPON_H