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

	enum class EncounterState
	{
		RETREAT,	// Player retreated from the encounter
		WIN,		// Player won the encounter
		LOSE,		// Player lost the encounter
		CONTINUE,	// Still in combat
		NONE		// No encounter
	};

	enum class EncounterAction
	{
		ERROR = -1,
		KILL,
		ATTACK,
		STUDY,
		RETREAT,
		QUIT
	};

	const static map<string, EncounterAction> encounterActions;
	const static vector<string> playerOptions;

	EnemyEncounter(Player& _player, vector<Enemy*>& _enemies);
	EncounterState begin();

private:
	void displayOptions();

	vector<Enemy*>& enemies;
	Player& player;
	EncounterState currentState;
};

#endif // ENEMY_ENCOUNTER_H