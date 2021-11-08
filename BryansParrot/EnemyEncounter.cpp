
#include <iostream>

#include "EnemyEncounter.h"
#include "AttackMove.h"
#include "Utils.h"

const set<Interaction::ActionType> EnemyEncounter::useableActions = {
	Interaction::ActionType::QUIT,
	Interaction::ActionType::INVENTORY,
	Interaction::ActionType::USE,
	Interaction::ActionType::ATTACK,
	Interaction::ActionType::CHARACTER,
	Interaction::ActionType::EQUIP,
	Interaction::ActionType::HELP,
	Interaction::ActionType::RETREAT,
	Interaction::ActionType::STUDY,
	Interaction::ActionType::KILL,
	Interaction::ActionType::LOOK,
	Interaction::ActionType::ERROR,
	Interaction::ActionType::END_TURN
};

const vector<string> EnemyEncounter::playerOptions = {
	"Attack [Enemy Name]",
	"Study [Enemy Name]",
	"End Turn",
	"Retreat"
};

EnemyEncounter::EnemyEncounter()
	: currentState(EncounterState::NONE), lastRoom(nullptr) {}

bool EnemyEncounter::canUseAction(Interaction::ActionType actionType)
{
	return useableActions.find(actionType) != useableActions.end();
}

bool EnemyEncounter::startEncounter()
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
		return false;
	
	currentState = EncounterState::ACTIVE;
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

	displayAttack(player, enemy, damageResult);

	if (enemy.isDead())
	{
		enemies.erase(enemies.begin() + index);

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

void EnemyEncounter::enemyTurn(Player& player)
{
	for (Enemy& enemy : enemies)
	{
		AttackMove::DamageResult damageResult = enemy.calcDamage(enemy.getRandomAttack());
		player.damage(damageResult.damage);

		displayAttack(enemy, player, damageResult);

		if (player.isDead())
			return;
	}
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

void EnemyEncounter::displayAttack(const Character& attacker, const Character& target, const AttackMove::DamageResult& damageResult)
{
	cout << "\t==============================================" << endl;
	cout << "\t        " << attacker.getName() << "'s Turn" << endl;
	cout << "\t----------------------------------------------" << endl;

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

	if (target.isDead())
	{
		cout << "\t\t" << target.getName() << " died!" << endl;
	}

	cout << "\t==============================================" << endl;
}
