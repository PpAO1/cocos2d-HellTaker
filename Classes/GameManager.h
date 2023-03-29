#pragma once
#include "cocos2d.h"
#include "UI.h"
#include "stdafx.h"
#include "Player.h"
#include "Skeleton.h"
#include "Spike.h"
#include "Rock.h"
#include "Lock.h"
#include "Key.h"

class GameManager : public cocos2d::Layer
{
private:
	GameManager();
	~GameManager();

	static GameManager* _instance;
	Stage stage;

public:
	int stage1Map[STAGE1_HEIGHT][STAGE1_WIDTH];

	cocos2d::Vec2 stage1StartPos;

	static GameManager& getInstance();
	virtual bool init();
	void FileDataRead();
	void TextFileRead(std::string str, int width);
	void SetPlayerPos(int stageHeight, int stageWidth);
	void SetObjectsPos(int stageHeight, int stageWidth);
	void ReStart();

};