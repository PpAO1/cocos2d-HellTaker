#pragma once
#include "cocos2d.h"

class UI : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(UI);

	int _moveCount;

	cocos2d::Sprite* _startAnim;

	void StartAnim();


};