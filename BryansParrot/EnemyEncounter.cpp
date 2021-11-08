
#include <iostream>

#include "EnemyEncounter.h"
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
	Interaction::ActionType::LOOK
};


const set<Interaction::DevActionType> EnemyEncounter::useableDevActions = {
	Interaction::DevActionType::KILL,
	Interaction::DevActionType::TP
};

EnemyEncounter::EnemyEncounter()
	: currentState(EncounterState::NONE), lastRoom(nullptr) {}

bool EnemyEncounter::canUseAction(Interaction::ActionType actionType)
{
	return useableActions.find(actionType) != useableActions.end();
}

bool EnemyEncounter::canUseDevAction(Interaction::DevActionType devActionType)
{
	return useableDevActions.find(devActionType) != useableDevActions.end();
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

bool EnemyEncounter::attackEnemy(const Player& player, Weapon::AttackType attackType, const string& enemyName)
{
	if (currentState != EncounterState::ACTIVE)
		return false;

	int index = getEnemyIndex(enemyName);

	if (index == -1)
	{
		cout << "That enemy does not exist" << endl;
		return false;
	}

	cout << "\t==============================================" << endl;
	cout <<"\t\t"<< player.getName() << "'s Turn" << endl;
	cout << "\t----------------------------------------------" << endl;

	Enemy& enemy = enemies[index];

	Weapon::DamageResult damageResult = player.calcDamage(attackType);

	if (!damageResult.isHit)
	{
		cout << "\t\tYour attack missed!" << endl;
	}
	else
	{
		if (damageResult.critical)
			cout << "\t\tCritical Hit!" << endl;

		enemy.damage(damageResult.damage);

		if (enemy.isDead())
		{
			cout << "\t\tYour Attack Hit!" << endl;
			cout << "\t\tYou killed " << enemy.getName() << endl;

			enemies.erase(enemies.begin() + index);

			if (enemies.size() == 0)
			{
				currentState = EncounterState::WIN;
			}
		}
		else
		{
			cout << "\t\tYour Attack Hit!" << endl;
			cout << "\t\tYou dealt " << damageResult.damage << " damage to " << enemy.getName() << endl;
		}
	}

	cout << "\t==============================================" << endl;

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
		cout << "\t==============================================" << endl;
		cout << "\t        " << enemy.getName() << "'s Turn" << endl;
		cout << "\t----------------------------------------------" << endl;


		Weapon::AttackType type = (Weapon::AttackType)(rand() % 2 + 1);

		Weapon::DamageResult damageResult = enemy.calcDamage(type);

		switch (type)
		{
		case Weapon::AttackType::LIGHT:

			cout << "\t\t" <<enemy.getName() << " used a light attack!" << endl;
			break;
		case Weapon::AttackType::HEAVY:
			cout << "\t\t" <<enemy.getName() << " used a heavy attack!" << endl;
			break;
		}
		
		if (!damageResult.isHit)
		{
			cout <<"\t\t"<< enemy.getName() << "'s attack missed!" << endl;
		}
		else
		{
			if (damageResult.critical)
			{
				cout << "\t\tCritical Hit!" << endl;
			}

			cout <<"\t\t" << enemy.getName() << " dealt " << damageResult.damage << " damage to " << player.getName() << endl;

			player.damage(damageResult.damage);
		}

		cout << "\t==============================================" << endl;

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
	cout << "\t==============================================";
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
