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

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	gameLayer = &GameManager::getInstance(1);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(2);
	gameLayer->init();
	this->addChild(gameLayer);

	main = Sprite::create("Sprite/chapterBG0002.png");
	main->setAnchorPoint(Vec2(0, 0));
	main->setPosition(0, 0);
	main->setZOrder(1);
	this->addChild(main);

	this->scheduleUpdate();

	return true;
}

void MainScene01::SceneEnd(float f)
{
}

void MainScene01::update(float f)
{
	if (gameLayer->isRestart)
	{
		scheduleOnce(schedule_selector(MainScene01::Restart), 1.8f);
		gameLayer->isRestart = false;

		this->unscheduleUpdate();
	}

	if (gameLayer->pressF)
	{
		scheduleOnce(schedule_selector(MainScene01::Restart), 0.01f);
		gameLayer->pressF = false;

		this->unscheduleUpdate();
	}
}

void MainScene01::Restart(float f)
{
	/*gameLayer->removeAllChildrenWithCleanup(true);

	gameLayer = &GameManager::getInstance();
	gameLayer->getInstance();
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(2);
	gameLayer->init();
	this->addChild(gameLayer);*/

	/*_director->getTextureCache()->removeUnusedTextures();*/  //<- 렉 걸리게하는 주범! 

	gameLayer->removeAllChildren();
	gameLayer->removeFromParentAndCleanup(true);

	auto pScene = MainScene01::createScene();
	Director::getInstance()->replaceScene(pScene);
}