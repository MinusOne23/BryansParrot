#include <iostream>

#include "Room.h"
#include "Door.h"
#include "Key.h"
#include "Player.h"
#include "Inventory.h" 
#include "Enemy.h"

using namespace std;

int main()
{
	//Obj 
	Room firstRoom;
	Room secondRoom;
	Door door, door2(2);
	Key key(&door);
	Room goblin;
	Player player1;
	Enemy enemy("goblin");

	//Room 1: Initialization
	firstRoom.addItem(&key);
	firstRoom.addDoor(&door);

	//Room 2: Initialization
	secondRoom.addDoor(&door2);
	secondRoom.addEnemy(&enemy);

	//Enter Room 1
	firstRoom.displayContents();
	firstRoom.roomInteract(&player1, door);

	//Enter Room 2
	secondRoom.displayContents();
	secondRoom.roomInteract(&player1, door2);
	secondRoom.addItem(&key);
	secondRoom.displayContents();
	secondRoom.roomInteract(&player1, door2);

	system("pause");
	return 0;
};