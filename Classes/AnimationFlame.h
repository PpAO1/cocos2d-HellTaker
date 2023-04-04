#pragma once
#include "cocos2d.h"

class AnimationFlame
{
public:
	AnimationFlame();
	~AnimationFlame();

	void AdleAnim(int start, int end, const char* spriteStr, cocos2d::Sprite* sprite);
	//void EffectAim(int start, int end, std::string spritestr, const char* spriteStrAnim, cocos2d::Sprite* sprite, Node* node);
	void MomentAnim();
};