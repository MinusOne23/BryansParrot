#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
public:
	string getName() const;

private:
	string name;
};

#endif // ITEM_H

