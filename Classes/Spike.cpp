#include "Spike.h"

USING_NS_CC;

Spike::Spike()
{
}

Spike::~Spike()
{
}

Spike::Spike(int objNum, bool up)
{
	if (objNum == MapObject::SPIKE)
	{
		isMove = false;
		isUp = true;

		this->init();
	}
	else if (objNum == MapObject::MOVESPIKEUP || objNum == MapObject::MOVESPUKEDOWN)
	{
		isMove = true;
		if (up)
		{
			isUp = true;
		}
		else
		{
			isUp = false;
		}

		this->init();
	}
}

bool Spike::init()
{
	if (isUp)
	{
		pSpike = Sprite::create("Sprite/assets100V20116.png");
		this->setContentSize(pSpike->getContentSize());
		this->addChild(pSpike);
	}
	else
	{
		pSpike = Sprite::create("Sprite/assets100V20120.png");
		this->setContentSize(pSpike->getContentSize());
		this->addChild(pSpike);
	}
	return true;
}

void Spike::SpikeAnim()
{
	if (isUp == true && isMove == true)
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
		pSpike->runAction(animate);
	}
	else if(isUp == false && isMove == true)
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
		pSpike->runAction(animate);
	}
}

void Spike::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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

void Spike::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
}

void Spike::onEnter()
{
	Layer::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(Spike::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(Spike::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void Spike::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Layer::onExit();
}
