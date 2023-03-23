#pragma once
#include "cocos2d.h"
#include "UI.h"
#include "stdafx.h"

class GameManager : public cocos2d::Layer
{
private:
	GameManager();
	~GameManager();
	static GameManager* _instance;
	UI* ui;

public:
	static GameManager& getInstance();

	virtual bool init();
	void FileDataRead();

};