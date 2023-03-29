#pragma once
#include "cocos2d.h"

class Rock : public cocos2d::Layer
{
private:
	Rock();
	~Rock();
	static Rock* _instance;

public:
	cocos2d::Sprite* rock;
	static Rock& getInctance();
	virtual bool init();
};