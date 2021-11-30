#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <memory>

#include "Health.h"
#include "Weapon.h"
#include "Potion.h"
#include "Shield.h"

using namespace std;

/*
* Character class to be inherited by any character in the game that can die, attack,
*	and has a name
*
* structures:
*	Equipment - structure to hold on to all of the equipment for the character (i.e.
*		weapons, armor)
*
* methods:
*	getCurrentHealth() - returns current health of the character
*	getMaxHealth() - returns maximum health of the character
*	isDead() - returns true if current health has reached 0
*	getName() - returns character name
*
*	damage(int amt) - decreases the character health by amt
*	heal(int amt) - increases the character health by amt
*	equipWeapon(shared_ptr<Weapon> weapon) - sets the mainWeapon in the equipment
*		to weapon
*	drinkPotion(shared_ptr<Potion> potion) - heals the character by the potion amount
*	getDamage() - uses the mainWeapon getDamage() method to return a randomized
*		amount of damage using the character stats
*	displayStats() - displays the stats of the character to the console
*
* member variables:
*	health - holds all aspects of the character health
*	name - character's name
*	equipment - holds character equipment that is currently equipped
*/


class Character
{
protected:
	struct Equipment
	{
		Weapon baseWeapon;

		shared_ptr<Weapon> mainWeapon;
		shared_ptr<Shield> shield;
	};

	Character(Health _health, string _name, int _baseSpeed, int _baseStamina, float _dodgeChance, Weapon _baseWeapon);

	Health health;
	string name;
	int baseSpeed;
	int baseStamina;
	Equipment equipment;
	float dodge;

	int staminaUsed = 0;


public:

	int getCurrentHealth() const;
	int getMaxHealth() const;
	int getMaxStamina() const;
	int getSpeed() const;
	float getDodgeChance() const;

	int getCurrentStamina() const;
	virtual void refreshStamina();
	void useStamina(int amt);

	bool isDead() const;
	string getName() const;
	Weapon getActiveWeapon() const;
	const shared_ptr<Shield> getShield() const;

	virtual void damage(int amt);
	virtual void heal(int amt);
	virtual void equip(shared_ptr<Equippable> equippable);
	virtual void drinkPotion(shared_ptr<Potion> potion);
	virtual AttackMove::DamageResult calcDamage(string attackName) const;

	string healthDisplay() const;


	void displayStats() const;
};

#endif // CHARACTER_H