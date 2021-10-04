#pragma once
#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "Door.h"

class Key : Item
{
public:
	Key(Door* _door);
private:
	Door* door;
};

#endif // KEY_H
