#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "Health.h"
#include "Weapon.h"

using namespace std;

class Character
{
protected:
	struct Equipment
	{
		Weapon baseWeapon;

		shared_ptr<Weapon> mainWeapon;
	};

	Health health;
	string name;
	Equipment equipment;

public:

	Character(Health _health, string _name, Weapon _baseWeapon);

	int getCurrentHealth() const;
	int getMaxHealth() const;
	bool isDead() const;
	string getName() const;

	virtual void damage(int amt);
	virtual void heal(int amt);
	virtual void equipWeapon(shared_ptr<Weapon> weapon);
	virtual Weapon::DamageResult getDamage();

	void displayStats();
};

#endif // CHARACTER_H