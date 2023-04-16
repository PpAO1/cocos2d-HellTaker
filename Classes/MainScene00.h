#pragma once
#include "cocos2d.h"
#include "GameManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

class MainScene00 : public cocos2d::Scene
{
private:

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene00);

	GameManager* gameLayer;

	cocos2d::Sprite* main;

	int stageNum;
	
	void SceneEnd(float f);
	void update(float f);
	void Restart(float f);
	void ReleaseTest(float f);
};