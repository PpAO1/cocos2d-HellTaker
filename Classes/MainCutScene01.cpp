#include "MainCutScene01.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainCutScene01::createScene()
{
	return MainCutScene01::create();
}

bool MainCutScene01::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}