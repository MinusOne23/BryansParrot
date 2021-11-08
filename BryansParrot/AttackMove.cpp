#include <sstream>
#include <iomanip>

#include "AttackMove.h"

AttackMove::AttackMove(string _name, int _minDamage, int _maxDamage, int _stamina, float _accuracy)
	: name(_name), minDamage(_minDamage), maxDamage(_maxDamage), stamina(_stamina), accuracy(_accuracy) {}

string AttackMove::getName() const
{
	return name;
}

string AttackMove::display() const
{
	stringstream ss;

	ss << name << ": (" << minDamage << " - " << maxDamage << "), " << stamina << " stamina, " << fixed << setprecision(2) << accuracy * 100 << "% accuracy";

	return ss.str();
}

AttackMove::DamageResult AttackMove::getDamage(float critChance, float critMult) const
{
	DamageResult result;

	int hitNum = rand() % 1000;
	result.isHit = hitNum <= 1000 * accuracy;

	if (!result.isHit)
		return result;

	result.damage = rand() % (maxDamage - minDamage + 1) + minDamage;

	int critNum = rand() % 1000;
	result.isCritical = critNum <= 1000 * critChance;

	if (result.isCritical)
		result.damage *= critMult;

	result.attackName = name;

	return result;
}


