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
	void updateRoom();
	void gameInteract(Player* player, Room* room);
private:
	Room* currentRoom;
	Door* door;
	Key* key;
	Room* goblin;
	Player* player1;
	Enemy* enemy;
	Game* game;
};

#endif // GAME_H

