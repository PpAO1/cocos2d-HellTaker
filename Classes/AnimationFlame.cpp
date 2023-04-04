#include "AnimationFlame.h"

USING_NS_CC;

AnimationFlame::AnimationFlame()
{
}

AnimationFlame::~AnimationFlame()
{
}

void AnimationFlame::AdleAnim(int start, int end, const char* spriteStr, cocos2d::Sprite* sprite)
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = start; i < end; i++)
	{
		sprintf(str, spriteStr, i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	sprite->runAction(rep);
}

//void AnimationFlame::EffectAim(int start, int end, std::string spritestr, const char* spriteStrAnim, cocos2d::Sprite* sprite, Node* node)
//{
//	auto effect = Sprite::create(spritestr);
//	effect->setPosition(sprite->getPosition());
//	effect->setZOrder(1);
//	//this->addChild(effect);
//	node->addChild(effect);
//
//	auto dustAnim = Animation::create();
//
//	dustAnim->setDelayPerUnit(0.07f);
//
//	char str[100] = { 0, };
//
//	for (int i = start; i < end; i++)
//	{
//		sprintf(str, spriteStrAnim, i);
//		dustAnim->addSpriteFrameWithFile(str);
//	}
//
//	auto dustAnimation = Animate::create(dustAnim);
//	RemoveSelf* removeanim = RemoveSelf::create(dustAnimation);
//	effect->runAction(Sequence::create(dustAnimation, removeanim, nullptr));
//}

void AnimationFlame::MomentAnim()
{

}
