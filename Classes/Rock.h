#pragma once
#include "cocos2d.h"
#include "stdafx.h"

class Rock : public cocos2d::Layer
{
private:
	Rock();
	~Rock();
	static Rock* _instance;

public:
	Coordinate _mapPos;
	cocos2d::Sprite* rock;
	static Rock& getInctance();
	void RockMove(cocos2d::Vec2 pos);
	void RockMoveAnim();
	virtual bool init();
};