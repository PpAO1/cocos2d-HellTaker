#include "MoveSpike.h"

USING_NS_CC;
MoveSpike* MoveSpike::_instance = nullptr;

MoveSpike::MoveSpike()
{
}

MoveSpike::MoveSpike(bool isup)
{
	if (isup == false)
		isUp = false;
	else
		isUp = true;
}

MoveSpike::~MoveSpike()
{
}

MoveSpike& MoveSpike::getInstance()
{
	_instance = new MoveSpike();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool MoveSpike::init()
{
	if (isUp) 
	{
		pMoveSpike = Sprite::create("Sprite/assets100V20116.png");
	}
	else
	{
		pMoveSpike = Sprite::create("Sprite/assets100V20120.png");
	}

	this->setContentSize(pMoveSpike->getContentSize());
	this->addChild(pMoveSpike);
	return true;
}

void MoveSpike::SpikeAnim()
{
	if (isUp)
	{
		isUp = false;

		auto animation = Animation::create();

		animation->setDelayPerUnit(0.1f);

		char str[100] = { 0, };

		for (int i = 16; i < 21; i++)
		{
			sprintf(str, "Sprite/assets100V201%d.png", i);
			animation->addSpriteFrameWithFile(str);
		}

		auto animate = Animate::create(animation);
		pMoveSpike->runAction(animate);
	}
	else
	{
		isUp = true;

		auto animation = Animation::create();

		animation->setDelayPerUnit(0.1f);

		char str[100] = { 0, };

		for (int i = 20; i < 24; i++)
		{
			sprintf(str, "Sprite/assets100V201%d.png", i);
			animation->addSpriteFrameWithFile(str);
		}

		auto animate = Animate::create(animation);
		pMoveSpike->runAction(animate);
	}
}

void MoveSpike::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		SpikeAnim();
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		SpikeAnim();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		SpikeAnim();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		SpikeAnim();
		break;
	}
}

void MoveSpike::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
}

void MoveSpike::onEnter()
{
	Layer::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(MoveSpike::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(MoveSpike::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void MoveSpike::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Layer::onExit();
}
