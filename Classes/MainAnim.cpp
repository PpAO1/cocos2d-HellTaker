#include "MainAnim.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainAnim::createScene()
{
	return MainAnim::create();
}

bool MainAnim::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}
