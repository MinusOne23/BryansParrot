#include <sstream>
#include <iostream>

#include "Shield.h"
#include "Utils.h"

Shield::Shield(string _name)
	: Equippable{ _name } {}

void Shield::setBlockMove(BlockType blockType, BlockMove blockMove)
{
	if (blockType == BlockType::ERROR)
		return;

	blockMoves[(int)blockType] = blockMove;
}

Shield::BlockType Shield::blockTypeFromStr(const string& moveName) const
{
	if (Utils::equalsCI(moveName, "single block") || Utils::equalsCI(moveName, "single"))
		return BlockType::SINGLE;

	if (Utils::equalsCI(moveName, "group block") || Utils::equalsCI(moveName, "group"))
		return BlockType::GROUP;

	return BlockType::ERROR;
}

int Shield::calcBlockAmt(BlockType blockType)
{
	if (blockType == BlockType::ERROR)
		return 0;

	BlockMove move = blockMoves[(int)blockType];
	return Utils::randInt(move.minBlock, move.maxBlock);
}

int Shield::getStaminaRequied(BlockType blockType)
{
	if (blockType == BlockType::ERROR)
		return 0;

	return blockMoves[(int)blockType].stamina;
}

string Shield::equipmentDisplay(string title, string linePrefix) const
{
	BlockMove singleBlock = blockMoves[(int)BlockType::SINGLE];
	BlockMove groupBlock = blockMoves[(int)BlockType::GROUP];

	stringstream ss;
	ss << Equippable::equipmentDisplay(title, linePrefix);
	ss << blocksDisplay(linePrefix + "   ");
	return ss.str();
}

string Shield::blocksDisplay(string linePrefix) const
{
	BlockMove singleBlock = blockMoves[(int)BlockType::SINGLE];
	BlockMove groupBlock = blockMoves[(int)BlockType::GROUP];

	stringstream ss;
	ss << linePrefix << "Single Block: " << singleBlock.display() << endl;
	ss << linePrefix << "Group Block: " << groupBlock.display() << endl;
	return ss.str();
}

string Shield::BlockMove::display()
{
	stringstream ss;
	ss << "(" << minBlock << " - " << maxBlock << "), " << stamina << " stamina";

	return ss.str();
}
