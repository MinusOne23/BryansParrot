#pragma once
#ifndef SHIELD_H
#define SHIELD_H

#include <string>

#include "Equippable.h"

using namespace std;

class Shield : public Equippable
{
public:
	enum class BlockType
	{
		SINGLE = 0,
		GROUP
	};

	struct BlockMove
	{
		int minBlock = 0;
		int maxBlock = 0;
	};

	Shield(string _name);

	void setBlockMove(BlockType blockType, BlockMove blockMove);

	int calcBlockAmt(BlockType blockType);

	virtual string equipmentDisplay(string title, string linePrefix = "");

private:

	BlockMove blockMoves[2];
};

#endif // SHIELD_H
