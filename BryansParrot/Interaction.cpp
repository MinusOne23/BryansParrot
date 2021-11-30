#include <iostream>

#include "Interaction.h"
#include "Utils.h"
#include "DungeonBuilder.h"

struct ActionInfo
{
	bool useInRoom = false;
	bool useInEncounter = false;
	bool isDevAction = false;
	string helpString = "";
};

const int Interaction::MAX_ACTION_WORDS = 2;
const string Interaction::DEV_MODE = "bryan";

const map<string, Interaction::ActionType> Interaction::actions = {
	// Universal
	{"q",			ActionType::QUIT},
	{"quit",		ActionType::QUIT},
	{"i",			ActionType::INVENTORY},
	{"inventory",	ActionType::INVENTORY},
	{"h",			ActionType::HELP},
	{"help",		ActionType::HELP},
	{"use",			ActionType::USE},
	{"drink",		ActionType::DRINK},
	{"read",		ActionType::READ},
	{"c",			ActionType::CHARACTER},
	{"character",	ActionType::CHARACTER},
	{"equip",		ActionType::EQUIP},
	{"unequip",		ActionType::UNEQUIP},
	{"inspect",		ActionType::INSPECT},
	{DEV_MODE,		ActionType::ENABLE_DEV_MODE},

	// Room Specific
	{"take",		ActionType::TAKE},
	{"grab",		ActionType::TAKE},
	{"pick up",		ActionType::TAKE},
	{"open",		ActionType::OPEN},
	{"unlock",		ActionType::UNLOCK},
	{"l",			ActionType::LOOK},
	{"look",		ActionType::LOOK},
	{"drop",		ActionType::DROP},

	// Enemy Encounter
	{"attack",		ActionType::ATTACK},
	{"retreat",		ActionType::RETREAT},
	{"end turn",	ActionType::END_TURN},
	{"study",		ActionType::STUDY},
	{"dodge",		ActionType::DODGE},
	{"block",		ActionType::BLOCK},
	{"kill",		ActionType::KILL},
	{"tp",			ActionType::TP}
};

const map<Interaction::ActionType, ActionInfo> actionInfoMap = {
	//											room	encounter	isDevAction	helpString
	//Universal
	{Interaction::ActionType::INVENTORY,		{true,	true,		false,		"Displays Inventory"}},
	{Interaction::ActionType::USE,				{true,	true,		false,		"Use the specified item from the inventory"}},
	{Interaction::ActionType::CHARACTER,		{true,	true,		false,		"Displays the player stats"}},
	{Interaction::ActionType::EQUIP,			{true,	true,		false,		"Equips the specified piece of equipment from the inventory"}},
	{Interaction::ActionType::UNEQUIP,			{true,	true,		false,		"Unequips the specified piece of equipment and places into inventory"}},
	{Interaction::ActionType::DRINK,			{true,	true,		false,		"Drink the specified item from the player's inventory"}},
	{Interaction::ActionType::INSPECT,			{true,	true,		false,		"Displays the stats of the specified item in the player's inventory"}},
	{Interaction::ActionType::QUIT,				{true,	true,		false,		"Quits the game"}},
	{Interaction::ActionType::READ,				{true,	true,		false,		"Read items from players inventory"}},
	{Interaction::ActionType::ERROR,			{true,	true,		false,		""}},
	{Interaction::ActionType::HELP,				{true,	true,		false,		""}},
	{Interaction::ActionType::ENABLE_DEV_MODE,	{true,	true,		false,		""}},
	{Interaction::ActionType::TP,				{true,	true,		true,		""}},


	//Room Specific	
	{Interaction::ActionType::TAKE,				{true,	false,		false,		"Takes the specified item in the room"}},
	{Interaction::ActionType::OPEN,				{true,	false,		false,		"Opens the specified container/door"}},
	{Interaction::ActionType::DROP,				{true,	false,		false,		"Drop the specified item from the inventory into the room"}},
	{Interaction::ActionType::UNLOCK,			{true,	false,		false,		"Unlocks the specified container/door"}},
	{Interaction::ActionType::LOOK,				{true,	false,		false,		"Displays the contents of the room"}},

	//Encounter Specific
	{Interaction::ActionType::ATTACK,			{false,	true,		false,		"Attack the specified enemy in the room"}},
	{Interaction::ActionType::BLOCK,			{false,	true,		false,		"Blocks the specified enemy in the room"}},
	{Interaction::ActionType::RETREAT,			{false,	true,		false,		"Retreat from the current encounter"}},
	{Interaction::ActionType::STUDY,			{false,	true,		false,		"Display the enemy stats"}},
	{Interaction::ActionType::DODGE,			{false,	true,		false,		"Attempt to dodge enemy attack awarding you with free turn"}},
	{Interaction::ActionType::END_TURN,			{false,	true,		false,		""}},
	{Interaction::ActionType::KILL,				{false,	true,		true,		""}},
};

set<string> Interaction::actionsUsed = {
	"character",
	"inventory",
	"inspect",
	"look",
	"quit"
};

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
bool Interaction::isDevAction(ActionType type)
{
	if (actionInfoMap.find(type) == actionInfoMap.end())
		return false;

	ActionInfo info = actionInfoMap.at(type);
	return info.isDevAction;
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

	if (!player.isDev() && isDevAction(inputResult.actionType))
		inputResult.actionType = ActionType::ERROR;

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
		player.setIsDev(!player.isDev());

		if (player.isDev())
			cout << "DevMode: Activated" << endl;
		else
			cout << "DevMode: Deactivated" << endl;

		break;
	}
	case ActionType::EQUIP:
	{
		inputResult.succeeded = player.findAndEquip(inputResult.target);
		break;
	}
	case ActionType::UNEQUIP:
	{
		inputResult.succeeded = player.findAndUnequip(inputResult.target);
		break;
	}
	case ActionType::CHARACTER:
	{
		player.displayStats();
		break;
	}
	case ActionType::INSPECT:
	{
		inputResult.succeeded = player.findAndInspect(inputResult.target);
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
	case ActionType::READ:
	{
		inputResult.succeeded = player.findAndRead(inputResult.target);
		break;
	}
	case ActionType::HELP:
	{
		helperDisplay();
		break;
	}
	case Interaction::ActionType::TP:
	{

		string roomName = inputResult.target;
		vector<string> allRoomNames = DungeonBuilder::getRoomNames();

		int roomIndex = Utils::vecIndexOf(allRoomNames, roomName);

		if (roomIndex != -1)
		{
			cout << "Room Found" << endl;

			inputResult.tpRoomName = roomName;
			inputResult.succeeded = true;
		}
		else
		{
			cout << "Room Not Found" << endl;
			inputResult.succeeded = false;
		}

		break;
	}
	case ActionType::ERROR:
	{
		cout << "Sorry, that input is not recognized." << endl;
		break;
	}
	}

	if (inputResult.actionType != ActionType::ERROR)
		addActionUsed(inputResult.actionStr);

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
			result.succeeded = true;
			result.isDevAction = isDevAction(result.actionType);

			return result;
		}
	}

	result.actionType = ActionType::ERROR;
	return result;
}