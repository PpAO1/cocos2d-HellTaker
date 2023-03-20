#include "Prologue.h"
#include "Prologue2.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* Prologue::createScene()
{
	return Prologue::create();
}

bool Prologue::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	main = Sprite::create("Texture2D/Texture2D #21.png");
	main->setPosition(960, 540);
	this->addChild(main);

	TTFConfig ttfconfig("Font/The_Jamsil_5_Bold.ttf",30);

	plabel = Label::createWithTTF(ttfconfig, "Cocos2d 모작 < Helltaker >\n Prod : [ 정재환 ]",TextHAlignment::CENTER);
	plabel->setTextColor(Color4B::WHITE);
	plabel->setPosition(960, 540);
	plabel->setZOrder(2);
	this->addChild(plabel);

	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(Prologue::SceneEnd), 4.0f);

	return true;
}

void Prologue::update(float f)
{
	main->setScale(main->getScale() + (f * 0.05f));
	
	if (main->getScale() > 1.15f)
	{
		plabel->setOpacity(plabel->getOpacity() - (f * 1000));

		if (plabel->getOpacity() == 0)
		{
			plabel->setVisible(false);
		}
	}
}

void Prologue::SceneEnd(float f)
{
	_director->getTextureCache()->removeUnusedTextures();
	auto pScene = Prologue2::createScene();
	Director::getInstance()->replaceScene(pScene);
}
