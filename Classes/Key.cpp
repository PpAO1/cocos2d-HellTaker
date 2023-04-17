#include "Key.h"

USING_NS_CC;

Key::Key()
{
	this->init();
	isGetKey = false;
}

Key::~Key()
{
}

bool Key::init()
{
	pKey = Sprite::create("Sprite/assets100V2014.png");
	this->setContentSize(pKey->getContentSize());
	this->addChild(pKey);
	this->KeyAnim();
	return true;
}

void Key::KeyAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 4; i < 16 ; i++)
	{
		sprintf(str, "Sprite/assets100V201%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pKey->runAction(rep);
}

void Key::KeyEating()
{
	auto eatingEffect = Sprite::create("Sprite/huge_vfx0001.png");
	eatingEffect->setPosition(pKey->getPosition());
	eatingEffect->setZOrder(1);
	this->addChild(eatingEffect);

	auto EffectAnim = Animation::create();

	EffectAnim->setDelayPerUnit(0.07f);

	char str3[100] = { 0, };

	for (int i = 1; i < 10; i++)
	{
		sprintf(str3, "Sprite/huge_vfx000%d.png", i);
		EffectAnim->addSpriteFrameWithFile(str3);
	}

	auto EffectAnimate = Animate::create(EffectAnim);
	RemoveSelf* removeanim = RemoveSelf::create(EffectAnimate);
	eatingEffect->runAction(Sequence::create(EffectAnimate, removeanim, nullptr));

	pKey->setOpacity(0);
	isGetKey = true;
}
