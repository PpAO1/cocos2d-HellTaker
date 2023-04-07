#pragma once
#include "cocos2d.h"

class Npc : public cocos2d::Layer
{
private:
	Npc();
	~Npc();
	static Npc* _instance;
public:
	static Npc& getInstance();
	virtual bool init();
};