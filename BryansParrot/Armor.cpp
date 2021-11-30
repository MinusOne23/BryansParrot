#include <sstream>

#include "Armor.h"

const string Armor::TYPE_NAMES[Armor::NUM_TYPES] =
{
    "Head",
    "Chest",
    "Hands",
    "Legs",
    "Feet"
};

Armor::Armor(string _name, ArmorType _armorType, int _defense)
    : Equippable{ _name }, armorType(_armorType), defense(_defense) {}

Armor::ArmorType Armor::getArmorType() const
{
    return armorType;
}

int Armor::getDefense() const
{
    return defense;
}

int Armor::getHealthBoost() const
{
    return healthBoost;
}

void Armor::setDefense(int newDefense)
{
    defense = newDefense;
}

void Armor::setHealthBoost(int newHealthBoost)
{
    healthBoost = newHealthBoost;
}

string Armor::equipmentDisplay(string title, string linePrefix) const
{
    stringstream ss;
    ss << Equippable::equipmentDisplay(title, linePrefix);
    ss << linePrefix << "   Defense +" << defense << endl;

    if (healthBoost)
        ss << linePrefix << "   Health +" << healthBoost << endl;

    return ss.str();
}
