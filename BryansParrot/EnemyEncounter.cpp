
#include <iostream>

#include "EnemyEncounter.h"
#include "AttackMove.h"
#include "Utils.h"

const int EnemyEncounter::TURN_TIME = 100;

const vector<string> EnemyEncounter::playerOptions = {
	"Attack [Enemy Name]",
	"Study [Enemy Name]",
	"End Turn",
	"Retreat"
};


const set<Interaction::DevActionType> EnemyEncounter::useableDevActions = {
	Interaction::DevActionType::KILL,
	Interaction::DevActionType::TP
};

EnemyEncounter::EnemyEncounter()
	: currentState(EncounterState::NONE), lastRoom(nullptr) {}

bool EnemyEncounter::startEncounter(Player& player)
{
	//cout << flush;
	system("CLS");
	cout << "\t===================================================" << endl;
	cout << "\t          You have encountered " << enemies.size() << " enem" << (enemies.size() > 1 ? "ies." : "y.") << endl;
	cout << "\t---------------------------------------------------" << endl;
	cout << "\t  Would you like to retreat or enter the encounter?" << endl;
	cout << "\t===================================================" << endl;

	string input = Utils::inputValidator();

	while (input != "retreat" && input != "enter")
	{
		cout << "Please type either retreat or enter" << endl;
		input = Utils::inputValidator();
	}

	if (input == "retreat")
	{
		cout << "You have reteated to the previous room" << endl;
		return false;
	}

	system("CLS");

	if (enemyTimes.size() == 0)
	{
		for (int i = 0; i < enemies.size(); i++)
			enemyTimes.push_back(0);
	}

	currentState = EncounterState::ACTIVE;

	while (currentState == EncounterState::ACTIVE)
	{
		tick(player);
	}

	if (currentState == EncounterState::RETREAT || currentState == EncounterState::LOSE)
		return false;

	return true;
}

bool EnemyEncounter::attackEnemy(Player& player, const string& attackName, const string& enemyName)
{
	if (currentState != EncounterState::ACTIVE)
		return false;

	int index = getEnemyIndex(enemyName);

	if (index == -1)
	{
		cout << "That enemy does not exist" << endl;
		return false;
	}

	Enemy& enemy = enemies[index];
	AttackMove::DamageResult damageResult = player.calcDamage(attackName);
	if (player.getCurrentStamina() < damageResult.staminaUsed)
	{
		cout << "You do not have enough stamina" << endl;
		return false;
	}

	player.useStamina(damageResult.staminaUsed);
	enemy.damage(damageResult.damage);

	displayTurnStart(player);
	displayAttack(player, enemy, damageResult);

	if (enemy.isDead())
	{
		enemies.erase(enemies.begin() + index);
		enemyTimes.erase(enemyTimes.begin() + index);

		if (enemies.size() == 0)
			currentState = EncounterState::WIN;
	}
		
	return true;
}

bool EnemyEncounter::killEnemy(const string& enemyName)
{
	if (currentState != EncounterState::ACTIVE)
		return false;

	int index = getEnemyIndex(enemyName);

	if (index == -1)
	{
		cout << "That enemy does not exist" << endl;
		return false;
	}

	Enemy& enemy = enemies[index];

	cout << "You killed " << enemy.getName() << endl;

	enemies.erase(enemies.begin() + index);

	if (enemies.size() == 0)
	{
		currentState = EncounterState::WIN;
	}

	return true;
}

bool EnemyEncounter::studyEnemy(const string& enemyName) const
{
	if (currentState != EncounterState::ACTIVE)
		return false;

	int index = getEnemyIndex(enemyName);

	if (index == -1)
	{
		cout << "That enemy does not exist" << endl;
		return false;
	}

	const Enemy& enemy = enemies[index];

	enemy.displayStats();
	return true;
}

bool EnemyEncounter::enemyExists(const string& enemyName) const
{
	return getEnemyIndex(enemyName) != -1;
}

vector<shared_ptr<Item>> EnemyEncounter::removeDrops()
{
	vector<shared_ptr<Item>> result = drops;
	drops.clear();

	return result;
}

void EnemyEncounter::addDrop(shared_ptr<Item> item)
{
	drops.push_back(item);
}

void EnemyEncounter::addEnemy(Enemy enemy)
{
	enemies.push_back(enemy);
}

void EnemyEncounter::setLastRoom(Room* room)
{
	lastRoom = room;
}

Room* EnemyEncounter::getLastRoom()
{
	return lastRoom;
}

EnemyEncounter::EncounterState EnemyEncounter::getCurrentState() const
{
	return currentState;
}

void EnemyEncounter::displayNextTurns(const Player& player, int numTurns) const
{
	if (numTurns < 1)
		numTurns = 1;

	cout << "\t==============================================\n";
	cout << "\t\t\tUp Next:" << endl;
	cout << "\t----------------------------------------------\n";

	int tempPlayerTime = playerTime;
	vector<int> tempEnemyTimes = enemyTimes;

	int turnCount = 0;

	if (currentTurn != -1)
	{
		tempEnemyTimes[currentTurn] = 0;

		for (int i = currentTurn + 1; i++; i < enemies.size() && turnCount < numTurns)
		{
			tempEnemyTimes[i] += enemies[i].getSpeed();

			if (tempEnemyTimes[i] >= TURN_TIME)
			{
				cout << "\t - " << enemies[i].getName() << endl;
				tempEnemyTimes[i] -= TURN_TIME;
				turnCount++;
			}
		}

		if (turnCount < numTurns)
		{
			tempPlayerTime += player.getSpeed();

			if (tempPlayerTime >= TURN_TIME)
			{
				cout << "\t - " << player.getName() << endl;
				tempPlayerTime -= TURN_TIME;
				turnCount++;
			}
		}
	}
	else
	{
		tempPlayerTime = 0;
	}

	while (turnCount < numTurns)
	{
		for (int i = 0; i < enemies.size() && turnCount < numTurns; i++)
		{
			tempEnemyTimes[i] += enemies[i].getSpeed();

			if (tempEnemyTimes[i] >= TURN_TIME)
			{
				cout << "\t - " << enemies[i].getName() << endl;
				tempEnemyTimes[i] -= TURN_TIME;
				turnCount++;
			}
		}

		if (turnCount < numTurns)
		{
			tempPlayerTime += player.getSpeed();

			if (tempPlayerTime >= TURN_TIME)
			{
				cout << "\t - " << player.getName() << endl;
				tempPlayerTime -= TURN_TIME;
				turnCount++;
			}
		}
	}

	cout << "\t==============================================" << endl;
}

void EnemyEncounter::displayEnemies() const
{
	cout << "\t==============================================\n";
	cout << "\t\t\tEnemies:" << endl;
	cout << "\t----------------------------------------------\n";

	for (Enemy enemy : enemies)
	{
		cout << "\t - " << enemy.getName() << " " << enemy.healthDisplay() << endl;
	}
	cout << "\t==============================================" << endl;
}

void EnemyEncounter::displayPlayerOptions() const
{
	cout << "\t==============================================\n";
	cout << "\t\t\Options:" << endl;
	cout << "\t----------------------------------------------\n";

	for (string option : playerOptions)
	{
		cout << "\t - " << option << endl;
	}
	cout << "\t==============================================" << endl;
}

void EnemyEncounter::displaySummary(const Player& player) const
{
	displayEnemies();
	displayNextTurns(player, 3);

	cout << endl;
	cout << "\t==============================================" << endl;
	cout << "\t - Player Health: " << player.healthDisplay() << endl;
	cout << "\t - Player Stamina: " << player.getCurrentStamina() << endl;
	cout << "\t==============================================" << endl;


	displayPlayerOptions();
}

int EnemyEncounter::getEnemyIndex(const string& enemyName) const
{
	for (int i = 0; i < enemies.size(); i++)
	{
		const Enemy& enemy = enemies[i];

		if (Utils::equalsCI(enemy.getName(), enemyName))
		{
			return i;
		}
	}

	return -1;
}

void EnemyEncounter::displayTurnStart(const Character& curChar) const
{
	cout << "\t==============================================" << endl;
	cout << "\t        " << curChar.getName() << "'s Turn" << endl;
	cout << "\t----------------------------------------------" << endl;
}

void EnemyEncounter::enemyTurn(Enemy& enemy, Player& player)
{
	if (currentState != EncounterState::ACTIVE)
	{
		return;
	}

	enemy.refreshStamina();

	string attack = enemy.getRandomAttack();

	displayTurnStart(enemy);

	while (attack != "")
	{
		AttackMove::DamageResult damageResult = enemy.calcDamage(attack);
		player.damage(damageResult.damage);

		enemy.useStamina(damageResult.staminaUsed);
		attack = enemy.getRandomAttack();

		displayAttack(enemy, player, damageResult);

		if (player.isDead())
		{
			currentState = EncounterState::LOSE;
			return;
		}
	}

	system("pause");
	system("CLS");
}

void EnemyEncounter::playerTurn(Player& player)
{
	bool endTurn = false;

	while (!endTurn)
	{
		if (currentState != EncounterState::ACTIVE)
		{
			return;
		}

		displaySummary(player);

		Interaction::InteractionResult inputResult = Interaction::universalInput(player);

		if (!Interaction::canUseInEncounter(inputResult.actionType))
		{
			cout << "Sorry you can't do that right now" << endl;
			continue;
		}

		switch (inputResult.actionType)
		{
		case Interaction::ActionType::ATTACK:
		{
			if (!enemyExists(inputResult.target))
			{
				cout << "That enemy does not exist" << endl;
				inputResult.succeeded = false;
				break;
			}

			Weapon activeWeapon = player.getActiveWeapon();

			cout << "\t===========================================\n";
			cout << "\t\tAttack Types:" << endl;
			cout << "\t------------------------------------------\n";

			activeWeapon.displayAttacks("\t - ");

			cout << "\t - Cancel" << endl;
			cout << "\t===========================================\n";

			string input = Utils::inputValidator();

			while (!Utils::equalsCI(input, "cancel") && !activeWeapon.hasAttackMove(input))
			{
				cout << "That move does not exist" << endl;
				input = Utils::inputValidator();
			}

			if (Utils::equalsCI(input, "cancel"))
			{
				cout << "You've canceled your Attack" << endl;
				inputResult.succeeded = false;
			}
			else
			{
				system("CLS");
				inputResult.succeeded = attackEnemy(player, input, inputResult.target);
			}

			break;
		}
		case Interaction::ActionType::KILL:
		{
			inputResult.succeeded = killEnemy(inputResult.target);
			break;
		}
		case Interaction::ActionType::STUDY:
		{
			inputResult.succeeded = studyEnemy(inputResult.target);
			break;
		}
		case Interaction::ActionType::RETREAT:
		{
			currentState = EncounterState::RETREAT;
			break;
		}
		case Interaction::ActionType::END_TURN:
		{
			endTurn = true;
			player.refreshStamina();
			break;
		}
		}

		system("pause");
		system("CLS");
	}
}

void EnemyEncounter::tick(Player& player)
{
	playerTime += player.getSpeed();

	if (playerTime >= TURN_TIME)
	{
		currentTurn = -1;
		playerTurn(player);
		playerTime -= TURN_TIME;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemyTimes[i] += enemies[i].getSpeed();

		if (enemyTimes[i] >= TURN_TIME)
		{
			currentTurn = i;
			enemyTurn(enemies[i], player);
			enemyTimes[i] -= TURN_TIME;
		}
	}
}

void EnemyEncounter::displayAttack(const Character& attacker, const Character& target, const AttackMove::DamageResult& damageResult) const
{
	cout << "\t\t" << attacker.getName() << " used " << damageResult.attackName << "!" << endl;

	if (!damageResult.isHit)
	{
		cout << "\t\t" << attacker.getName() << "'s attack missed!" << endl;
	}
	else
	{
		if (damageResult.isCritical)
		{
			cout << "\t\tCritical Hit!" << endl;
		}

		cout << "\t\t" << attacker.getName() << " dealt " << damageResult.damage << " damage to " << target.getName() << endl;
	}

	cout << "\t\tStamina used: " << damageResult.staminaUsed << endl;
	cout << "\t\tStamina remaining: " << attacker.getCurrentStamina() << endl;
	cout << endl;

	if (target.isDead())
	{
		cout << "\t\t" << target.getName() << " died!" << endl;
	}
	else
	{
		cout << "\t\t" << target.getName() << " Health: " << target.healthDisplay() << endl;
	}

	cout << "\t==============================================" << endl;
}
