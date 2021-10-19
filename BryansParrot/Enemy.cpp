#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::~Enemy()
{
	for (Item* item : drops)
		delete item;
}

Enemy::Enemy(string _name, int maxHealth, int minDamage, int maxDamage, float critChance)
{
	name = _name;
	health = Health(maxHealth);

	damageStats.min = minDamage;
	damageStats.max = maxDamage;
	damageStats.critChance = critChance;
}

vector<Item*> Enemy::removeDrops()
{
	vector<Item*> result = drops;
	drops.clear();

	return result;
}

void Enemy::addDrop(Item* item)
{
	drops.push_back(item);
}
