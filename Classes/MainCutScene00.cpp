#include "MainCutScene00.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainCutScene00::createScene()
{
	return MainCutScene00::create();
}

bool MainCutScene00::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}
