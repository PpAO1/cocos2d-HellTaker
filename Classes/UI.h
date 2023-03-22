#pragma once
#include "cocos2d.h"

class UI : public cocos2d::Layer
{
public:
	virtual bool init();

	int _moveCount;

	cocos2d::Sprite* _startAnim;

	void StartAnim();


};