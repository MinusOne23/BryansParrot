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
		QUIT,
		INVENTORY,
		TAKE,
		OPEN,
		UNLOCK,
		ATTACK,
		LOOK,
		CHARACTER,
		ERROR
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
	void start();
	void gameInteract();
};

#endif // GAME_H

