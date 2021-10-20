#include "Door.h"
#include "Room.h"

Door::Door(Room& nRoom, int locks) 
	: nextRoom(nRoom), numLocks(locks), locksLeft(locks) {}

bool Door::isLocked() const
{
	return locksLeft > 0;
}

int Door::getNumLocks() const
{
	return numLocks;
}

int Door::getLocksLeft() const
{
	return locksLeft;
}

void Door::unlock()
{
	if (!isLocked())
		return;

	locksLeft--;
}