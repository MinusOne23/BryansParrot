#pragma once
#ifndef MINI_MAP_H
#define MINI_MAP_H

#include <string>
#include <vector>

#include "Room.h"

using namespace std;

class MiniMap
{
public:

	void discoverRoom(Room* currentRoom);
	string mapDisplay() const;

private:

	enum class RoomMapState
	{
		ENEMY_ENCOUNTER = '!',
		NOT_CLEARED = '?',
		CLEARED = 'X',
		CURRENT_ROOM = '@',
		NONE = ' '
	};

	vector<vector<Room*>> discoveredRooms;
	Room::Position minFoundPos = { -1, -1 }, maxFoundPos = { -1, -1 };

	char getSymbol(Room* room) const;

};

#endif // MINI_MAP_H