#pragma once
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

enum prologueEnum
{
	OPENING1 = 0, OPENING2 = 1, MENUCHOICE = 2, START1 = 3, START2 = 4, START3 = 5, START4 = 6, START5 = 7, CHAPTERCHOICE = 8, GAMESTART = 10, EXIT = 11
};

class Prologue2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void SetMenuLabel(cocos2d::TTFConfig& ttfconfig, cocos2d::Label* label, std::string text, cocos2d::Vec2 pos);

	CREATE_FUNC(Prologue2);

	cocos2d::Sprite* pbackground1;
	cocos2d::Sprite* pbackground2;
	cocos2d::Sprite* button;
	cocos2d::Sprite* menuButton;
	cocos2d::Sprite* menuButton2;
	cocos2d::Sprite* menuButton3;
	cocos2d::Sprite* chapterButton0;
	cocos2d::Sprite* chapterButton1;
	cocos2d::Sprite* chapterButton2;
	cocos2d::Sprite* beel_fly;
	cocos2d::Label* chapterLabel0;
	cocos2d::Label* chapterLabel1;
	cocos2d::Label* chapterLabel2;
	cocos2d::Label* plabel;
	cocos2d::Label* plabel2;
	cocos2d::Label* chapterPlabel0;
	cocos2d::Layer* menuLayer;
	cocos2d::Layer* chapterLayer;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void SetMenuColor(cocos2d::Color3B color1, cocos2d::Color3B color2, cocos2d::Color3B color3, int index);
	void SetChapterMenuColor(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2, cocos2d::Sprite* sprite3,
		cocos2d::Label* label1, cocos2d::Label* label2, cocos2d::Label* label3, int index, std::string str);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onEnter();
	void onExit();
	void ButtonAnim();
	void RepeatBackground();

	

private:
	cocos2d::EventListenerKeyboard* _listener;
	bool _enter, _up, _down;
	int order, menuOrder, chapterOrder;

	cocos2d::Sprite* cutScene1;
	cocos2d::Sprite* cutScene2;
	cocos2d::Sprite* cutScene3;

	void update(float f);
	void Opening1(float f);
	void Opening2(float f);
	void Start0(float f);
	void Start1(float f);
	void Start2(float f);
	void Start3(float f);
	void Start4(float f);
	void Start5(float f);
	void Start6(float f);
	void GameExit(float f);
	void ChapterChoice(float f);
	void GameStart(float f);
	void SetMenu();
	void SetChapterSelectMenu();


};