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
		TAKE_KEY = 2,
		OPEN_DOOR = 3,
		UNLOCK_DOOR = 4,
		KILL_GOBLIN = 5,
		MOVE_BACK = 6,
		LOOK = 7,
		HELP=8,
		ERROR = 99
	};
	static const map<string, Interaction> actions;
	vector<string> helper;

	Room* currentRoom;
	Player player;

public:
	
	void addHelper(string);
	void helperDisplay();
	void start();
	void gameInteract();
	virtual Interaction enumInputChecker(string inputStr);

	
};

#endif // GAME_H

