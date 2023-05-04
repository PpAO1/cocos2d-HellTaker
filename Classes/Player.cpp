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

	auto dust = Sprite::create("Sprite/small_vfx0001.png");
	dust->setPosition(pPlayer->getPosition());
	dust->setZOrder(1);
	this->addChild(dust);

	auto dustAnim = Animation::create();

	dustAnim->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "Sprite/small_vfx000%d.png", i);
		dustAnim->addSpriteFrameWithFile(str);
	}

	auto dustAnimation = Animate::create(dustAnim);
	RemoveSelf* removeanim = RemoveSelf::create(dustAnimation);
	dust->runAction(Sequence::create(dustAnimation, removeanim, nullptr));

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.1f);

	char str2[100] = { 0, };

	for (int i = 3; i < 9; i++)
	{
		sprintf(str2, "Sprite/assets100V2005%d.png", i);
		animation->addSpriteFrameWithFile(str2);
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
	RemoveSelf* removeanim = RemoveSelf::create(animation);
	huge->runAction(Sequence::create(animate, removeanim, nullptr));
}

void Player::PlayerMove(cocos2d::Vec2 pos)
{
	auto playermove = MoveBy::create(0.15f, pos);
	pPlayer->runAction(playermove);
}

void Player::PlayerClearAnim1(float f)
{
	pPlayer->stopAllActions();

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.15f);

	char str[100] = { 0, };

	for (int i = 59; i < 71; i++)
	{
		sprintf(str, "Sprite/hero00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);

	pPlayer->runAction(animate);
}

void Player::PlayerClearAnim2(float f)
{
	pPlayer->stopAllActions();

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.1f);
	
	char str[100] = { 0, };

	for (int i = 71; i < 76; i++)
	{
		sprintf(str, "Sprite/hero00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);

	pPlayer->runAction(animate);
}

void Player::PlayerClearAnim3(float f)
{
	pPlayer->stopAllActions();

	auto animation2 = Animation::create();
	animation2->setDelayPerUnit(0.2f);
	/*animation2->addSpriteFrameWithFile("Sprite/hero0075.png");*/
	animation2->addSpriteFrameWithFile("Sprite/hero0076.png");
	animation2->addSpriteFrameWithFile("Sprite/hero0077.png");

	auto animate2 = Animate::create(animation2);
	auto rep = RepeatForever::create(animate2);
	
	pPlayer->runAction(rep);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		pPlayer->setFlippedX(true);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		pPlayer->setFlippedX(false);
		break;
	}
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
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

void Player::GOAL() 
{
	scheduleOnce(schedule_selector(Player::PlayerClearAnim1), 0.4f);
	scheduleOnce(schedule_selector(Player::PlayerClearAnim2), 2.2f);
	scheduleOnce(schedule_selector(Player::PlayerClearAnim3), 2.7f);
}