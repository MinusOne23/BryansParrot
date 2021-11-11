#include <sstream>
#include <iomanip>

#include "AttackMove.h"
#include "Utils.h"

AttackMove::AttackMove(string _name, int _minDamage, int _maxDamage, int _stamina, float _accuracy)
	: name(_name), minDamage(_minDamage), maxDamage(_maxDamage), stamina(_stamina), accuracy(_accuracy) {}

string AttackMove::getName() const
{
	return name;
}

int AttackMove::getStamina() const
{
	return stamina;
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
	result.attackName = name;
	result.staminaUsed = stamina;

	result.isHit = Utils::chanceTest(accuracy);

	if (!result.isHit)
		return result;

	result.damage = rand() % (maxDamage - minDamage + 1) + minDamage;

	result.isCritical = Utils::chanceTest(critChance);

	if (result.isCritical)
		result.damage *= critMult;


	return result;
}


