#include "Interaction.h"
#include "Utils.h"

const int Interaction::MAX_ACTION_WORDS = 2;

const map<string, Interaction::ActionType> Interaction::actions = {
	{"q", ActionType::QUIT},
	{"i", ActionType::INVENTORY},
	{"inventory", ActionType::INVENTORY},
	{"take", ActionType::TAKE},
	{"grab", ActionType::TAKE},
	{"pick up", ActionType::TAKE},
	{"open", ActionType::OPEN},
	{"unlock", ActionType::UNLOCK},
	{"l", ActionType::LOOK},
	{"look", ActionType::LOOK},
	{"h", ActionType::HELP},
	{"help", ActionType::HELP},
	{"use", ActionType::USE},
	{"drink", ActionType::DRINK},
	{"drop", ActionType::DROP},
	{"c", ActionType::CHARACTER},
	{"character", ActionType::CHARACTER},
	{"equip", ActionType::EQUIP},
	{"attack", ActionType::ATTACK},
	{"retreat", ActionType::RETREAT},
	{"study", ActionType::STUDY},
	{"kill", ActionType::KILL}
};

const map<Interaction::ActionType, string> Interaction::helpStrings = {
	{ActionType::INVENTORY, "Displays Inventory"},
	{ActionType::TAKE, "Takes the specified item in the room"},
	{ActionType::USE, "Use the specified item from the inventory"},
	{ActionType::OPEN, "Opens the specified container/door"},
	{ActionType::DROP, "Drop the specified item from the inventory into the room"},
	{ActionType::UNLOCK, "Unlocks the specified container/door"},
	{ActionType::ATTACK, "Attack the specified enemy in the room"},
	{ActionType::LOOK, "Displays the contents of the room"},
	{ActionType::CHARACTER, "Displays the player stats"},
	{ActionType::EQUIP, "Equips the specified piece of equipment from the inventory"},
	{ActionType::RETREAT, "Retreat from the current encounter"},
	{ActionType::STUDY, "Display the enemy stats"},
	{ActionType::KILL, "Kill the enemy"},
	{ActionType::DRINK, "Drink the specified item from the player's inventory"}
};

const map<Interaction::ActionType, bool> Interaction::isActiveActions = {
	{ActionType::INVENTORY, false},
	{ActionType::TAKE, true},
	{ActionType::USE, true},
	{ActionType::OPEN, true},
	{ActionType::DROP, true},
	{ActionType::UNLOCK, true},
	{ActionType::ATTACK, true},
	{ActionType::LOOK, false},
	{ActionType::CHARACTER, false},
	{ActionType::EQUIP, true},
	{ActionType::HELP, false},
	{ActionType::RETREAT, true},
	{ActionType::STUDY, false},
	{ActionType::KILL, true},
	{ActionType::DRINK, true}
};

string Interaction::getHelpText(string action)
{
	string lowerAct = Utils::strToLower(action);

	if (actions.find(lowerAct) != actions.end())
	{
		ActionType type = actions.at(lowerAct);

		if (helpStrings.find(type) != helpStrings.end())
		{
			return helpStrings.at(type);
		}
	}

	return "";
}

Interaction::InteractionResult Interaction::parseInput(const string& input)
{
	InteractionResult result;
	vector<string> tokens = Utils::tokenize(input);

	for (int i = 1; i < tokens.size() + 1 && i <= MAX_ACTION_WORDS; i++)
	{
		string actionStr = tokens[0];

		for (int j = 1; j < i; j++)
		{
			actionStr += " " + tokens[j];
		}

		if (actions.find(actionStr) != actions.end())
		{
			result.actionType = actions.at(actionStr);

			if (i < tokens.size())
			{
				result.target = tokens[i];
				for (int j = i + 1; j < tokens.size(); j++)
				{
					result.target += " " + tokens[j];
				}
			}

			result.actionStr = Utils::strToLower(actionStr);

			if (isActiveActions.find(result.actionType) != isActiveActions.end())
				result.isActiveAction = isActiveActions.at(result.actionType);

			result.succeeded = true;

			return result;
		}
	}

	result.actionType = ActionType::ERROR;
	return result;
}