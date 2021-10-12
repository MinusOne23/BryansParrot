#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"

using namespace std;

class Game
{
public:
	void start();
	void gameInteract();
private:

	Room* currentRoom;
	Player player;
};

#endif // GAME_H

