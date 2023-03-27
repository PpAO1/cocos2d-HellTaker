#include "Player.h"


Player* Player::_instance = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

Player& Player::getInstance()
{
	if (_instance == nullptr)
		_instance = new Player();

	return *_instance;
}
