#include <iostream>

#include "Room.h"
#include "Door.h"
#include "Key.h"
#include "Player.h"
#include "Inventory.h" 
#include "Enemy.h"
#include "Game.h"

using namespace std;

int main()
{
	Game game;
	game.start();

	system("pause");
	return 0;
};