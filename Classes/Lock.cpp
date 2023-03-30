#include "Lock.h"

USING_NS_CC;

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

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Lock::init()
{
	pLock = Sprite::create("Sprite/backup_lockbox.png");
	this->setContentSize(pLock->getContentSize());
	this->addChild(pLock);
	return true;
}
