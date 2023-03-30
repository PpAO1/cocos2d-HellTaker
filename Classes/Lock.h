#pragma once
#include "cocos2d.h"

class Lock : public cocos2d::Layer
{
private:
	Lock();
	~Lock();
	static Lock* _instance;

public:
	cocos2d::Sprite* pLock;
	static Lock& getInstance();
	virtual bool init();
};
