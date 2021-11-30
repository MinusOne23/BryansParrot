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
	: health(_health), baseHealth(_health.getMaxHealth()), name(_name), baseSpeed(_baseSpeed), baseStamina(_baseStamina), dodge(_dodgeChance), equipment{_baseWeapon} {}

string Character::getName() const
{
	return name;
}

Weapon Character::getActiveWeapon() const
{
	return equipment.getActiveWeapon();
}

const shared_ptr<Shield> Character::getShield() const
{
	return equipment.getShield();
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
	equipment.equip(equippable);
	calcNewHealth();
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

void Character::calcNewHealth()
{
	Equipment::EquipmentStats stats = equipment.getEquipmentStats();
	health.setMaxHealth(baseHealth + stats.health);
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

int Character::getDefense() const
{
	return equipment.getEquipmentStats().defense;
}

int Character::getMaxStamina() const
{
	Equipment::EquipmentStats stats = equipment.getEquipmentStats();

	return baseStamina + stats.stamina;
}

int Character::getSpeed() const
{
	Equipment::EquipmentStats stats = equipment.getEquipmentStats();

	return baseSpeed + stats.speed;
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
	Equipment::EquipmentStats stats = equipment.getEquipmentStats();

	cout << "\t===========================================\n";
	cout << "\t " << name << " Stats:" << endl;
	cout << "\t-------------------------------------------\n";
	cout << "\t Health: " << healthDisplay() << endl;
	cout << "\t Stamina: " << getMaxStamina() << endl;
	cout << "\t Speed: " << getSpeed() << endl;
	cout << "\t Defense: " << stats.defense << endl;
	cout << "\t Dodge Chance: " << fixed << setprecision(2) << dodge * 100 << "%" << endl;
	cout << "\t Equipment: " << endl;
	cout << equipment.display("\t    ");
	cout << "\t===========================================\n";
}
