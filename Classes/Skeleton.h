#pragma once
#include "cocos2d.h"

class Skeleton : public cocos2d::Layer 
{
private:
	Skeleton();
	~Skeleton();
	static Skeleton* _instance;

public:
	static Skeleton& getInstance();

};