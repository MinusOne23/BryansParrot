#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

#include "Character.h"

using namespace std;

Character::Character(Health _health, string _name, Weapon _baseWeapon)
	: health(_health), name(_name), equipment{_baseWeapon} {}

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

void Character::equipWeapon(shared_ptr<Weapon> weapon)
{
	equipment.mainWeapon = weapon;
}

Weapon::DamageResult Character::getDamage()
{
	return equipment.mainWeapon == nullptr ? (equipment.baseWeapon.getDamage()) : (equipment.mainWeapon->getDamage());
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

void Character::displayStats()
{
	Weapon mainWeapon = equipment.mainWeapon == nullptr ? equipment.baseWeapon : *equipment.mainWeapon;
	Weapon::Stats mainStats = mainWeapon.getStats();

	cout << "\t===========================================\n";
	cout << "\t " << name << " Stats:" << endl;
	cout << "\t-------------------------------------------\n";
	cout << "\t Health: " << health.getCurrentHealth() << " / " << health.getMaxHealth() << endl;
	cout << "\t Equipment: " << endl;
	cout << "\t    MainWeapon: " << mainWeapon.getName() << endl;
	cout << "\t       Base Damage: " << mainStats.base.min << "-" << mainStats.base.max << endl;
	cout << "\t       Crit Chance: " << fixed << setprecision(2) << mainStats.critChance * 100 << "%" << endl;
	cout << "\t       Crit Damage: " << mainStats.critDamage.min << "-" << mainStats.critDamage.max << endl;
	cout << "\t===========================================\n";
}
