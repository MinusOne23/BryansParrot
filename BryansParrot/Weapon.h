#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <map>
#include <vector>

#include "Item.h"
#include "AttackMove.h"
#include "Equippable.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Weapon class that can be owned by any character within the game to increase damage
* during combat. Has a list of moves unique to it that can be used during combat
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
*
* getDamage(string attackName)
*	returns damage produced by the AttackMove with the name attackName. If there is no
*	such attack, returns a default DamageResult
* 
* hasAttackMove(string attackName)
*	returns whether or not the weapon has an attack with the given attackName
* 
* addAttackMove(AttackMove newMove)
*	adds newMove to the attackMoves map
* 
* getDisplay()
*	returns the weapon name as its display
* 
* displayAttacks()
*	displays all of the weapon's attacks to the player
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* attackMoves
*	map of attackMoves that map each attack's name to the move
* 
* critChance
*	float for the percent chance the weapon will have a critical hit
* 
* critDamage
*	structure outlining weapon damage range for a critical hit
* --------------------------------------------------------------------------------------
*/
class Weapon : public Equippable
{
public:
	Weapon(string _name, float _critChance, float _critMult);

	AttackMove::DamageResult getDamage(string attackName) const;
	bool hasAttackMove(string attackName) const;

	void addAttackMove(AttackMove newMove);

	vector<string> getMoveNames(int maxStamina = -1) const;
	float getCritChance() const;
	float getCritMult() const;

	virtual string equipmentDisplay(string title, string linePrefix = "");
	string attacksDisplay(string linePrefix = "") const;

private:

	map<string, AttackMove> attackMoves;

	float critChance;
	float critMult;
};

#endif // WEAPON_H