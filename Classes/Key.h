#pragma once
#include "cocos2d.h"

class Key : public cocos2d::Layer
{
private:
	Key();
	~Key();
	static Key* _instance;

public:
	cocos2d::Sprite* pKey;
	static Key& getInstance();
	virtual bool init();
	
	void KeyAnim();
	
};