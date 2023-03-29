#pragma once
#include "cocos2d.h"

class Key : public cocos2d::Layer
{
private:
	Key();
	~Key();
	static Key* _instance;

public:
	static Key& getInstance();
	
};