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

	char input[256];

	while (true)
	{
		cin.getline(input, 256);

		string inputStr(input);

		if (inputStr == "q")
		{
			break;
		}
		else if (inputStr == "i")
		{
			player1.displayInventory();
		}
		else if (inputStr == "take key")
		{
			player1.takeItem(&key);
		}
		else
		{
			cout << "Sorry, that input is not recognized." << endl;
		}
	}

	system("pause");
	return 0;
}