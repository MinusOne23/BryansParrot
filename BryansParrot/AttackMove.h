#pragma once
#ifndef ATTACK_MOVE_H
#define ATTACK_MOVE_H

#include <string>

using namespace std;

class AttackMove
{
public:
	struct DamageResult
	{
		string attackName = "NULL ATTACK";
		int staminaUsed = 0;
		bool isCritical = false;
		bool isHit = false;
		int damage = 0;
	};

	AttackMove(string _name, int _minDamage, int _maxDamage, int _stamina, float _accuracy);
	
	string getName() const;

	DamageResult getDamage(float critChance, float critMult) const;
	
	string display() const;

private:
	string name;
	int minDamage;
	int maxDamage;
	int stamina;
	float accuracy;
};

#endif // ATTACK_MOVE_H

