#pragma once
#include "cocos2d.h"

class Skeleton : public cocos2d::Layer 
{
private:
	Skeleton();
	~Skeleton();
	static Skeleton* _instance;

public:
	cocos2d::Sprite* pSkeleton;
	static Skeleton& getInstance();
	virtual bool init();

	void SkeletonIdleAnim(float f);
	void SkeletonDamagedAnim();
	void SkeletonDieAnim();

	void update(float f);

};