#pragma once
#include "cocos2d.h"

class Player : public cocos2d::Layer
{
private:
	Player ();
	~Player ();
	static Player* _instance;

public:
	static Player& getInstance();
};