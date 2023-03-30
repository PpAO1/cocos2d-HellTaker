#pragma once
#include "cocos2d.h"

class Spike : public cocos2d::Layer
{
private:
	Spike();
	~Spike();
	static Spike* _instance;
public:
	cocos2d::Sprite* pSpike;
	static Spike& getInstance();
	virtual bool init();
};