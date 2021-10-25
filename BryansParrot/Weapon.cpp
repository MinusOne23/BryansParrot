#include "Weapon.h"

Weapon::Weapon(string _name, Damage _baseDamage, float _critChance, Damage _critDamage)
	: Item{_name}, baseDamage(_baseDamage), critChance(_critChance), critDamage(_critDamage) {}

Weapon::Damage Weapon::getBaseDamage() const
{
	return baseDamage;
}

float Weapon::getCritChance() const
{
	return critChance;
}

Weapon::Damage Weapon::getCritDamage() const
{
	return critDamage;
}

Weapon::DamageResult Weapon::getDamage() const
{
	DamageResult result;

	int critNum = rand() % 1000;
	result.critical = critNum <= 1000 * critChance;

	Damage damage = result.critical ? critDamage : baseDamage;
	result.damage = rand() % (damage.max - damage.min + 1) + damage.min;

	return result;
}

string Weapon::getDisplay() const
{
	return name;
}
