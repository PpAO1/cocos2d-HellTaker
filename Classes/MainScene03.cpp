#include "MainScene03.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainScene03::createScene()
{
	return MainScene03::create();
}

bool MainScene03::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	gameLayer = &GameManager::getInstance(3);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(2);
	gameLayer->init();
	this->addChild(gameLayer);

	main = Sprite::create("Sprite/chapterBG0004.png");
	main->setAnchorPoint(Vec2(0, 0));
	main->setPosition(0, 0);
	main->setZOrder(1);
	this->addChild(main);

	this->scheduleUpdate();

	return true;
}

void MainScene03::SceneEnd(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);
	gameLayer->ReleaseInstance();

	auto pScene = MainScene03::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void MainScene03::update(float f)
{
	if (gameLayer->isRestart)
	{
		scheduleOnce(schedule_selector(MainScene03::Restart), 1.8f);
		gameLayer->isRestart = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->pressF)
	{
		scheduleOnce(schedule_selector(MainScene03::Restart), 0.01f);
		gameLayer->pressF = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->isGonextMap)
	{
		scheduleOnce(schedule_selector(MainScene03::SceneEnd), 0.01f);
		gameLayer->isGonextMap = false;

		this->unscheduleUpdate();
	}
}

void MainScene03::Restart(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);

	auto pScene = MainScene03::createScene();
	Director::getInstance()->replaceScene(pScene);
}