#include "MainCutScene02.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainCutScene02::createScene()
{
	return MainCutScene02::create();
}

bool MainCutScene02::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}

void MainCutScene02::SceneEnd(float f)
{
}
