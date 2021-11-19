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

Weapon Character::getActiveWeapon() const
{
	return equipment.mainWeapon == nullptr ? equipment.baseWeapon : *equipment.mainWeapon;
}

const shared_ptr<Shield> Character::getShield() const
{
	return equipment.shield;
}

void Character::damage(int amt)
{
	health.removeHealth(amt);
}

void Character::heal(int amt)
{
	health.addHealth(amt);
}

void Character::equip(shared_ptr<Equippable> equippable)
{
	shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(equippable);

	if (weapon != nullptr)
	{
		if (equipment.mainWeapon != nullptr)
			equipment.mainWeapon->isEquipped = false;

		equipment.mainWeapon = weapon;
		return;
	}

	shared_ptr<Shield> shield = dynamic_pointer_cast<Shield>(equippable);

	if (shield != nullptr)
	{
		if (equipment.shield != nullptr)
			equipment.shield->isEquipped = false;

		equipment.shield = shield;
		return;
	}
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
	int stamBoost = baseStamina;
	stamBoost += getActiveWeapon().getStaminaBoost();

	if (equipment.shield != nullptr)
		stamBoost += equipment.shield->getStaminaBoost();

	return stamBoost;
}

int Character::getSpeed() const
{
	return getActiveWeapon().getSpeedBoost() + baseSpeed;
}

int Character::getCurrentStamina() const
{
	int maxStamina = getMaxStamina();
	return staminaUsed > maxStamina ? 0 : getMaxStamina() - staminaUsed;
}

void Character::refreshStamina()
{
	staminaUsed = 0;
}

void Character::useStamina(int amt)
{
	staminaUsed += amt;
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
	cout << "\t Dodge Chance: " << fixed << setprecision(2) << dodge * 100 << "%" << endl;
	cout << "\t Equipment: " << endl;
	cout << getActiveWeapon().equipmentDisplay("Main Weapon", "\t    ");
	if (equipment.shield != nullptr)
		cout << equipment.shield->equipmentDisplay("Shield", "\t    ");
	cout << "\t===========================================\n";
}
