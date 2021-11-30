#include <iostream>
#include <iomanip>
#include <sstream>

#include "Weapon.h"
#include "Utils.h"



Weapon::Weapon(string _name, float _critChance, float _critMult)
	: Equippable{ _name }, critChance(_critChance), critMult(_critMult) {}

AttackMove::DamageResult Weapon::getDamage(string attackName) const
{
	if(!hasAttackMove(attackName))
		return AttackMove::DamageResult();

	return attackMoves.at(Utils::strToLower(attackName)).getDamage(critChance, critMult);
}

bool Weapon::hasAttackMove(string attackName) const
{
	return attackMoves.find(Utils::strToLower(attackName)) != attackMoves.end();
}

void Weapon::addAttackMove(AttackMove newMove)
{
	attackMoves.insert({ Utils::strToLower(newMove.getName()), newMove });
}

vector<string> Weapon::getMoveNames(int maxStamina) const
{
	vector<string> names;

	for (map<string, AttackMove>::const_iterator it = attackMoves.begin(); it != attackMoves.end(); it++)
	{
		if(maxStamina < 0 || it->second.getStamina() <= maxStamina)
			names.push_back(it->first);
	}

	return names;
}

float Weapon::getCritChance() const
{
	return critChance;
}

float Weapon::getCritMult() const
{
	return critMult;
}

string Weapon::equipmentDisplay(string title, string linePrefix) const
{
	stringstream ss;
	ss << Equippable::equipmentDisplay(title, linePrefix);
	ss << attacksDisplay(linePrefix + "   ");
	ss << linePrefix << "   Crit Chance: " << fixed << setprecision(2) << critChance * 100 << "%" << endl;
	ss << linePrefix << "   Crit Multiplier: " << fixed << setprecision(2) << critMult << "x" << endl;

	return ss.str();
}

string Weapon::attacksDisplay(string linePrefix) const
{
	stringstream ss;
	map<string, AttackMove>::const_iterator it = attackMoves.begin();


	for (int i = 0; i < attackMoves.size(); i++)
	{
		ss << linePrefix << it->second.display() << endl;
		it++;
	}

	return ss.str();
}
