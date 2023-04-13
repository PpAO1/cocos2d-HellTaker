#pragma once
#include "cocos2d.h"

class Npc : public cocos2d::Layer
{
public:
	Npc();
	~Npc();
	Npc(int stage);
	int stageNum;
	cocos2d::Sprite* loveSign;
	cocos2d::Sprite* pNpc;
	virtual bool init();
	void LoveSignAnim();
	void Stage1NpcAnim();
};