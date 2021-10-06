#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Item.h"
#include "Door.h"

class Player {
public:
	void takeItem(Item* item);
	void displayInventory() const;
	//void roomInteract(Item* item,Door door);
private:
	Inventory inventory;
};
#endif // !PLAYER.H
