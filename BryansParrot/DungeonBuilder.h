#pragma once
#ifndef DUNGEON_BUILDER_H
#define DUNGEON_BUILDER_H

#include <map>
#include <vector>

#include "Room.h"
#include "Story.h"

using namespace std;

class DungeonBuilder
{
public:
	static map<string, Room> buildDungeon();
	static vector<string> getRoomNames();

private:
	static vector<string> roomNames;
	DungeonBuilder();
};

#endif // DUNGEON_BUILDER_H