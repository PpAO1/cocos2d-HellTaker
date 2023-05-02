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

	index = 0;

	auto wlayer = LayerColor::create(Color4B(2, 2, 27, 255));
	wlayer->setPosition(Vec2(0, 0));
	wlayer->setAnchorPoint(Vec2(0, 0));
	this->addChild(wlayer);

	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);
	TTFConfig ttfconfig2("Font/The_Jamsil_4_Medium.ttf", 40);

	main = Sprite::create("Sprite/dialogueBG_hell.png");
	main->setPosition(0, 400);
	main->setAnchorPoint(Vec2(0, 0));
	main->setZOrder(2);
	this->addChild(main);

	npc = Sprite::create("Sprite/pand_idle.png");
	npc->setPosition(960, 720);
	npc->setAnchorPoint(Vec2(0.5f, 0.5f));
	npc->setZOrder(3);
	this->addChild(npc);

	button = Sprite::create("Sprite/booper001.png");
	button->setColor(Color3B(255, 102, 102));
	button->setPosition(960, 100);
	this->addChild(button);

	nameLabel = Label::createWithTTF(ttfconfig2, "[ 지친 악마, 판데모니카 ]", TextHAlignment::CENTER);
	nameLabel->setTextColor(Color4B(255, 102, 102, 255));
	nameLabel->setPosition(960, 340);
	this->addChild(nameLabel);

	textLabel = Label::createWithTTF(ttfconfig, "지옥 고객 서비스 센터의 판데모니카입니다.\n무엇을 도와드릴까요?", TextHAlignment::CENTER);
	textLabel->setTextColor(Color4B::WHITE);
	textLabel->setPosition(960, 270);
	textLabel->setZOrder(2);
	this->addChild(textLabel);

	this->ButtonAnim();
	this->scheduleUpdate();

	return true;
}

void MainCutScene01::ButtonAnim()
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

void MainCutScene01::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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

void MainCutScene01::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{

}

void MainCutScene01::onEnter()
{
	Scene::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(MainCutScene01::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(MainCutScene01::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void MainCutScene01::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Scene::onExit();
}

void MainCutScene01::update(float f)
{
	if (index == 0)
		scheduleOnce(schedule_selector(MainCutScene01::Enter0), 0.01f);
	else if (index == 1)
		scheduleOnce(schedule_selector(MainCutScene01::Enter1), 0.01f);
	else if (index == 2)
		scheduleOnce(schedule_selector(MainCutScene01::Enter2), 0.5f);
}

void MainCutScene01::Enter0(float f)
{
	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);

	button->setOpacity(0);
	menu = Sprite::create("Sprite/button0003.png");
	menu->setPosition(960, -150);
	menu->setColor(Color3B(255, 102, 102));
	this->addChild(menu);

	menuLabel = Label::createWithTTF(ttfconfig, "오히려 '그 쪽'을 도와줘야 할 판인데?", TextHAlignment::CENTER);
	menuLabel->setPosition(menu->getPosition());
	this->addChild(menuLabel);

	auto moveaction = MoveBy::create(0.25f, Vec2(0, 300));
	auto moveaction2 = MoveBy::create(0.25f, Vec2(0, 300));
	menu->runAction(moveaction);
	menuLabel->runAction(moveaction2);
}

void MainCutScene01::Enter1(float f)
{
	textLabel->setString("그래주면 좋겠네요. 지금 커피 한잔이 너무 마시고 싶은데\n지금 제정신이 아니네요.");
	menu->setOpacity(0);
	menuLabel->setOpacity(0);

	npc2 = Sprite::create("Sprite/pand_flust.png");
	npc2->setPosition(960, 720);
	npc2->setAnchorPoint(Vec2(0.5f, 0.5f));
	npc2->setZOrder(3);
	this->addChild(npc2);

	auto success = Sprite::create("Sprite/success0001.png");
	success->setPosition(960, 150);
	success->setZOrder(1);
	this->addChild(success);

	auto successAnim = Animation::create();

	successAnim->setDelayPerUnit(0.1f);

	char str[100] = { 0, };

	for (int i = 1; i < 9; i++)
	{
		sprintf(str, "Sprite/success000%d.png", i);
		successAnim->addSpriteFrameWithFile(str);
	}

	auto successAnimation = Animate::create(successAnim);
	success->runAction(successAnimation);
}

void MainCutScene01::Enter2(float f)
{
	_director->getTextureCache()->
		removeUnusedTextures();

	Director::getInstance()->popScene();
}
