#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
public:
	virtual string getDisplay() const = 0;

protected:
	string name;
};

#endif // ITEM_H

