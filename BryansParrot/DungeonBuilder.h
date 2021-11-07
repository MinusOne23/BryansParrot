#pragma once
#ifndef DUNGEON_BUILDER_H
#define DUNGEON_BUILDER_H

#include <vector>

#include "Room.h"

using namespace std;

class DungeonBuilder
{
public:
	static vector<Room> buildDungeon();

private:
	DungeonBuilder();
};

#endif // DUNGEON_BUILDER_H