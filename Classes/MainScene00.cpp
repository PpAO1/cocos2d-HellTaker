#include "MainScene00.h"
#include "MainScene01.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainScene00::createScene()
{
	return MainScene00::create();
}

bool MainScene00::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	gameLayer = &GameManager::getInstance(0);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(2);
	gameLayer->init();
	this->addChild(gameLayer);

	main = Sprite::create("Sprite/chapterBG0001.png");
	main->setAnchorPoint(Vec2(0, 0));
	main->setPosition(0, 0);
	main->setZOrder(1);
	this->addChild(main);

	this->scheduleUpdate();

	return true;
}

void MainScene00::SceneEnd(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);
	gameLayer->ReleaseInstance();

	auto pScene = MainScene01::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void MainScene00::update(float f)
{
	if (gameLayer->isRestart)
	{
		scheduleOnce(schedule_selector(MainScene00::Restart), 1.8f);
		gameLayer->isRestart = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->pressF)
	{
		scheduleOnce(schedule_selector(MainScene00::Restart), 0.01f);
		gameLayer->pressF = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->isGonextMap)
	{
		scheduleOnce(schedule_selector(MainScene00::SceneEnd), 0.01f);
		gameLayer->isGonextMap = false;

		this->unscheduleUpdate();
	}
}

void MainScene00::Restart(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);

	auto pScene = MainScene00::createScene();
	Director::getInstance()->replaceScene(pScene);
}