#include "UI.h"

USING_NS_CC;

Scene* UI::createScene()
{
	return UI::create();
}

bool UI::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_startAnim = Sprite::create("Sprite/transition0002.png");
	return true;
}

void UI::StartAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.05f);

	char str[100] = { 0, };

	for (int i = 2; i < 31; i++)
	{
		sprintf(str, "Sprite/transition000%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	_startAnim->runAction(rep);
}
