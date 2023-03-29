#include "Key.h"

Key* Key::_instance = nullptr;

Key::Key()
{
}

Key::~Key()
{
}

Key& Key::getInstance()
{
	_instance = new Key();

	return *_instance;
}
