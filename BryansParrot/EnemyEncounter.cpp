
#include <iostream>

#include "EnemyEncounter.h"
#include "AttackMove.h"
#include "Utils.h"
#include "Interaction.h"
#include "MiniMap.h"

const int EnemyEncounter::TURN_TIME = 100;

const vector<string> EnemyEncounter::playerOptions = {
	"Attack [Enemy Name]",
	"Study [Enemy Name]",
	"Dodge [Enemy Name] - 1 stamina",
	"Block",
	"End Turn",
	"Retreat"
};

EnemyEncounter::EnemyEncounter()
	: currentState(EncounterState::NONE), lastRoom(nullptr) {}

EnemyEncounter::EncounterResult EnemyEncounter::startEncounter(Player& player, MiniMap& miniMap)
{
	//cout << flush;
	system("CLS");
	cout << "\t===================================================" << endl;
	cout << "\t          You have encountered " << enemies.size() << " enem" << (enemies.size() > 1 ? "ies." : "y.") << endl;
	cout << "\t---------------------------------------------------" << endl;
	cout << "\t  Would you like to retreat or enter the encounter?" << endl;
	cout << "\t===================================================" << endl;

	string input = Utils::inputValidator();
	EncounterResult result;

	while (input != "retreat" && input != "enter")
	{
		cout << "Please type either retreat or enter" << endl;
		input = Utils::inputValidator();
	}

	if (input == "retreat")
	{
		cout << "You have retreated to the previous room" << endl;
		result.encounterComplete = false;
		return result;
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
		tick(player, miniMap, result);

		if (player.isDead())
		{
			currentState = EncounterState::LOSE;
			result.encounterComplete = false;
			return result;
		}
	}

	return result;
}

bool EnemyEncounter::attackEnemy(Player& player, const string& attackName, const string& enemyName, bool useStamina)
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

	if (!useStamina)
		damageResult.staminaUsed = 0;

	if (player.getCurrentStamina() < damageResult.staminaUsed)
	{
		cout << "You do not have enough stamina" << endl;
		return false;
	}

	player.useStamina(damageResult.staminaUsed);

	damageResult.damage -= enemy.getDefense();

	if (damageResult.damage < 0)
		damageResult.damage = 0;

	enemy.damage(damageResult.damage);

	displayTurnStart(player);
	displayAttack(player, enemy, damageResult, 0, false, false);

	if (enemy.isDead())
	{
		int dodgeIndex = getDodgeIndex(enemy.getName());

		while (dodgeIndex != -1)
		{
			playerDodges.erase(playerDodges.begin() + dodgeIndex);
			dodgeIndex = getDodgeIndex(enemy.getName());
		}

		enemies.erase(enemies.begin() + index);
		enemyTimes.erase(enemyTimes.begin() + index);

		if (enemies.size() == 0)
			currentState = EncounterState::WIN;
	}

	return true;
}

bool EnemyEncounter::dodgeEnemy(const Player& player, const Enemy& enemy)
{
	return Utils::chanceTest(player.getDodgeChance());
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

	if (playerDodges.size() > 0)
	{
		displayDodgeAttempts();
	}


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

int EnemyEncounter::getDodgeIndex(const string& enemyName) const
{
	for (int i = 0; i < playerDodges.size(); i++)
	{
		if (Utils::equalsCI(enemyName, playerDodges[i]))
			return i;
	}

	return -1;
}

void EnemyEncounter::displayTurnStart(const Character& curChar) const
{
	cout << "\t==============================================" << endl;
	cout << "\t        " << curChar.getName() << "'s Turn" << endl;
	cout << "\t----------------------------------------------" << endl;
}

void EnemyEncounter::displayDodgeAttempts() const
{
	cout << endl;
	cout << "\t==============================================" << endl;
	cout << "\t           Pending Dodge Attempts:" << endl;
	cout << "\t==============================================" << endl;

	for (int i = 0; i < playerDodges.size(); i++)
	{
		cout << "\t - " << playerDodges[i] << endl;
	}

	cout << "\t==============================================" << endl;
}

void EnemyEncounter::enemyTurn(Enemy& enemy, Player& player, bool shouldBlock)
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
		bool dodge = false;
		int dodgeIndex = -1;

		if (!shouldBlock)
		{
			dodgeIndex = getDodgeIndex(enemy.getName());

			if (dodgeIndex != -1)
			{
				dodge = dodgeEnemy(player, enemy);
				playerDodges.erase(playerDodges.begin() + dodgeIndex);
			}
		}

		AttackMove::DamageResult damageResult = enemy.calcDamage(attack);
		enemy.useStamina(damageResult.staminaUsed);

		if (!dodge)
		{
			int blockAmt = 0;

			if (shouldBlock)
			{
				if (blockLeft >= damageResult.damage)
				{
					blockAmt = damageResult.damage;
				}
				else
				{
					blockAmt = blockLeft;
				}

				blockLeft -= blockAmt;
				damageResult.damage -= blockAmt;
			}

			damageResult.damage -= player.getDefense();

			if (damageResult.damage < 0)
				damageResult.damage = 0;

			player.damage(damageResult.damage);
			displayAttack(enemy, player, damageResult, blockAmt, dodgeIndex != -1, dodge);

			if (player.isDead())
			{
				system("pause");
				system("CLS");
				currentState = EncounterState::LOSE;
				return;
			}
		}
		else
		{
			displayAttack(enemy, player, damageResult, 0, dodgeIndex != -1, dodge);
			
			cout << "\n\tYou can now counter the attack!" << endl;

			Weapon activeWeapon = player.getActiveWeapon();

			cout << "\t===========================================\n";
			cout << "\t\tAttack Types:" << endl;
			cout << "\t------------------------------------------\n";

			cout << activeWeapon.attacksDisplay("\t - ");

			cout << "\t===========================================\n";

			string input = Utils::inputValidator();

			while (!activeWeapon.hasAttackMove(input))
			{
				cout << "That move does not exist" << endl;
				input = Utils::inputValidator();
			}

			int enemyCount = enemies.size();

			system("CLS");
			attackEnemy(player, input, enemy.getName(), false);
			system("pause");
			system("CLS");

			if (enemies.size() < enemyCount)
			{
				return;
			}

			displayTurnStart(enemy);
		}

		attack = enemy.getRandomAttack();
	}

	system("pause");
	system("CLS");
}

void EnemyEncounter::playerTurn(Player& player, MiniMap& miniMap, EncounterResult& result)
{
	bool endTurn = false;
	isBlocking = false;
	blockLeft = 0;

	while (!endTurn)
	{
		if (currentState != EncounterState::ACTIVE)
		{
			return;
		}

		displaySummary(player);

		Interaction::InteractionResult inputResult = Interaction::universalInput(player, miniMap);

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

			cout << activeWeapon.attacksDisplay("\t - ");

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
		case Interaction::ActionType::BLOCK:
		{
			shared_ptr<Shield> shieldPtr = player.getShield();

			if (shieldPtr == nullptr)
			{
				cout << "You must have a shield equipped to block" << endl;
				inputResult.succeeded = false;
				break;
			}

			Shield shield = *shieldPtr;

			cout << "\t===========================================\n";
			cout << "\t\Block Types:" << endl;
			cout << "\t------------------------------------------\n";

			cout << shield.blocksDisplay("\t - ");

			cout << "\t - Cancel" << endl;
			cout << "\t===========================================\n";

			string input = Utils::inputValidator();

			Shield::BlockType blockType = shield.blockTypeFromStr(input);

			while (!Utils::equalsCI(input, "cancel") && blockType == Shield::BlockType::ERROR)
			{
				cout << "That move does not exist" << endl;
				input = Utils::inputValidator();
				blockType = shield.blockTypeFromStr(input);
			}

			if (Utils::equalsCI(input, "cancel"))
			{
				cout << "You've canceled your Block" << endl;
				inputResult.succeeded = false;
				break;
			}

			if (player.getCurrentStamina() < shield.getStaminaRequied(blockType))
			{
				cout << "You do not have enough stamina" << endl;
				inputResult.succeeded = false;
				break;
			}

			isBlocking = true;
			blockLeft = shield.calcBlockAmt(blockType);

			switch (blockType)
			{
			case Shield::BlockType::SINGLE:
			{
				cout << "Which enemy would you like to block?" << endl;
				int enemyIndex = getEnemyIndex(Utils::inputValidator());

				while (enemyIndex == -1)
				{
					cout << "That enemy does not exist, please try again" << endl;
					enemyIndex = getEnemyIndex(Utils::inputValidator());
				}

				blockTargetIndex = enemyIndex;
				break;
			}
			case Shield::BlockType::GROUP:
			{
				blockTargetIndex = -1;
				break;
			}
			}

			cout << "You are now blocking for " << blockLeft << " damage" << endl;

			endTurn = true;
			break;
		}
		case Interaction::ActionType::DODGE:
		{
			if (player.getCurrentStamina() < 1)
			{
				inputResult.succeeded = false;
				cout << "You need at least 1 stamina to dodge" << endl;
			}
			else
			{
				int index = getEnemyIndex(inputResult.target);

				if (index != -1)
				{
					playerDodges.push_back(enemies[index].getName());
					inputResult.succeeded = true;
					player.useStamina(1);
				}
				else
				{
					cout << "That enemy does not exist" << endl;
					inputResult.succeeded = false;
				}
			}
			break;
		}
		case Interaction::ActionType::RETREAT:
		{
			currentState = EncounterState::RETREAT;
			result.encounterComplete = false;
			break;
		}
		case Interaction::ActionType::END_TURN:
		{
			endTurn = true;
			player.refreshStamina();
			break;
		}
		case Interaction::ActionType::TP:
		{
			if (inputResult.succeeded)
			{
				currentState = EncounterState::RETREAT;
				result.encounterComplete = false;
				result.tpRoomName = inputResult.tpRoomName;
			}
		}
		}

		system("pause");
		system("CLS");
	}
}

void EnemyEncounter::tick(Player& player, MiniMap& miniMap, EncounterResult& result)
{
	playerTime += player.getSpeed();

	if (playerTime >= TURN_TIME)
	{
		currentTurn = -1;
		player.refreshStamina();
		playerTurn(player, miniMap, result);
		playerTime -= TURN_TIME;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemyTimes[i] += enemies[i].getSpeed();

		if (enemyTimes[i] >= TURN_TIME)
		{
			bool shouldBlock = isBlocking && (blockTargetIndex == -1 || blockTargetIndex == i) && blockLeft > 0;

			currentTurn = i;

			int enemyCount = enemies.size();
			enemyTurn(enemies[i], player, shouldBlock);

			int diff = enemyCount - enemies.size();
			i -= diff;

			if(diff == 0)
				enemyTimes[i] -= TURN_TIME;

			if (player.isDead())
				return;
		}
	}

	if (currentState == EncounterState::WIN)
	{
		result.encounterComplete = true;
		player.refreshStamina();
	}
}

void EnemyEncounter::displayAttack(const Character& attacker, const Character& target, const AttackMove::DamageResult& damageResult, int blockAmt, bool dodgeAttempted, bool dodgeSuccess) const
{
	cout << "\t\t" << attacker.getName() << " used " << damageResult.attackName << "!" << endl;

	if(dodgeAttempted)
	{
		if(dodgeSuccess)
			cout << "\t\t" << target.getName() << " successfully dodged the attack!" << endl;
		else
			cout << "\t\t" << target.getName() << " failed to dodge the attack!" << endl;
	}

	if (!dodgeAttempted || dodgeAttempted && !dodgeSuccess)
	{
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

			if (blockAmt > 0)
			{
				cout << "\t\t" << target.getName() << " blocked " << blockAmt << " damage!" << endl;
			}

			cout << "\t\t" << attacker.getName() << " dealt " << damageResult.damage << " damage to " << target.getName() << endl;
		}
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
