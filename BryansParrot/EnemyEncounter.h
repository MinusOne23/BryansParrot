#pragma once
#ifndef ENEMY_ENCOUNTER_H
#define ENEMY_ENCOUNTER_H

#include <map>

#include "Player.h"
#include "Enemy.h"

using namespace std;

class EnemyEncounter
{
public:

	enum class EncounterResult
	{
		RETREAT,	// Player retreated from the encounter
		WIN,		// Player won the encounter
		LOSE,		// Player lost the encounter
		NONE		// No encounter
	};

	enum class EncounterAction
	{
		KILL,
		ATTACK,
		STUDY,
		RETREAT
	};

	const static map<string, EncounterAction> encounterActions;

	EnemyEncounter(Player& _player, vector<Enemy*>& _enemies);
	EncounterResult begin();

private:
	vector<Enemy*>& enemies;
	Player& player;
};

#endif // ENEMY_ENCOUNTER_H