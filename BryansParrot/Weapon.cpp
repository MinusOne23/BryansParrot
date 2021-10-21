#include "Weapon.h"

Weapon::Weapon(string _name, Damage _baseDamage, float _critChance, Damage _critDamage)
	: Item{_name}, baseDamage(_baseDamage), critChance(_critChance), critDamage(_critDamage) {}

Weapon::DamageResult Weapon::getDamage()
{
	DamageResult result;

	int critNum = rand() % 1000;

	result.critical = critNum <= 1000 * critChance;

	Damage damage = result.critical ? critDamage : baseDamage;

	result.damage = rand() % (damage.max - damage.min + 1) + damage.min;

	return result;
}

Weapon::Stats Weapon::getStats()
{
	return {baseDamage, critChance, critDamage};
}

string Weapon::getDisplay() const
{
	return name;
}
