#pragma once
#ifndef ENEMY_ENCOUNTER_H
#define ENEMY_ENCOUNTER_H

#include <map>
#include <set>

#include "Player.h"
#include "Enemy.h"
#include "Interaction.h"

using namespace std;

class EnemyEncounter
{
public:
	enum class EncounterState
	{	
		WIN,		// Player won the encounter
		LOSE,		// Player lost the encounter
		ACTIVE,		// Still in combat
		NONE		// Not started
	};

	EnemyEncounter();

	const static vector<string> playerOptions;

	static bool canUseAction(Interaction::ActionType actionType);

	bool startEncounter();
	bool attackEnemy(const Player& player, const string& enemyName);
	bool killEnemy(const string& enemyName);
	bool studyEnemy(const string& enemyName) const;

	vector<shared_ptr<Item>> removeDrops();
	void addDrop(shared_ptr<Item> item);

	void addEnemy(Enemy enemy);

	EncounterState getCurrentState() const;

private:
	static const set<Interaction::ActionType> useableActions;

	int getEnemyIndex(const string& enemyName) const;
	void displayOptions() const;

	vector<Enemy> enemies;
	vector<shared_ptr<Item>> drops;
	EncounterState currentState;

};

#endif // ENEMY_ENCOUNTER_H