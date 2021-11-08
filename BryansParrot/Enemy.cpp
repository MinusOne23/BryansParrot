#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy(string _name, int maxHealth, int _baseSpeed, int _baseStamina, Weapon _baseWeapon)
	: Character{ Health(maxHealth), _name, _baseSpeed, _baseStamina, _baseWeapon } {}

string Enemy::getRandomAttack() const
{
	Weapon activeWeapon = getActiveWeapon();
	vector<string> attackNames = activeWeapon.getMoveNames();

	return attackNames[rand() % attackNames.size()];
}
