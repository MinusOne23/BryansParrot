#include <iostream>

#include "Interaction.h"
#include "Utils.h"

struct ActionInfo
{
	bool useInRoom = false;
	bool useInEncounter = false;
	string helpString = "";
};

const int Interaction::MAX_ACTION_WORDS = 2;
const string Interaction::DEV_MODE = "bryan";

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
	{"end turn", ActionType::END_TURN},
	{"study", ActionType::STUDY},
	{DEV_MODE, ActionType::ENABLE_DEV_MODE}
};

 map<string, Interaction::DevActionType> Interaction::devActions = {
	{"kill", DevActionType::KILL},
	{"tp", DevActionType::TP}
};

const map<Interaction::ActionType, ActionInfo> actionInfoMap = {
	//										room	encounter	helpString
	//Universal
	{Interaction::ActionType::INVENTORY,	{true,	true,		"Displays Inventory"}},
	{Interaction::ActionType::USE,			{true,	true,		"Use the specified item from the inventory"}},
	{Interaction::ActionType::CHARACTER,	{true,	true,		"Displays the player stats"}},
	{Interaction::ActionType::EQUIP,		{true,	true,		"Equips the specified piece of equipment from the inventory"}},
	{Interaction::ActionType::DRINK,		{true,	true,		"Drink the specified item from the player's inventory"}},
	{Interaction::ActionType::ERROR,		{true,	true,		""}},
	{Interaction::ActionType::QUIT,			{true,	true,		""}},
	{Interaction::ActionType::HELP,			{true,	true,		""}},

	//Room Specific
	{Interaction::ActionType::TAKE,			{true,	false,		"Takes the specified item in the room"}},
	{Interaction::ActionType::OPEN,			{true,	false,		"Opens the specified container/door"}},
	{Interaction::ActionType::DROP,			{true,	false,		"Drop the specified item from the inventory into the room"}},
	{Interaction::ActionType::UNLOCK,		{true,	false,		"Unlocks the specified container/door"}},
	{Interaction::ActionType::LOOK,			{true,	false,		"Displays the contents of the room"}},

	//Encounter Specific
	{Interaction::ActionType::ATTACK,		{false,	true,		"Attack the specified enemy in the room"}},
	{Interaction::ActionType::RETREAT,		{false,	true,		"Retreat from the current encounter"}},
	{Interaction::ActionType::STUDY,		{false,	true,		"Display the enemy stats"}},
	{Interaction::ActionType::KILL,			{false,	true,		"Kill the enemy"}},
	{Interaction::ActionType::END_TURN,		{false,	true,		""}}
};

set<string> Interaction::actionsUsed;

bool Interaction::canUseInRoom(ActionType type)
{
	if (actionInfoMap.find(type) == actionInfoMap.end())
	{
		return false;
	}

	ActionInfo info = actionInfoMap.at(type);
	return info.useInRoom;
}

bool Interaction::canUseInEncounter(ActionType type)
{
	if (actionInfoMap.find(type) == actionInfoMap.end())
	{
		return false;
	}

	ActionInfo info = actionInfoMap.at(type);
	return info.useInEncounter;
}

string Interaction::getHelpText(string action)
{
	string lowerAct = Utils::strToLower(action);

	if (actions.find(lowerAct) != actions.end())
	{
		ActionType type = actions.at(lowerAct);
		ActionInfo info;

		if (actionInfoMap.find(type) != actionInfoMap.end())
		{
			return actionInfoMap.at(type).helpString;
		}
	}

	return "";
}

Interaction::InteractionResult Interaction::universalInput(Player& player)
{
	string inputStr = Utils::inputValidator();
	Interaction::InteractionResult inputResult = Interaction::parseInput(inputStr);

	switch (inputResult.actionType)
	{
	case ActionType::QUIT:
	{
		exit(0);
	}
	case ActionType::INVENTORY:
	{
		player.displayInventory();
		break;
	}
  case Interaction::ActionType::ENABLE_DEV_MODE:
	{
		isDevMode = !isDevMode;

		if (isDevMode)
			cout << "DevMode: Activated" << endl;
		else
			cout << "DevMode: Deactivated" << endl;

		return;
	}
	case ActionType::EQUIP:
	{
		inputResult.succeeded = player.findAndEquip(inputResult.target);
		break;
	}
	case ActionType::CHARACTER:
	{
		player.displayStats();
		break;
	}
	case ActionType::USE:
	{
		inputResult.succeeded = player.useItem(inputResult.target);
		break;
	}
	case ActionType::DRINK:
	{
		inputResult.succeeded = player.findAndDrink(inputResult.target);
		break;
	}
	case ActionType::HELP:
	{
		helperDisplay();
		break;
	}
	case ActionType::ERROR:
	{
		cout << "Sorry, that input is not recognized." << endl;
		break;
	}
	}

	if(inputResult.actionType != ActionType::ERROR)
		addActionUsed(inputResult.actionStr);

	cout << endl;

	return inputResult;
}

void Interaction::addActionUsed(string actionStr)
{
	actionsUsed.insert(actionStr);
}

void Interaction::helperDisplay()
{
	cout << "\t===========================================\n";
	cout << "\t\t\tKnownCommands\n";
	cout << "\t-------------------------------------------\n";
	for (string act : actionsUsed)
	{
		string helpStr = Interaction::getHelpText(act);

		if (helpStr != "")
			cout << "\t- " << act << ": " << helpStr << endl;
	}
	cout << "\t===========================================\n";
}

Interaction::InteractionResult Interaction::parseInput(const string& input, bool devMode)
{
	InteractionResult result;

	if (devMode)
		result = parseInputDev(input);
	else
		result.devActionType = DevActionType::ERROR;

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

			result.succeeded = true;

			return result;
		}
	}

	result.actionType = ActionType::ERROR;
	return result;
}

Interaction::InteractionResult Interaction::parseInputDev(const string& input)
{
	InteractionResult result;
	vector<string> tokens = Utils::tokenize(input);

	for (int i = 1; i < tokens.size() + 1 && i <= MAX_ACTION_WORDS; i++)
	{
		string devactionStr = tokens[0];

		for (int j = 1; j < i; j++)
		{
			devactionStr += " " + tokens[j];
		}

		if (devActions.find(devactionStr) != devActions.end())
		{
			result.devActionType = devActions.at(devactionStr);

			if (i < tokens.size())
			{
				result.target = tokens[i];
				for (int j = i + 1; j < tokens.size(); j++)
				{
					result.target += " " + tokens[j];
				}
			}

			result.actionStr = Utils::strToLower(devactionStr);

			if (isActiveDevActions.find(result.devActionType) != isActiveDevActions.end())
				result.isActiveDevAction = isActiveDevActions.at(result.devActionType);

			result.succeeded = true;

			return result;
		}
	}

	result.devActionType = DevActionType::ERROR;
	return result;
}