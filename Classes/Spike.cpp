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
	_instance = new Spike();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Spike::init()
{
	pSpike = Sprite::create("Sprite/assets100V20116.png");
	this->setContentSize(pSpike->getContentSize());
	this->addChild(pSpike);
	return true;
}
