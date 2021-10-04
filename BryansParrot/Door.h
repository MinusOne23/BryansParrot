#pragma once
#ifndef DOOR_H
#define DOOR_H

class Room;

class Door
{
public:
	Door();
	Door(int locks);

	bool isLocked() const;
	int getNumLocks() const;
	int getLocksLeft() const;
	void unlock();
private:
	int numLocks;
	int locksLeft;
	Room* otherRoom;
};

#endif // DOOR_H