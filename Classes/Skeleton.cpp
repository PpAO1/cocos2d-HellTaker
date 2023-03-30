#include "Skeleton.h"

USING_NS_CC;
Skeleton* Skeleton::_instance = nullptr;

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
}

Skeleton& Skeleton::getInstance()
{
	_instance = new Skeleton();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Skeleton::init()
{
	pSkeleton = Sprite::create("Sprite/assets100V20230.png");
	this->setContentSize(pSkeleton->getContentSize());
	this->addChild(pSkeleton);
	this->SkeletonIdleAnim();
	return true;
}

void Skeleton::SkeletonIdleAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);
	
	char str[100] = { 0, };

	for (int i = 25; i < 37; i++)
	{
		sprintf(str, "Sprite/assets100V202%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pSkeleton->runAction(rep);
}

void Skeleton::SkeletonDamagedAnim()
{

}

void Skeleton::SkeletonDieAnim()
{
}

void Skeleton::update(float f)
{
}
