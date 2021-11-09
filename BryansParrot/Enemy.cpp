#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy(string _name, int maxHealth, Weapon _baseWeapon, float _dodgeChance)
	: Character{ Health(maxHealth), _name, _baseWeapon, _dodgeChance } {}
