#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <map>

using namespace std;

class Interaction
{
public:

	enum class ActionType
	{
		ERROR = -1,
		QUIT,
		INVENTORY,
		TAKE,
		USE,
		OPEN,
		DROP,
		UNLOCK,
		ATTACK,
		LOOK,
		CHARACTER,
		EQUIP,
		HELP,
		RETREAT,
		STUDY,
		KILL
	};

	struct InteractionResult
	{
		ActionType actionType;
		string objectName;
		string actionStr;
		bool isActiveAction;
	};

	static string getHelpText(string action);
	static InteractionResult parseInput(const string& input);

private:
	static const int MAX_ACTION_WORDS;

	Interaction();
	static const map<string, ActionType> actions;
	static const map<ActionType, string> helpStrings;
	static const map<ActionType, bool> isActiveActions;
};

#endif // INTERACTION_H