#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy(string _name, int maxHealth, int minDamage, int maxDamage, float critChance)
{
	name = _name;
	health = Health(maxHealth);

	damageStats.min = minDamage;
	damageStats.max = maxDamage;
	damageStats.critChance = critChance;
}

void Enemy::addDrop(Item* item)
{
	drops.push_back(item);
}
