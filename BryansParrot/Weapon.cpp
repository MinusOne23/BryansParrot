#include <iostream>
#include <iomanip>
#include <sstream>

#include "Weapon.h"

Weapon::Weapon(string _name, Damage _lightDmg, Damage _heavyDmg, float _critChance, float _critMult)
	: Item{ _name }, lightDmg(_lightDmg), heavyDmg(_heavyDmg), critChance(_critChance), critMult(_critMult){}

float Weapon::getCritChance() const
{
	return critChance;
}

float Weapon::getCritMult() const
{
	return critMult;
}

Weapon::DamageResult Weapon::calcDamage(AttackType attackType) const
{
	switch (attackType)
	{
	case AttackType::LIGHT:
		return getDamage(lightDmg);
	case AttackType::HEAVY:
		return getDamage(heavyDmg);
	}

	return DamageResult();
}

Weapon::Damage Weapon::getLightDmg() const
{
	return lightDmg;
}

Weapon::Damage Weapon::getHeavyDmg() const
{
	return heavyDmg;
}


Weapon::DamageResult Weapon::getDamage(Damage damage) const
{
	DamageResult result;
	int hitNum = rand() % 1000;
	result.isHit = hitNum <= 1000 * damage.acc;
	if (!result.isHit)
		return result;

	int critNum = rand() % 1000;
	result.critical = critNum <= 1000 * critChance;

	result.damage = rand() % (damage.max - damage.min + 1) + damage.min;

	if (result.critical)
		result.damage *= critMult;

	return result;
}

string Weapon::getDisplay() const
{
	return name;
}

string Weapon::Damage::display()
{
	stringstream stream;
	stream << min << "-" << max << " " << fixed << setprecision(2) << acc * 100 << "% Accurracy";

	return stream.str();
}
