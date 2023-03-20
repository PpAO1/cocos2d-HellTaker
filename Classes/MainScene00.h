#pragma once
#include "cocos2d.h"
#include "Player.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

class MainScene00 : public cocos2d::Scene
{
private:
	Player* player;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene00);

	cocos2d::Sprite* main;

	void update(float f);
	void SceneEnd(float f);
};