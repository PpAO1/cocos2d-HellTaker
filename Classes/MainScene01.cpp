#include "MainScene01.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainScene01::createScene()
{
	return MainScene01::create();
}

bool MainScene01::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}

void MainScene01::update(float f)
{
}

void MainScene01::SceneEnd(float f)
{
}
