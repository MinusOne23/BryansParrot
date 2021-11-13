#pragma once
#ifndef DOOR_H
#define DOOR_H

#include <memory>

using namespace std;

/*
* Door class for players to be able to move from room
* to room
* 
* methods:
*	unlock() - unlocks a single lock on the door
* 
* member variables:
*	numLocks - total number of locks on the door
*	locksLeft - number of locked locks left on the door
*/
class Door
{
public:
	Door(int locks = 0);

	bool isLocked() const;
	int getNumLocks() const;
	int getLocksLeft() const;

	void unlock();
private:
	int numLocks;
	int locksLeft;
};

#endif // DOOR_H