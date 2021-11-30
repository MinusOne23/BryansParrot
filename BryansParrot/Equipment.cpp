#include <sstream>

#include "Equipment.h"
#include "Utils.h"

Equipment::Equipment(Weapon _baseWeapon)
	: baseWeapon(_baseWeapon) {}

Weapon Equipment::getActiveWeapon() const
{
	return curWeapon == nullptr ? baseWeapon : *curWeapon;
}

shared_ptr<Shield> Equipment::getShield() const
{
	return curShield;
}

shared_ptr<Armor> Equipment::getArmor(Armor::ArmorType armorType) const
{
	return curArmors[(int)armorType];
}

Equipment::EquipmentStats Equipment::getEquipmentStats() const
{
	EquipmentStats stats;

	Weapon weapon = getActiveWeapon();
	stats.stamina += weapon.getStaminaBoost();
	stats.speed += weapon.getSpeedBoost();

	if (curShield != nullptr)
	{
		stats.stamina += curShield->getStaminaBoost();
		stats.speed += curShield->getSpeedBoost();
	}

	for (int i = 0; i < Armor::NUM_TYPES; i++)
	{
		if (curArmors[i] != nullptr)
		{
			shared_ptr<Armor> armor = curArmors[i];

			stats.stamina += armor->getStaminaBoost();
			stats.speed += armor->getSpeedBoost();
			stats.health += armor->getHealthBoost();
			stats.defense += armor->getDefense();
		}
	}

	return stats;
}


void Equipment::equip(shared_ptr<Equippable> equippable)
{
	shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(equippable);

	if (weapon != nullptr)
	{
		if (curWeapon != nullptr)
			curWeapon->isEquipped = false;

		curWeapon = weapon;
		return;
	}

	shared_ptr<Shield> shield = dynamic_pointer_cast<Shield>(equippable);

	if (shield != nullptr)
	{
		if (curShield != nullptr)
			curShield->isEquipped = false;

		curShield = shield;
		return;
	}

	shared_ptr<Armor> armor = dynamic_pointer_cast<Armor>(equippable);

	if (armor != nullptr)
	{
		Armor::ArmorType armorType = armor->getArmorType();
		int typeIndex = (int)armorType;

		if (curArmors[typeIndex] != nullptr)
			curArmors[typeIndex]->isEquipped = false;

		curArmors[typeIndex] = armor;
		return;
	}
}

shared_ptr<Equippable> Equipment::unequip(const string& itemName)
{
	shared_ptr<Equippable> result = nullptr;

	if (curWeapon != nullptr && Utils::equalsCI(itemName, curWeapon->getName()))
	{
		result = curWeapon;
		curWeapon->isEquipped = false;
		curWeapon = nullptr;
	}
	else if (curShield != nullptr && Utils::equalsCI(itemName, curShield->getName()))
	{
		result = curShield;
		curShield->isEquipped = false;
		curShield = nullptr;
	}
	else
	{
		for (int i = 0; i < Armor::NUM_TYPES; i++)
		{
			shared_ptr<Armor> armor = curArmors[i];

			if (armor != nullptr && Utils::equalsCI(itemName, armor->getName()))
			{
				result = armor;
				armor->isEquipped = false;
				curArmors[i] = nullptr;
				break;
			}
		}
	}

	return result;
}

string Equipment::display(string linePrefix) const
{
	stringstream ss;
	ss << getActiveWeapon().equipmentDisplay("Main Weapon", linePrefix);
	if (curShield != nullptr)
		ss << curShield->equipmentDisplay("Shield", linePrefix);

	for (int i = 0; i < Armor::NUM_TYPES; i++)
	{
		if (curArmors[i] != nullptr)
			ss << curArmors[i]->equipmentDisplay(Armor::TYPE_NAMES[i], linePrefix);
	}

	return ss.str();
}
