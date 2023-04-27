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
		pNpc = Sprite::create("Sprite/modeus_finalModel0001.png");
		stageNum = stage;
		this->init();
		break;
	case 1:
		pNpc = Sprite::create("Sprite/pandemonica_finalModel0001.png");
		stageNum = stage;
		this->init();
		break;
	case 2:
		pNpc = Sprite::create("Sprite/cerberus_finalModel0001.png");
		stageNum = stage;
		this->init();
		break;
	case 3:
		pNpc = Sprite::create("Sprite/malina_finalModel0001.png");
		stageNum = stage;
		this->init();
		break;
	default:
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
		NpcAnim("Sprite/modeus_finalModel000%d.png");
		break;
	case 1:
		NpcAnim("Sprite/pandemonica_finalModel000%d.png");
		break;
	case 2:
		NpcAnim("Sprite/cerberus_finalModel000%d.png");
		break;
	case 3:
		NpcAnim("Sprite/malina_finalModel000%d.png");
		break;
	default:
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

void Npc::NpcAnim(const char* str)
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.07f);

	char str2[100] = { 0, };

	for (int i = 1; i < 13; i++)
	{
		sprintf(str2, str, i);
		animation->addSpriteFrameWithFile(str2);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pNpc->runAction(rep);
}

void Npc::StageClearAnim1(float f)
{
	loveSign->setOpacity(0);
	auto whiteAction =   FadeOut::create(1.5f);
	pNpc->runAction(whiteAction);

	std::vector<Sprite*> effect;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 50; i++)
	{
		auto sprite = Sprite::create("Sprite/particle0010.png");
		effect.push_back(sprite);
		effect[i]->setScale(0.8f);
		effect[i]->setZOrder(3);
		effect[i]->setPosition(pNpc->getPositionX() + (rand() % 500) - (rand() % 500), pNpc->getPositionY() + (rand() % 500) - (rand() % 500));
		this->addChild(effect[i]);
	}

	for (int i = 0; i < 50; i++)
	{
		auto effectMoveAction = MoveTo::create(0.9f, pNpc->getPosition());
		RemoveSelf* removeanim = RemoveSelf::create(effectMoveAction);
		effect[i]->runAction(Sequence::create(effectMoveAction, removeanim, nullptr));
	}
}

void Npc::stageClaerAnim2(float f)
{
	auto lovePlosion = Sprite::create("Sprite/lovePlosion0001.png");
	lovePlosion->setPosition(pNpc->getPosition());
	lovePlosion->setScale(2.0f);
	this->addChild(lovePlosion);

	auto animation = Animation::create();

	animation->setDelayPerUnit(0.05f);

	char str[100] = { 0, };

	for (int i = 1; i < 16; i++)
	{
		sprintf(str, "Sprite/lovePlosion000%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	lovePlosion->runAction(animate);
}

void Npc::NpcGoal()
{
	scheduleOnce(schedule_selector(Npc::StageClearAnim1), 0.4f);
	scheduleOnce(schedule_selector(Npc::stageClaerAnim2), 2.2f);
}
