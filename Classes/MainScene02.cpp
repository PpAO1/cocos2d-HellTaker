#include "MainScene02.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainScene02::createScene()
{
	return MainScene02::create();
}

bool MainScene02::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}

void MainScene02::SceneEnd(float f)
{
}
