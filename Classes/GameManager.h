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
#include "Npc.h"


class GameManager : public cocos2d::Layer
{
private:
	GameManager();
	GameManager(int index);
	~GameManager();

	static GameManager* _instance;
	cocos2d::EventListenerKeyboard* _listener;

	Stage stage;
	int index;

public:
	std::vector<std::vector<int>> mapStage;

	//int stage1Map[STAGE1_HEIGHT][STAGE1_WIDTH];

	int MoveChance;
	int stageIndex;

	bool isRestart;
	bool pressF;
	bool isClear;
	bool isGonextMap;

	cocos2d::Vec2 stage1StartPos;

	Player* pPlayer;
	Key* pKey;
	Lock* pLock;
	UI* ui;

	std::vector<Npc*> npcVec;
	std::vector<Skeleton*> skeletonVec;
	std::vector<Rock*> rockVec;

	Coordinate origin;

	static GameManager& getInstance(int index);
	static void ReleaseInstance();

	virtual bool init();
	void FileDataRead();
	void TextFileRead(std::string str, int width, int height);
	void SetPlayerPos(int stageHeight, int stageWidth, int startx, int starty);
	void SetObjectsPos(int stageHeight, int stageWidth);

	template <typename T>
	void SetObjects(T node, int j, int i, int startx, int starty);
	void Logic(int offsetX, int offsetY, int oriX, int oriY, cocos2d::Vec2 pos);
	void Damaged(float f);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
	
	void StageClear(float f);
	void PlayerDie();
	void NextStage(float f);
};

template<typename T>
inline void GameManager::SetObjects(T node, int j, int i, int startx, int starty)
{
	node->setPosition((startx + (j * CELL)), (starty + (i * CELL)));
	node->setAnchorPoint(Vec2(0, 0));
	node->setZOrder(3);
	this->addChild(node);
}
