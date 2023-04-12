#pragma once
#include "cocos2d.h"
#include "stdafx.h"

class Spike : public cocos2d::Layer
{
private:
	cocos2d::EventListenerKeyboard* _listener;
public:
	Spike();
	~Spike();
	Spike(int objNum, bool up);

	bool isMove;
	bool isUp;
	cocos2d::Sprite* pSpike;
	virtual bool init();

	void SpikeAnim();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
};