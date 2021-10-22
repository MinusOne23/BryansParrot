#pragma once
#ifndef DOOR_H
#define DOOR_H

#include <memory>

using namespace std;

// Forward declaring room to reference in the door
class Room;

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
*	otherRoom - the other room that this door leads to
*/
class Door
{
public:
	Door(Room& nRoom, int locks = 0);

	bool isLocked() const;
	int getNumLocks() const;
	int getLocksLeft() const;

	inline Room& getNextRoom() const { return nextRoom; }

	void unlock();
private:
	int numLocks;
	int locksLeft;
	Room& nextRoom;
};

#endif // DOOR_H