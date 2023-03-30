#pragma once
#include "cocos2d.h"

class Player : public cocos2d::Layer
{
private:
	Player ();
	~Player ();
	static Player* _instance;

public:
	cocos2d::Sprite* pPlayer;
	static Player& getInstance();
	virtual bool init();
	
	void PlayerIdleAnim();
	void update(float f);
};