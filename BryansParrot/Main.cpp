#include <iostream>

#include "Room.h"
#include "Door.h"
#include "Key.h"
#include "Player.h"
#include "Inventory.h"

using namespace std;

int main()
{
	Room firstRoom;
	Door door;
	Key key(&door);
	Player player1;
	

	firstRoom.addItem(&key);
	firstRoom.addDoor(&door);

	firstRoom.displayContents();

	system("pause");
	return 0;
}