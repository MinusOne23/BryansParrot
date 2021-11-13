#pragma once
#ifndef ENEMY_ENCOUNTER_H
#define ENEMY_ENCOUNTER_H

#include <map>
#include <set>

#include "Player.h"
#include "Enemy.h"

using namespace std;

class Room;

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
		RETREAT,	// Player Retreated
		NONE,		// Not started
	};

	struct EncounterResult
	{
		bool encounterComplete = false;	// Whether or not player completed the encounter
		string tpRoomName = "";			// Only set if tp
	};

	EnemyEncounter();

	//void enemyTurn(Player& player, bool dodge, int ExtraDodgeTurn);
	EncounterResult startEncounter(Player& player);
	bool attackEnemy(Player& player, const string& attackName, const string& enemyName, bool useStamina = true);
	bool killEnemy(const string& enemyName);
	bool studyEnemy(const string& enemyName) const;
	bool dodgeEnemy(const Player& player, const Enemy& enemy);
	bool enemyExists(const string& enemyName) const;

	vector<shared_ptr<Item>> removeDrops();
	void addDrop(shared_ptr<Item> item);

	void addEnemy(Enemy enemy);
	void setLastRoom(Room* room);
	Room* getLastRoom();

	EncounterState getCurrentState() const;

	void displayNextTurns(const Player& player, int numTurns = 3) const;
	void displayEnemies() const;
	void displayPlayerOptions() const;
	void displaySummary(const Player& player) const;

private:
	static const int TURN_TIME;

	int getEnemyIndex(const string& enemyName) const;
	int getDodgeIndex(const string& enemyName) const;
	void displayAttack(const Character& attacker, const Character& target, const AttackMove::DamageResult& damageResult, bool dodgeAttempted = false, bool dodgeSuccess = false) const;
	void displayTurnStart(const Character& curChar) const;
	void displayDodgeAttempts() const;
	void enemyTurn(Enemy& enemy, Player& player);
	void playerTurn(Player& player, EncounterResult& result);

	void tick(Player& player, EncounterResult& result);

	const static vector<string> playerOptions;

	vector<Enemy> enemies;
	vector<shared_ptr<Item>> drops;
	EncounterState currentState;
	Room* lastRoom;

	int currentTurn = 0;
	int playerTime = 0;
	vector<int> enemyTimes;

	vector<string> playerDodges;
};

#endif // ENEMY_ENCOUNTER_H