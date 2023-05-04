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
	scheduleOnce(schedule_selector(Skeleton::SkeletonIdleAnim), 0.01f);
	return true;
}

void Skeleton::SkeletonIdleAnim(float f)
{
	pSkeleton->stopAllActions();

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
	pSkeleton->stopAllActions();

	auto damagedEffect = Sprite::create("Sprite/small_vfx0001.png");
	damagedEffect->setPosition(pSkeleton->getPosition());
	damagedEffect->setZOrder(1);
	this->addChild(damagedEffect);

	auto EffectAnim = Animation::create();

	EffectAnim->setDelayPerUnit(0.07f);

	char str3[100] = { 0, };

	for (int i = 1; i < 4; i++)
	{
		sprintf(str3, "Sprite/small_vfx000%d.png", i);
		EffectAnim->addSpriteFrameWithFile(str3);
	}

	auto EffectAnimate = Animate::create(EffectAnim);
	RemoveSelf* removeanim = RemoveSelf::create(EffectAnimate);
	damagedEffect->runAction(Sequence::create(EffectAnimate, removeanim, nullptr));

	// -------------------------------------------------------------

	auto dust = Sprite::create("Sprite/small_vfx0001.png");
	dust->setPosition(pSkeleton->getPosition());
	dust->setZOrder(1);
	this->addChild(dust);

	auto dustAnim = Animation::create();

	dustAnim->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "Sprite/small_vfx000%d.png", i);
		dustAnim->addSpriteFrameWithFile(str);
	}

	auto dustAnimation = Animate::create(dustAnim);
	RemoveSelf* removeanim2 = RemoveSelf::create(dustAnimation);
	dust->runAction(Sequence::create(dustAnimation, removeanim2, nullptr));

	//-----------------------------------------------------------------

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str2[100] = { 0, };

	for (int i = 198; i < 204; i++)
	{
		sprintf(str2, "Sprite/assets100V20%d.png", i);
		animation->addSpriteFrameWithFile(str2);
	}

	auto animate = Animate::create(animation);
	pSkeleton->runAction(animate);
	scheduleOnce(schedule_selector(Skeleton::SkeletonIdleAnim), 0.42f);

	//----------------------------------------------------------------
}

void Skeleton::SkeletonDieAnim(cocos2d::Vec2 pos)
{
	auto damagedEffect = Sprite::create("Sprite/small_vfx0015.png");
	damagedEffect->setPosition(pSkeleton->getPosition()+ pos);
	damagedEffect->setZOrder(1);
	this->addChild(damagedEffect);

	auto EffectAnim = Animation::create();

	EffectAnim->setDelayPerUnit(0.1f);

	char str3[100] = { 0, };

	for (int i = 15; i < 18; i++)
	{
		sprintf(str3, "Sprite/small_vfx00%d.png", i);
		EffectAnim->addSpriteFrameWithFile(str3);
	}

	auto EffectAnimate = Animate::create(EffectAnim);
	RemoveSelf* removeanim = RemoveSelf::create(EffectAnimate);
	damagedEffect->runAction(Sequence::create(EffectAnimate, removeanim, nullptr));

	//-----------------------------------------------------------------------------

	auto Born = Sprite::create("Sprite/particle0004.png");
	Born->setPosition((pSkeleton->getPositionX() + pos.x), (pSkeleton->getPositionY() - 20 + pos.y));
	Born->setZOrder(1);
	this->addChild(Born);

	auto skeletonRemove = Hide::create();
	auto BornAction = JumpBy::create(0.4f, Vec2(0, 0), 70, 1);
	auto BornAction2 = Hide::create();
	Born->runAction(Sequence::create(BornAction, BornAction2, nullptr));
	pSkeleton->runAction(skeletonRemove);
}

void Skeleton::SkeletonMove(cocos2d::Vec2 pos)
{
	auto skeletonmove = MoveBy::create(0.15f, pos);
	pSkeleton->runAction(skeletonmove);
}
