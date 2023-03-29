#pragma once
#include "cocos2d.h"

class UI : public cocos2d::Layer
{
private:
	UI();
	~UI();
	static UI* _instance;
public:
	virtual bool init();

	int _moveCount;

	cocos2d::Sprite* _startAnim;
	cocos2d::Sprite* right_spr;
	cocos2d::Sprite* left_spr;
	cocos2d::Sprite* right_spr2;
	cocos2d::Sprite* left_spr2;

	static UI& getInstance();
	void StartAnim();
	void Spritecrete(cocos2d::Sprite* sprite, std::string str, cocos2d::Vec2 pos, cocos2d::Vec2 anchorpos, int zorder, bool Flipped);


};