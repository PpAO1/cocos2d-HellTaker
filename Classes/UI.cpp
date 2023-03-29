#include "UI.h"

USING_NS_CC;

UI* UI::_instance = nullptr;

UI::UI()
{
}

UI::~UI()
{
}

bool UI::init()
{
	this->setContentSize(Size(_director->getWinSize().width, _director->getWinSize().height));

	_startAnim = Sprite::create("Sprite/transition002.png");
	_startAnim->setPosition(Vec2(960, 0));
	_startAnim->setAnchorPoint(Vec2(0.5f, 0));
	_startAnim->setZOrder(3);
	this->addChild(_startAnim);

	Spritecrete(right_spr, "Sprite/mainUIexport_fUI0001.png", Vec2(1920, 0), Vec2(1, 0), 2, true);
	Spritecrete(left_spr, "Sprite/mainUIexport_fUI0001.png", Vec2(0, 0), Vec2(0, 0), 2, false);
	Spritecrete(right_spr2, "Sprite/mainUIexport_bUI2.png", Vec2(1920, 1080), Vec2(1, 1), 1, true);
	Spritecrete(right_spr2, "Sprite/mainUIexport_bUI2.png", Vec2(0, 1080), Vec2(0, 1), 1, false);

	this->StartAnim();

	return true;
}

UI& UI::getInstance()
{
	_instance = new UI();

	return *_instance;
}

void UI::StartAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.05f);

	char str[100] = { 0, };

	for (int i = 2; i < 31; i++)
	{
		sprintf(str, "Sprite/transition00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	RemoveSelf* removeanim  = RemoveSelf::create(animate);
	_startAnim->runAction(Sequence::create(animate, removeanim, nullptr));
}

void UI::Spritecrete(cocos2d::Sprite* sprite, std::string str, cocos2d::Vec2 pos, cocos2d::Vec2 anchorpos, int zorder, bool Flipped)
{
	sprite = Sprite::create(str);
	sprite->setPosition(pos);
	sprite->setAnchorPoint(anchorpos);
	sprite->setZOrder(zorder);
	sprite->setFlippedX(Flipped);
	this->addChild(sprite);
}