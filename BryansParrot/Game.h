#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"

using namespace std;

class Game
{
private:
	enum class Interaction
	{
		QUIT = 0,
		INVENTORY = 1,
		TAKE = 2,
		OPEN_DOOR = 3,
		UNLOCK_DOOR = 4,
		ATTACK = 5,
		MOVE_BACK = 6,
		LOOK = 7,
		CHARACTER = 8,
		ERROR = 99
	};

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
	};

	static const int MAX_ACTION_WORDS;
	static const map<string, Interaction> actions;

	GameState gameState;
	Room* currentRoom;
	Room* winRoom;
	Player player;

	vector<Room*> allRooms;

	void initializeGame();
	InputCheckerResult enumInputChecker(string inputStr);
	void playerDied();
	void playerWin();
	void promptReplay();

public:
	~Game();

	void start();
	void gameInteract();
};

#endif // GAME_H

