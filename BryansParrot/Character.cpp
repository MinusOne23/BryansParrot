#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Character.h"

using namespace std;

/// CHARACTER CLASS FUNCTIONS
/// 
/// GET_NAME: Returns character name
/// DAMAGE: Lowers players heath
/// HEAL: Adds to players health
/// GET_CURRENT_HEALTH: Returns players current health
/// GET_MAX_HEALTH: Returns max health possible
/// IS_DEAD: Player health reaches 0
/// GET_DAMAGE: Adds up damage health and returns
/// DISPLAY_STATS: Displays Current/Max Health, min/max damage, and Crit chance percentage

Character::Character(Health _health, string _name, int _baseSpeed, int _baseStamina, float _dodgeChance, Weapon _baseWeapon)
	: health(_health), name(_name), baseSpeed(_baseSpeed), baseStamina(_baseStamina), dodge(_dodgeChance), equipment{_baseWeapon} {}

string Character::getName() const
{
	return name;
}

Character::Equipment Character::getEquipment() const
{
	return equipment;
}

Weapon Character::getActiveWeapon() const
{
	return equipment.mainWeapon == nullptr ? equipment.baseWeapon : *equipment.mainWeapon;
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
	curStamina += weapon->staminaBoost;
}

void Character::drinkPotion(shared_ptr<Potion> potion)
{
	heal(potion->getPotionSize());
}

AttackMove::DamageResult Character::calcDamage(string attackName) const
{
	return getActiveWeapon().getDamage(attackName);
}

string Character::healthDisplay() const
{
	stringstream ss;

	ss << "(" << health.getCurrentHealth() << " / " << health.getMaxHealth() << ")";

	return ss.str();
}

int Character::getCurrentHealth() const
{
	return health.getCurrentHealth();
}

int Character::getMaxHealth() const
{
	return health.getMaxHealth();
}

float Character::getDodgeChance() const
{
	return dodge;
}

int Character::getMaxStamina() const
{
	return getActiveWeapon().staminaBoost + baseStamina;
}

int Character::getSpeed() const
{
	return getActiveWeapon().speedBoost + baseSpeed;
}

int Character::getCurrentStamina() const
{
	return curStamina;
}

void Character::refreshStamina()
{
	curStamina = getMaxStamina();
}

void Character::useStamina(int amt)
{
	curStamina -= amt;

	if (curStamina < 0)
		curStamina = 0;
}

bool Character::isDead() const
{
	return health.getCurrentHealth() <= 0;
}

void Character::displayStats() const
{
	Weapon activeWeapon = getActiveWeapon();

	cout << "\t===========================================\n";
	cout << "\t " << name << " Stats:" << endl;
	cout << "\t-------------------------------------------\n";
	cout << "\t Health: " << healthDisplay() << endl;
	cout << "\t Stamina: " << getMaxStamina() << endl;
	cout << "\t Speed: " << getSpeed() << endl;
	cout << "\t Equipment: " << endl;
	cout << "\t    MainWeapon: " << activeWeapon.getName() << endl;
	activeWeapon.displayAttacks("\t       ");
	cout << "\t       Crit Chance: " << fixed << setprecision(2) << activeWeapon.getCritChance() * 100 << "%" << endl;
	cout << "\t       Crit Multiplier: " << fixed << setprecision(2) << activeWeapon.getCritMult() << "x" << endl;
	if(activeWeapon.speedBoost)
		cout << "\t       Speed +" << activeWeapon.speedBoost << endl;
	if (activeWeapon.staminaBoost)
		cout << "\t       Stamina +" << activeWeapon.staminaBoost << endl;
	cout << "\t===========================================\n";
}
