#pragma once
#include "cocos2d.h"

class Lock : public cocos2d::Layer
{
public:
	Lock();
	~Lock();

	cocos2d::Sprite* pLock;
	virtual bool init();
	void UnLock();
};
