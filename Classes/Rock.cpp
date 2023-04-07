#include "Rock.h"

USING_NS_CC;

Rock* Rock::_instance = nullptr;

Rock::Rock()
{
}

Rock::~Rock()
{
}

Rock& Rock::getInctance()
{
	_instance = new Rock();
	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

void Rock::RockMove(cocos2d::Vec2 pos)
{
	auto rockmove = MoveBy::create(0.15f, pos);
	rock->runAction(rockmove);
}

void Rock::RockMoveAnim()
{
	auto dust = Sprite::create("Sprite/small_vfx0001.png");
	dust->setPosition(rock->getPosition());
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
	RemoveSelf* removeanim = RemoveSelf::create(dustAnimation);
	dust->runAction(Sequence::create(dustAnimation, removeanim, nullptr));

	//-----------------------------------------------------------------

	auto damagedEffect = Sprite::create("Sprite/small_vfx0015.png");
	damagedEffect->setPosition(rock->getPosition());
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
	RemoveSelf* removeanim2 = RemoveSelf::create(EffectAnimate);
	damagedEffect->runAction(Sequence::create(EffectAnimate, removeanim2, nullptr));
}

bool Rock::init()
{
	rock = Sprite::create("Sprite/boxExport0001.png");
	this->setContentSize(rock->getContentSize());
	this->addChild(rock);
	return true;
}
