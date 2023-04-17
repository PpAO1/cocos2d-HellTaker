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
	
	index = 0;

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);

	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);
	TTFConfig ttfconfig2("Font/The_Jamsil_4_Medium.ttf", 40);

	main = Sprite::create("Sprite/dialogueBG_hell.png");
	main->setPosition(0, 400);
	main->setAnchorPoint(Vec2(0, 0));
	main->setZOrder(2);
	this->addChild(main);

	button = Sprite::create("Sprite/booper001.png");
	button->setColor(Color3B(255, 102, 102));
	button->setPosition(960, 100);
	this->addChild(button);

	nameLabel = Label::createWithTTF(ttfconfig2, "[ »ö¿åÀÇ ¾Ç¸¶, ¸ðµ¥¿ì½º ]", TextHAlignment::CENTER);
	nameLabel->setTextColor(Color4B(255, 102, 102, 255));
	nameLabel->setPosition(960, 340);
	this->addChild(nameLabel);

	textLabel = Label::createWithTTF(ttfconfig, "³Ê¶û ³ª¶û, Áö±Ý ´çÀå ÇÏÀÚ.", TextHAlignment::CENTER);
	textLabel->setTextColor(Color4B::WHITE);
	textLabel->setPosition(960, 270);
	this->addChild(textLabel);

	this->ButtonAnim();

	return true;
}

void MainCutScene00::ButtonAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.05f);

	char str[100] = { 0 };
	for (int i = 1; i < 18; i++)
	{
		sprintf(str, "Sprite/booper00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	button->runAction(rep);
}

void MainCutScene00::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
		index++;
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	}
}

void MainCutScene00::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{

}

void MainCutScene00::onEnter()
{
	Scene::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(MainCutScene00::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(MainCutScene00::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void MainCutScene00::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Scene::onExit();
}

void MainCutScene00::update(float f)
{

}