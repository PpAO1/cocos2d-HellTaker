#pragma once
#include "cocos2d.h"

class Key : public cocos2d::Layer
{
public:
	Key();
	~Key();

	bool isGetKey;
	cocos2d::Sprite* pKey;
	virtual bool init();
	
	void KeyAnim();
	void KeyEating();
	
};