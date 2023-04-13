#include "Npc.h"
#include "Prologue2.h"

USING_NS_CC;

Npc::Npc()
{
}

Npc::~Npc()
{
}

Npc::Npc(int stage)
{
	switch (stage)
	{
	case 0:
		pNpc = Sprite::create("Sprite/pandemonica_finalModel0001.png");
		stageNum = stage;
		this->init();
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

bool Npc::init()
{
	this->setContentSize(pNpc->getContentSize());
	this->addChild(pNpc);
	this->LoveSignAnim();
	switch (stageNum)
	{
	case 0:
		Stage1NpcAnim();
		break;
	case 1:
		break;
	case 2:
		break;
	}
	return true;
}

void Npc::LoveSignAnim()
{
	loveSign = Sprite::create("Sprite/lovesign.png");
	loveSign->setPosition((pNpc->getPositionX() - 60), pNpc->getPositionY() + 10);
	loveSign->setAnchorPoint(Vec2(0, 0));
	loveSign->setZOrder(1);
	this->addChild(loveSign);

	// 러브마크 아래위로 움직이게 함.
	auto action1 = MoveBy::create(0.23f, Vec2(0, 10));
	auto action2 = MoveBy::create(0.23f, Vec2(0, -10));

	auto loveMove = Sequence::create(action1, action2, nullptr);
	auto rep = RepeatForever::create(loveMove);
	loveSign->runAction(rep);
}

void Npc::Stage1NpcAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str[100] = { 0, };

	for (int i = 1; i < 13; i++)
	{
		sprintf(str, "Sprite/pandemonica_finalModel000%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pNpc->runAction(rep);
}
