#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "Health.h"

using namespace std;

class Character
{
protected:

	struct DamageStats
	{
		int max;
		int min;

		float critChance;
	};

	Health health;
	DamageStats damageStats;
	string name;

public:

	struct DamageResult
	{
		bool critical;
		int damage;
	};


	int getCurrentHealth() const;
	int getMaxHealth() const;
	bool isDead() const;
	string getName() const;

	virtual void damage(int amt);
	virtual void heal(int amt);

	DamageResult getDamage();
	void displayStats();
};

#endif // CHARACTER_H