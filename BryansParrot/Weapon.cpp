#include "Weapon.h"


Weapon::Weapon(string _name, Damage _lightDmg, Damage _heavyDmg, float _critChance, float _critMulti)
	: Item{ _name }, lightDmg(_lightDmg), heavyDmg(_heavyDmg), critChance(_critChance), critMulti(_critMulti){}

float Weapon::getCritChance() const
{
	return critChance;
}

Weapon::DamageResult Weapon::calcLightDmg() const
{
	return getDamage(lightDmg);
}

Weapon::DamageResult Weapon::calcHeavyDmg() const
{
	return getDamage(heavyDmg);
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

	//Damage damage = result.critical ? critDamage : baseDamage;
	result.damage = (damage.max - damage.min + 1) + damage.min;
	if (result.critical)
		result.damage *= critMulti;

	return result;
}

string Weapon::getDisplay() const
{
	return name;
}
