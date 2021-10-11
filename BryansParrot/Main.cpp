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
	//Obj 
	Room firstRoom, secondRoom;
	Door door, door2(2);
	Key key(&door2), key2(&door2);
	Room goblin;
	Player player1;
	Enemy enemy("goblin");
	Game game;

	//Room 1: Initialization
	firstRoom.addItem(&key);
	firstRoom.addDoor(&door);

	//Room 2: Initialization
	secondRoom.addDoor(&door2);
	secondRoom.addEnemy(&enemy);

	//Enter Room 1
	firstRoom.displayContents();
	//game.gameInteract(&player1, &firstRoom);
	firstRoom.roomInteract(&player1);

	//Enter Room 2
	secondRoom.displayContents();
	//game.gameInteract(&player1, &secondRoom);
	secondRoom.roomInteract(&player1);
	secondRoom.addItem(&key2);
	secondRoom.displayContents();
	secondRoom.roomInteract(&player1);
	//game.gameInteract(&player1, &secondRoom);

	cout << "Congratulations you have navigated through all the rooms and beat the game!" << endl;

	system("pause");
	return 0;
};