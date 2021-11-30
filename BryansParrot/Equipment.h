#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <memory>
#include <string>

#include "Equippable.h"
#include "Weapon.h"
#include "Shield.h"
#include "Armor.h"

using namespace std;

class Equipment
{
public:
	struct EquipmentStats
	{
		int stamina = 0;
		int speed = 0;
		int health = 0;
		int defense = 0;
	};

	Equipment(Weapon _baseWeapon);

	Weapon getActiveWeapon() const;
	shared_ptr<Shield> getShield() const;
	shared_ptr<Armor> getArmor(Armor::ArmorType armorType) const;

	EquipmentStats getEquipmentStats() const;

	void equip(shared_ptr<Equippable> equippable);
	shared_ptr<Equippable> unequip(const string& itemName);

	string display(string linePrefix) const;

private:
	Weapon baseWeapon;
	shared_ptr<Weapon> curWeapon;
	shared_ptr<Shield> curShield;
	shared_ptr<Armor> curArmors[Armor::NUM_TYPES] = {0};
};

#endif // EQUIPMENT_H
