
#include <iostream>

#include "EnemyEncounter.h"
#include "Utils.h"


const map<string, EnemyEncounter::EncounterAction> EnemyEncounter::encounterActions = {
	{"kill", EnemyEncounter::EncounterAction::KILL},
	{"attack", EnemyEncounter::EncounterAction::ATTACK},
	{"study", EnemyEncounter::EncounterAction::STUDY},
	{"retreat", EnemyEncounter::EncounterAction::RETREAT}
};

EnemyEncounter::EnemyEncounter(Player& _player, vector<Enemy*>& _enemies)
	: player(_player), enemies(_enemies) {}

EnemyEncounter::EncounterResult EnemyEncounter::begin()
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
		return EnemyEncounter::EncounterResult::RETREAT;

	return EnemyEncounter::EncounterResult::WIN;
}
