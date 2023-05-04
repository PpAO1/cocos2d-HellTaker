#pragma once
#include "cocos2d.h"
#include "stdafx.h"

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

	//타일맵에서 포지션
	Coordinate _mapPos;
	
	void PlayerIdleAnim(float f);
	void PlayerMoveAnim();
	void PlayerHitAnim();
	void PlayerDamagedAnim();
	void PlayerMove(cocos2d::Vec2 pos);
	void PlayerClearAnim1(float f);
	void PlayerClearAnim2(float f);
	void PlayerClearAnim3(float f);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
	void GOAL();
};