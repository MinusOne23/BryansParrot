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
		ERROR = -1,
		SINGLE,
		GROUP
	};

	struct BlockMove
	{
		int minBlock = 0;
		int maxBlock = 0;
		int stamina = 0;

		string display();
	};

	Shield(string _name);

	void setBlockMove(BlockType blockType, BlockMove blockMove);
	BlockType blockTypeFromStr(const string& moveName) const;
	int calcBlockAmt(BlockType blockType);
	int getStaminaRequied(BlockType blockType);

	virtual string equipmentDisplay(string title = "", string linePrefix = "") const override;
	virtual string blocksDisplay(string linePrefix = "") const;

private:

	BlockMove blockMoves[2];
};

#endif // SHIELD_H
