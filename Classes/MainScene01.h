#pragma once
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

class MainScene01 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene01);

	cocos2d::Sprite* main;
	cocos2d::Label* plabel;

	void update(float f);
	void SceneEnd(float f);
};