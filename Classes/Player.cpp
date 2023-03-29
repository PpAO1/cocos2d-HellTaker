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

	return *_instance;
}
