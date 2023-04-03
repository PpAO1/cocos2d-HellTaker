#include "Player.h"

USING_NS_CC;
using namespace std;

Player* Player::_instance = nullptr;

Player::Player()
{
	
}

Player::~Player()
{
}

Player& Player::getInstance()
{
	_instance = new Player();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Player::init()
{
	pPlayer = Sprite::create("Sprite/hero0022.png");
	this->setContentSize(pPlayer->getContentSize());
	this->addChild(pPlayer);
	scheduleOnce(schedule_selector(Player::PlayerIdleAnim), 0.01f);
	return true;
}

void Player::PlayerIdleAnim(float f)
{
	pPlayer->stopAllActions();

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 22; i < 34; i++)
	{
		sprintf(str, "Sprite/hero00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pPlayer->runAction(rep);
}

void Player::PlayerMoveAnim()
{
	pPlayer->stopAllActions();

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 3; i < 9; i++)
	{
		sprintf(str, "Sprite/assets100V2005%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	pPlayer->runAction(animate);
	scheduleOnce(schedule_selector(Player::PlayerIdleAnim), 0.42f);
}

void Player::PlayerHitAnim()
{
	pPlayer->stopAllActions();

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 40; i < 53; i++)
	{
		sprintf(str, "Sprite/hero00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	pPlayer->runAction(animate);
	scheduleOnce(schedule_selector(Player::PlayerIdleAnim), 0.84f);
}

void Player::PlayerDamagedAnim()
{
	auto huge = Sprite::create("Sprite/huge_vfx0022.png");
	huge->setPosition(pPlayer->getPosition());
	huge->setZOrder(10);
	this->addChild(huge);

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 22; i < 28; i++)
	{
		sprintf(str, "Sprite/huge_vfx00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	huge->runAction(animate);

	auto blinkAnim = Blink::create(1.0f, 4);
	pPlayer->runAction(blinkAnim);
}



void Player::update(float f)
{

}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
		this->PlayerMoveAnim();
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		this->PlayerHitAnim();
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		this->PlayerDamagedAnim();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	}
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	}
}

void Player::onEnter()
{
	Layer::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void Player::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Layer::onExit();
}
