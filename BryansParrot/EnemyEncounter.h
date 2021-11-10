#pragma once
#ifndef ENEMY_ENCOUNTER_H
#define ENEMY_ENCOUNTER_H

#include <map>
#include <set>

#include "Player.h"
#include "Enemy.h"
#include "Interaction.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Enemy Encounter class to hold all information about an enemy encounter within a room
* and handle all logic based around those encounters, i.e attacking the enemies,
* studying the enemies, drops from the encounter
*
* --------------------------------------------------------------------------------------
* Enums and Structures
* --------------------------------------------------------------------------------------
* EncounterState:
*	All possible states that the encounter can currently be in
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* canUseAction(ActionType actionType)
*	returns whether or not the actionType is within the useableActions vector
* 
* startEncounter()
*	attempts to begin the encounter. If player chooses to retreat instead of enter the
*	encounter, will return false. Otherwise returns true
* 
* attackEnemy(Player player, string enemyName)
*	attempts to attack the enemy with the name enemyName using the player's current
*	damage stats. If enemy is not found returns false, else true
* 
* killEnemy(string enemyName)
*	attempts to kill the enemy with the name enemyName. If enemy is not found returns
*	false, else true
* 
* studyEnemy(string enemyName)
*	attempts to study the enemy with the name enemyName. If enemy is not found returns
*	false, else true
* 
* enemyTurn(Player player)
*	handles the logic for the enemy's turn - has each enemy in the room attack the
*	player based off of their individual stats
* 
* removeDrops()
*	returns the drops from the encounter and removes them from the list
* 
* displayEnemies()
*	displays all enemies in the encounter as a list to the player
*
* getEnemyIndex(string enemyName)
*	attempts to find the enemy with the given name, if not found returns -1, else
*	returns the index of the enemy within the enemies vector
* 
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* useableActions
*	all actionTypes that the player can use while within an enemy encounter
*
* enemies
*	all the enmies that are within the encounter
* 
* drops
*	all items to be dropped after the player completes the encounter
* 
* currentState
*	current state of the encounter
* 
* lastRoom
*	the previous room that can be retreated to by the player currently in the encounter
* --------------------------------------------------------------------------------------
*/
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

	static bool canUseAction(Interaction::ActionType actionType);

	bool startEncounter();
	bool attackEnemy(const Player& player, Weapon::AttackType attackType, const string& enemyName);
	bool dodgeEnemy(const Player& player, const string& enemyName);
	bool killEnemy(const string& enemyName);
	bool studyEnemy(const string& enemyName) const;
	bool enemyExists(const string& enemyName) const;
	void enemyTurn(Player& player, bool dodge, int ExtraDodgeTurn);

	vector<shared_ptr<Item>> removeDrops();
	void addDrop(shared_ptr<Item> item);

	void addEnemy(Enemy enemy);
	void setLastRoom(Room* room);
	Room* getLastRoom();

	EncounterState getCurrentState() const;

	void displayEnemies() const;

private:
	int getEnemyIndex(const string& enemyName) const;
	static const set<Interaction::ActionType> useableActions;


	vector<Enemy> enemies;
	vector<shared_ptr<Item>> drops;
	EncounterState currentState;
	Room* lastRoom;

};

#endif // ENEMY_ENCOUNTER_H