#include "Key.h"

USING_NS_CC;

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

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Key::init()
{
	pKey = Sprite::create("Sprite/assets100V2014.png");
	this->setContentSize(pKey->getContentSize());
	this->addChild(pKey);
	this->KeyAnim();
	return true;
}

void Key::KeyAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 4; i < 16 ; i++)
	{
		sprintf(str, "Sprite/assets100V201%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pKey->runAction(rep);
}
