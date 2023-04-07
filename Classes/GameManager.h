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
	~GameManager();

	static GameManager* _instance;
	cocos2d::EventListenerKeyboard* _listener;

	Stage stage;

public:
	int stage1Map[STAGE1_HEIGHT][STAGE1_WIDTH];

	cocos2d::Vec2 stage1StartPos;
	cocos2d::Label* moveCount;
	cocos2d::Label* stageCount;
	Player* pPlayer;
	Key* pKey;
	Lock* pLock;

	std::vector<Skeleton*> skeletonVec;
	std::vector<Rock*> rockVec;

	static GameManager& getInstance();
	virtual bool init();
	void FileDataRead();
	void TextFileRead(std::string str, int width);
	void SetPlayerPos(int stageHeight, int stageWidth);
	void SetObjectsPos(int stageHeight, int stageWidth);

	template <typename T>
	void SetObjects(T node, int j, int i);
	void Logic(int offsetX, int offsetY, int oriX, int oriY, cocos2d::Vec2 pos);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
	
	void StageClear();
	void ReStart();

};

template<typename T>
inline void GameManager::SetObjects(T node, int j, int i)
{
	node->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
	node->setAnchorPoint(Vec2(0, 0));
	node->setZOrder(3);
	this->addChild(node);
}
