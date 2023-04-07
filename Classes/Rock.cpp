#include "Rock.h"

USING_NS_CC;

Rock* Rock::_instance = nullptr;

Rock::Rock()
{
}

Rock::~Rock()
{
}

Rock& Rock::getInctance()
{
	_instance = new Rock();
	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

void Rock::RockMove(cocos2d::Vec2 pos)
{
	auto rockmove = MoveBy::create(0.15f, pos);
	rock->runAction(rockmove);
}

bool Rock::init()
{
	rock = Sprite::create("Sprite/boxExport0001.png");
	this->setContentSize(rock->getContentSize());
	this->addChild(rock);
	return true;
}
