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
	void DisplayContents() const;
	void AddItem(Item* newItem);
	void AddDoor(Door* newDoor);
private:
	vector<Item*> items;
	vector<Door*> doors;
};

#endif // ROOM_H