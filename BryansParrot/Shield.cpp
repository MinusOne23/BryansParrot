#include <sstream>

#include "Shield.h"
#include "Utils.h"

Shield::Shield(string _name)
	: Equippable{ _name } {}

void Shield::setBlockMove(BlockType blockType, BlockMove blockMove)
{
	blockMoves[(int)blockType] = blockMove;
}

int Shield::calcBlockAmt(BlockType blockType)
{
	BlockMove move = blockMoves[(int)blockType];
	return Utils::randInt(move.minBlock, move.maxBlock);
}

string Shield::equipmentDisplay(string title, string linePrefix)
{
	BlockMove singleBlock = blockMoves[(int)BlockType::SINGLE];
	BlockMove groupBlock = blockMoves[(int)BlockType::GROUP];

	stringstream ss;
	ss << Equippable::equipmentDisplay(title, linePrefix);
	ss << linePrefix << "   Single Block: (" << singleBlock.minBlock << " - " << singleBlock.maxBlock << ")" << endl;
	ss << linePrefix << "   Group Block: (" << groupBlock.minBlock << " - " << groupBlock.maxBlock << ")" << endl;
	return ss.str();
}
