#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <map>

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Interaction class to hold on to all logic for player interaction and
* parsing the input for different actions the player can take throughout
* the game
* 
* --------------------------------------------------------------------------------------
* Enums and Structures
* --------------------------------------------------------------------------------------
* ActionType:
*	All the possible interactions that the player can choose to have within the game
* 
* InteractionResult:
*	Structure to be returned when a player inputs an interaction for the game. Holds
*	what type of action it is, the target object name, the string for the action used
*	and whether or not it is an active action, meaning it would cause a turn switch
*	within an encounter
* 
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* getHelpText(string action)
*	Returns the help text for the ActionType designated to the passed action string
* 
* parseInput(string input)
*	Returns the created InteractionResult based off of the passed input - parses the
*	input to separate the action that the player is trying to perform followed by the
*	optional targetted object that the player wants to perform that action on.
* 
*	Ex) "use potion" would get parsed as "use" for the actionStr and "potion" as the
*	objectName
* 
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* MAX_ACTION_WORDS
*	The maximum amount of words that an action could be - helps keep parseInput
*	efficient for inputs with many words
* 
* actions
*	maps all possible string inputs to their designated action type
* 
* helpStrings
*	maps all action types to their designated help text
* 
* isActiveActions
*	mapa all action types to whether or not they are an active action
* --------------------------------------------------------------------------------------
*/
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
		LOOK,
		CHARACTER,
		EQUIP,
		HELP,
		ATTACK,
		KILL,
		STUDY,
		RETREAT
	};

	struct InteractionResult
	{
		ActionType actionType;
		string target;
		string actionStr;
		bool isActiveAction;
		bool succeeded;
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