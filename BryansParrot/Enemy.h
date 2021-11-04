#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <memory>

#include "Item.h"
#include "Character.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Enemy class designed for players to be able to encounter in rooms and defeat. Will
* also attack players in encounters. Inherits from the Character class
* --------------------------------------------------------------------------------------
*/
class Enemy : public Character
{
public:
	Enemy(string _name, int maxHealth, Weapon _baseWeapon);
};

#endif // Enemy_H

