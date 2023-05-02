#include "MainCutScene03.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* MainCutScene03::createScene()
{

	return MainCutScene03::create();
}

bool MainCutScene03::init()
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

	npc = Sprite::create("Sprite/mal_idle.png");
	npc->setPosition(960, 680);
	npc->setAnchorPoint(Vec2(0.5f, 0.5f));
	npc->setZOrder(3);
	this->addChild(npc);

	button = Sprite::create("Sprite/booper001.png");
	button->setColor(Color3B(255, 102, 102));
	button->setPosition(960, 100);
	this->addChild(button);

	nameLabel = Label::createWithTTF(ttfconfig2, "[ 깐깐한 악마, 말리나 ]", TextHAlignment::CENTER);
	nameLabel->setTextColor(Color4B(255, 102, 102, 255));
	nameLabel->setPosition(960, 340);
	this->addChild(nameLabel);

	textLabel = Label::createWithTTF(ttfconfig, "얼씨구, 대가리 빈 멍청이들이 더 왔어... 저 못생긴 놈은\n처음보네.  \n어디서 놀다온 사람이냐 넌?", TextHAlignment::CENTER);
	textLabel->setTextColor(Color4B::WHITE);
	textLabel->setPosition(960, 270);
	textLabel->setZOrder(2);
	this->addChild(textLabel);

	this->ButtonAnim();
	this->scheduleUpdate();

	return true;
}

void MainCutScene03::ButtonAnim()
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

void MainCutScene03::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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

void MainCutScene03::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{

}

void MainCutScene03::onEnter()
{
	Scene::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(MainCutScene03::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(MainCutScene03::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void MainCutScene03::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Scene::onExit();
}

void MainCutScene03::update(float f)
{
	if (index == 0)
		scheduleOnce(schedule_selector(MainCutScene03::Enter0), 0.01f);
	else if (index == 1)
		scheduleOnce(schedule_selector(MainCutScene03::Enter1), 0.01f);
	else if (index == 2)
		scheduleOnce(schedule_selector(MainCutScene03::Enter2), 0.5f);
}

void MainCutScene03::Enter0(float f)
{
	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);

	button->setOpacity(0);
	menu = Sprite::create("Sprite/button0003.png");
	menu->setPosition(960, -150);
	menu->setColor(Color3B(255, 102, 102));
	this->addChild(menu);

	menuLabel = Label::createWithTTF(ttfconfig, "그쪽이랑 노는게 가장 재밌어 보이는데.", TextHAlignment::CENTER);
	menuLabel->setPosition(menu->getPosition());
	this->addChild(menuLabel);

	auto moveaction = MoveBy::create(0.25f, Vec2(0, 300));
	auto moveaction2 = MoveBy::create(0.25f, Vec2(0, 300));
	menu->runAction(moveaction);
	menuLabel->runAction(moveaction2);
}

void MainCutScene03::Enter1(float f)
{
	textLabel->setString("뭐... 비디오 게임 같은거? 좋지 안될거 있나. 턴제 전투 게임만\n 좋아한다면 별로 상관은 없어.");
	menu->setOpacity(0);
	menuLabel->setOpacity(0);
	npc->setOpacity(0);

	npc2 = Sprite::create("Sprite/mal_puzzled.png");
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

void MainCutScene03::Enter2(float f)
{
	_director->getTextureCache()->
		removeUnusedTextures();

	Director::getInstance()->popScene();
}