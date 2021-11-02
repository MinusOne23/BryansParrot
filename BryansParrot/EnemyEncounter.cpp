
#include <iostream>

#include "EnemyEncounter.h"
#include "Utils.h"

const map<string, EnemyEncounter::EncounterAction> EnemyEncounter::encounterActions = {
	{"kill", EnemyEncounter::EncounterAction::KILL},
	{"attack", EnemyEncounter::EncounterAction::ATTACK},
	{"study", EnemyEncounter::EncounterAction::STUDY},
	{"retreat", EnemyEncounter::EncounterAction::RETREAT},
	{"quit", EnemyEncounter::EncounterAction::QUIT},
	{"q", EnemyEncounter::EncounterAction::QUIT}
};

const vector<string> EnemyEncounter::playerOptions = {
	"Kill: Kills the enemy",
	"Attack: Damages the enemy based off weapon stats",
	"Study: Displays the enemy stats",
	"Retreat: Retreats to the previous room"
};

EnemyEncounter::EnemyEncounter(Player& _player, vector<Enemy*>& _enemies)
	: player(_player), enemies(_enemies), currentState(EnemyEncounter::EncounterState::NONE) {}

EnemyEncounter::EncounterState EnemyEncounter::begin()
{
	cout << "You have encountered " << enemies.size() << " enem" << (enemies.size() > 1 ? "ies." : "y.") << endl;
	cout << "Would you like to retreat or enter the encounter?" << endl;

	string input = Utils::inputValidator();

	while (input != "retreat" && input != "enter")
	{
		cout << "Please type either retreat or enter" << endl;
		input = Utils::inputValidator();
	}

	if (input == "retreat")
		return EncounterState::RETREAT;

	currentState = EncounterState::CONTINUE;

	while (currentState == EncounterState::CONTINUE)
	{
		system("CLS");
		cout << "\nEnemies:" << endl;

		for (Enemy* enemy : enemies)
		{
			cout << "\t - " << enemy->getName() << endl;
		}

		cout << "Player's turn:" << endl;
		displayOptions();

		input = Utils::inputValidator();

		Utils::ActionResult inputResult = Utils::actionChecker(encounterActions, input);

		cout << inputResult.actionStr << endl;

		system("pause");
	}

}

void EnemyEncounter::displayOptions()
{
	for (string option : playerOptions)
	{
		cout << "\t - " << option << endl;
	}
}
