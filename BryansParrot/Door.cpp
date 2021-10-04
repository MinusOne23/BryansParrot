#include "Door.h"
#include "Room.h"

Door::Door()
{
	numLocks = 0;
	locksLeft = 0;
}

Door::Door(int locks)
{
	numLocks = locks;
	locksLeft = locks;
}

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
