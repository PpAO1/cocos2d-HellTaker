#include "MainScene02.h"
#include "MainScene03.h"


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

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	gameLayer = &GameManager::getInstance(2);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(2);
	gameLayer->init();
	this->addChild(gameLayer);

	main = Sprite::create("Sprite/chapterBG0003.png");
	main->setAnchorPoint(Vec2(0, 0));
	main->setPosition(0, 0);
	main->setZOrder(1);
	this->addChild(main);

	this->scheduleUpdate();

	return true;
}

void MainScene02::SceneEnd(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);
	gameLayer->ReleaseInstance();

	auto pScene = MainScene03::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void MainScene02::update(float f)
{
	if (gameLayer->isRestart)
	{
		scheduleOnce(schedule_selector(MainScene02::Restart), 1.44f);
		gameLayer->isRestart = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->pressF)
	{
		scheduleOnce(schedule_selector(MainScene02::Restart), 0.01f);
		gameLayer->pressF = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->isGonextMap)
	{
		scheduleOnce(schedule_selector(MainScene02::SceneEnd), 0.01f);
		gameLayer->isGonextMap = false;

		this->unscheduleUpdate();
	}
}

void MainScene02::Restart(float f)
{
	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);

	auto pScene = MainScene02::createScene();
	Director::getInstance()->replaceScene(pScene);
}