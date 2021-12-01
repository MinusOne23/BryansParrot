
#include <sstream>
#include <iostream>

#include "MiniMap.h"
#include "Utils.h"

void MiniMap::discoverRoom(Room* currentRoom)
{
	Room::Position position = currentRoom->getPosition();

	if (minFoundPos.row == -1 || position.row < minFoundPos.row)
		minFoundPos.row = position.row;

	if (minFoundPos.col == -1 || position.col < minFoundPos.col)
		minFoundPos.col = position.col;

	int minRows = position.row + 1;

	while (discoveredRooms.size() < minRows)
	{
		discoveredRooms.push_back(vector<Room*>());
	}

	int minCols = position.col + 1;

	while (discoveredRooms[position.row].size() < minCols)
	{
		discoveredRooms[position.row].push_back(nullptr);
	}

	discoveredRooms[position.row][position.col] = currentRoom;
}

string MiniMap::mapDisplay() const
{
	stringstream ss;

	ss << "\t===========================================" << endl;
	ss << "\t Mini Map" << endl;
	ss << "\t===========================================" << endl << endl;

	for (int r = minFoundPos.row; r < discoveredRooms.size(); r++)
	{
		ss << "\t ";
		for (int c = minFoundPos.col; c < discoveredRooms[r].size(); c++)
		{
			if (c != minFoundPos.col)
				ss << " ";

			ss << getSymbol(discoveredRooms[r][c]);
		}
		ss << endl;
	}

	ss << endl << "\t===========================================" << endl;

	return ss.str();
}

char MiniMap::getSymbol(Room* room) const
{
	if (room == nullptr)
		return (char)RoomMapState::NONE;

	if (room->getHasPlayer())
		return (char)RoomMapState::CURRENT_ROOM;

	if (room->encounterCount() > 0)
		return (char)RoomMapState::ENEMY_ENCOUNTER;

	if (!room->isCleared())
		return (char)RoomMapState::NOT_CLEARED;

	return (char)RoomMapState::CLEARED;
}


