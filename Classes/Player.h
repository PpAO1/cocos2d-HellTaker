#pragma once
#include "cocos2d.h"

class Player : public cocos2d::Layer
{
private:
	Player ();
	~Player ();
	static Player* _instance;
	cocos2d::EventListenerKeyboard* _listener;

public:
	cocos2d::Sprite* pPlayer;
	static Player& getInstance();
	virtual bool init();
	
	void PlayerIdleAnim(float f);
	void PlayerMoveAnim();
	void PlayerHitAnim();
	void PlayerDamagedAnim();
	void update(float f);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
};