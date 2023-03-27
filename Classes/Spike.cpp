#include "Spike.h"

USING_NS_CC;
Spike* Spike::_instance = nullptr;

Spike::Spike()
{
}

Spike::~Spike()
{
}

Spike& Spike::getInstance()
{
	if (_instance == nullptr)
		_instance = new Spike();

	return *_instance;
}
