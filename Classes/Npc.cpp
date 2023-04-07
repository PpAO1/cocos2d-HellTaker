#include "Npc.h"
#include "Prologue2.h"

USING_NS_CC;
Npc* Npc::_instance = nullptr;

Npc::Npc()
{
}

Npc::~Npc()
{
}

Npc& Npc::getInstance()
{
	_instance = new Npc();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Npc::init()
{

	return true;
}
