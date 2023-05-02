#pragma once
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

class MainCutScene01 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainCutScene01);

	int index;

	cocos2d::EventListenerKeyboard* _listener;

	cocos2d::Sprite* main;
	cocos2d::Sprite* button;
	cocos2d::Sprite* npc;
	cocos2d::Sprite* npc2;
	cocos2d::Label* nameLabel;
	cocos2d::Label* textLabel;
	cocos2d::Sprite* menu;
	cocos2d::Label* menuLabel;

	void ButtonAnim();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();

	void update(float f);
	void Enter0(float f);
	void Enter1(float f);
	void Enter2(float f);
};