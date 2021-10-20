#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

#include "Character.h"

using namespace std;

string Character::getName() const
{
	return name;
}

void Character::damage(int amt)
{
	health.removeHealth(amt);
}

void Character::heal(int amt)
{
	health.addHealth(amt);
}

int Character::getCurrentHealth() const
{
	return health.getCurrentHealth();
}

int Character::getMaxHealth() const
{
	return health.getMaxHealth();
}

bool Character::isDead() const
{
	return health.getCurrentHealth() <= 0;
}

Character::DamageResult Character::getDamage()
{
	DamageResult result;

	int critNum = rand() % 1000;

	result.critical = critNum <= 1000 * damageStats.critChance;

	result.damage = rand() % (damageStats.max - damageStats.min + 1) + damageStats.min;

	if (result.critical)
		result.damage *= 2;

	return result;
}

void Character::displayStats()
{
	cout << "\t===========================================\n";
	cout << "\t " << name << " Stats:" << endl;
	cout << "\t-------------------------------------------\n";
	cout << "\t Health: " << health.getCurrentHealth() << " / " << health.getMaxHealth() << endl;
	cout << "\t Damage: " << damageStats.min << "-" << damageStats.max << endl;
	cout << "\t Critical Chance: " << fixed << setprecision(2) << damageStats.critChance * 100 << "%" << endl;
	cout << "\t===========================================\n";
}
