#include "Key.h"

Key::Key()
{
	name = "Key";
	door = nullptr;
}

Key::Key(Door* _door)
{
	name = "Key";
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
