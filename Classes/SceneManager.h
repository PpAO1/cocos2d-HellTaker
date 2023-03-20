#pragma once
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

class SceneManager
{
private :
	SceneManager() {};
	~SceneManager() {};
	static SceneManager* instance;

public:
	static SceneManager& getInstance() {
		
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}

		return *instance;
	}

	virtual bool init();


	cocos2d::Sprite* main;
	cocos2d::Label* plabel;

};