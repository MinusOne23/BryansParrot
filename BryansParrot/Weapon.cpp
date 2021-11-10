#include <iostream>
#include <iomanip>
#include <sstream>

#include "Weapon.h"
#include "Utils.h"



Weapon::Weapon(string _name, float _critChance, float _critMult)
	: Item{ _name }, critChance(_critChance), critMult(_critMult) {}

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

string Weapon::getDisplay() const
{
	return name;
}

void Weapon::displayAttacks(string linePrefix) const
{
	map<string, AttackMove>::const_iterator it = attackMoves.begin();


	for (int i = 0; i < attackMoves.size(); i++)
	{
		cout << linePrefix << it->second.display() << endl;
		it++;
	}
}
