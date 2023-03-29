#include "Lock.h"

Lock* Lock::_instance = nullptr;

Lock::Lock()
{
}

Lock::~Lock()
{
}

Lock& Lock::getInstance()
{
	_instance = new Lock();

	return *_instance;
}
