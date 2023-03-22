#pragma once
#include "cocos2d.h"
#include "UI.h"

class GameManager : public cocos2d::Layer
{
private:
	GameManager();
	~GameManager();
	static GameManager* _instance;
	UI* ui;

public:
	cocos2d::Node _listener;
	static GameManager& getInstance();

	virtual bool init();

};