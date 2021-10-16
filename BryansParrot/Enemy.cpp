#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy(string _name, int maxHealth)
{
	name = _name;
	health = Health(maxHealth);
}

void Enemy::addDrop(Item* item)
{
	drops.push_back(item);
}
