#include "MainScene00.h"
#include "GameManager.h"


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

	GameManager* gameLayer = &GameManager::getInstance();
	gameLayer->getInstance();
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setZOrder(1000);
	gameLayer->init();
	this->addChild(gameLayer);

	main = Sprite::create("Sprite/chapterBG0001.png");
	main->setAnchorPoint(Vec2(0, 0));
	main->setPosition(0, 0);
	main->setZOrder(1);
	this->addChild(main);

	return true;
}

void MainScene00::SceneEnd(float f)
{
}
