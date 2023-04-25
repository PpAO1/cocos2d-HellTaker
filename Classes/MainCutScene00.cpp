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
	isEnd = false;

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

	npc = Sprite::create("Sprite/mod_idle.png");
	npc->setPosition(960, 720);
	npc->setAnchorPoint(Vec2(0.5f, 0.5f));
	npc->setZOrder(3);
	this->addChild(npc);

	button = Sprite::create("Sprite/booper001.png");
	button->setColor(Color3B(255, 102, 102));
	button->setPosition(960, 100);
	this->addChild(button);

	nameLabel = Label::createWithTTF(ttfconfig2, "[ 색욕의 악마, 모데우스 ]", TextHAlignment::CENTER);
	nameLabel->setTextColor(Color4B(255, 102, 102, 255));
	nameLabel->setPosition(960, 340);
	this->addChild(nameLabel);

	textLabel = Label::createWithTTF(ttfconfig, "너랑 나랑, 지금 당장 하자.", TextHAlignment::CENTER);
	textLabel->setTextColor(Color4B::WHITE);
	textLabel->setPosition(960, 270);
	this->addChild(textLabel);

	this->ButtonAnim();
	this->scheduleUpdate();

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
	if (index == 0)
		scheduleOnce(schedule_selector(MainCutScene00::Enter0), 0.01f);
	else if (index == 1)
		scheduleOnce(schedule_selector(MainCutScene00::Enter1), 0.01f);
	else if (index == 2)
		scheduleOnce(schedule_selector(MainCutScene00::Enter2), 0.5f);
}

void MainCutScene00::Enter0(float f)
{
	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);

	button->setOpacity(0);
	menu = Sprite::create("Sprite/button0003.png");
	menu->setPosition(960, -150);
	menu->setColor(Color3B(255, 102, 102));
	this->addChild(menu);

	menuLabel = Label::createWithTTF(ttfconfig, "그럴 시간 없어. 여자들 모으느라 바빠", TextHAlignment::CENTER);
	menuLabel->setPosition(menu->getPosition());
	this->addChild(menuLabel);

	auto moveaction = MoveBy::create(0.25f, Vec2(0, 300));
	auto moveaction2 = MoveBy::create(0.25f, Vec2(0, 300));
	menu->runAction(moveaction);
	menuLabel->runAction(moveaction2);
}

void MainCutScene00::Enter1(float f)
{
	textLabel->setString("악마 하렘? 가여워라... 다들 네 영혼을 찢으려 들텐데, 이건 '꼭' 봐야겠다.");
	menu->setOpacity(0);
	menuLabel->setOpacity(0);

	npc2 = Sprite::create("Sprite/mod_close.png");
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

void MainCutScene00::Enter2(float f)
{
	_director->getTextureCache()->
		removeUnusedTextures();
	isEnd = true;

	Director::getInstance()->popScene();
}
