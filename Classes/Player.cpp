#include "Player.h"

USING_NS_CC;

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
	this->PlayerIdleAnim();
	return true;
}

void Player::PlayerIdleAnim()
{
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

void Player::update(float f)
{
}
