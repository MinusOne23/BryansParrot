#include "Key.h"

Key::Key(Door* _door)
{
	name = "key";
	door = _door;
}

Key::Key(string _name, Door* _door)
{
	name = _name;
	door = _door;
}

string Key::getDisplay() const
{
	return name;
}
