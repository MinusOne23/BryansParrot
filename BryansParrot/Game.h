#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>
#include <set>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"

using namespace std;

/// GAME CLASS
/// -DEFINES ACTION ENUMS
/// -Used to interact with all rooms
/// -Game loops untill player dies or enters the winning room
/// 
/// INITIALIZE_GAME: Creates all rooms filled with items and enemies
/// ENUM_INPUT_CHECKER: Converst uiser input into an action
/// PLAYER_DIED: PLayer health reaches 0 - ends game
/// PLAYER_WIN: PLayer enters winning room - ends game
/// PROMPT_REPLAY: Game is over and asks to play game again
/// OPEN_DOOR: Player enters new room
/// START: Starts game and checks untill PLayer dies or player wins
/// GAME_INTERACT: Game loops and performs actions

class Game
{
private:

	enum class Interaction
	{
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
		ERROR
	};

	struct ActionResult
	{
		Interaction interaction;
		string helpStr;
	};

	static const map<string, ActionResult> actions;
	set<string> actionsUsed;

	enum class GameState
	{
		PLAY,
		WIN,
		DIED
	};

	struct InputCheckerResult
	{
		Interaction interaction;
		string objectName;
		string actionStr;
	};

	static const int MAX_ACTION_WORDS;

	GameState gameState;
	Player player;

	vector<Room> allRooms;

	Room* currentRoom;
	Room* winRoom;

	void initializeGame();
	InputCheckerResult enumInputChecker(string inputStr);
	void playerDied();
	void playerWin();
	void promptReplay();

	void openDoor(Room::DoorIndex index);
	Room::DoorIndex getDoorIndex(string doorName);

public:
	void helperDisplay();
	void start();
	void gameInteract();

	// Unit Test methods
	void initializeGameTest();
};

#endif // GAME_H

