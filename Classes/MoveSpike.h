#pragma once
#include "cocos2d.h"

class MoveSpike : public cocos2d::Layer
{
private:
	MoveSpike();
	MoveSpike(bool isup);
	~MoveSpike();
	static MoveSpike* _instance;
	cocos2d::EventListenerKeyboard* _listener;

public:
	cocos2d::Sprite* pMoveSpike;
	static MoveSpike& getInstance();
	bool isUp;
	virtual bool init();
	void SpikeAnim();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
};