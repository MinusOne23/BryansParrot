#include "Key.h"

Key::Key()
	: Item{ "Key" }, door(nullptr) {}

Key::Key(shared_ptr<Door> _door)
	: Item{ "Key" }, door(_door) {}

Key::Key(string _name, shared_ptr<Door> _door)
	: Item{ _name }, door(_door) {}

string Key::getDisplay() const
{
	return name;
}
