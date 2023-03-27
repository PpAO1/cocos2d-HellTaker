#pragma once
#include "cocos2d.h"
#include "UI.h"
#include "stdafx.h"
#include "Player.h"
#include "Skeleton.h"
#include "Spike.h"

class GameManager : public cocos2d::Layer
{
private:
	GameManager();
	~GameManager();

	static GameManager* _instance;
	UI* ui;
	Stage stage;

public:
	int stage1Map[STAGE1_HEIGHT][STAGE1_WIDTH];
	static GameManager& getInstance();
	virtual bool init();
	void FileDataRead();
	void TextFileRead(std::string str, int width);
	void SetPlayerPos(int stageHeight, int stageWidth); // �Ű������� 2���� �迭�� �ް� ������ ������ �𸣰ڴ�.
	void SetObjectsPos(int stageHeight, int stageWidth);
	void ReStart();

};