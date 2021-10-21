#include "Enemy.h"
#include "Room.h"
#include "Key.h"
#include <string>
#include <iostream>
using namespace std;

Enemy::Enemy(string _name, int maxHealth, Weapon _baseWeapon)
	: Character{ Health(maxHealth), _name, _baseWeapon } {}

vector<shared_ptr<Item>> Enemy::removeDrops()
{
	vector<shared_ptr<Item>> result = drops;
	drops.clear();

	return result;
}

void Enemy::addDrop(shared_ptr<Item> item)
{
	drops.push_back(item);
}
