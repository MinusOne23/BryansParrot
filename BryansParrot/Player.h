#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Item.h"

class Player {
public:
	void takeItem(Item* item);
	void displayInventory() const;
private:
	Inventory inventory;
};
#endif // !PLAYER.H
