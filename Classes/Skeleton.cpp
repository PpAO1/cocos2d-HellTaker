#include "Skeleton.h"

USING_NS_CC;
Skeleton* Skeleton::_instance = nullptr;

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
}

Skeleton& Skeleton::getInstance()
{
	_instance = new Skeleton();

	return *_instance;
}
