#include <iostream>

#include "Room.h"
#include "Door.h"
#include "Key.h"

using namespace std;

int main()
{
	Room firstRoom;
	Door door;
	Key key(&door);

	firstRoom.addItem(&key);
	firstRoom.addDoor(&door);

	firstRoom.displayContents();

	system("pause");
	return 0;
}