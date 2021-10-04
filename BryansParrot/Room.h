#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "Item.h"
#include "Door.h"

using namespace std;

class Room
{
public:
	void displayContents() const;
	void addItem(Item* newItem);
	void addDoor(Door* newDoor);
private:
	vector<Item*> items;
	vector<Door*> doors;

	void displayItems() const;
	void displayDoors() const;
};

#endif // ROOM_H