#include "Lock.h"

USING_NS_CC;

Lock* Lock::_instance = nullptr;

Lock::Lock()
{
}

Lock::~Lock()
{
}

Lock& Lock::getInstance()
{
	_instance = new Lock();

	if (_instance && _instance->init())
		_instance->autorelease();
	else
		CC_SAFE_DELETE(_instance);

	return *_instance;
}

bool Lock::init()
{
	pLock = Sprite::create("Sprite/backup_lockbox.png");
	this->setContentSize(pLock->getContentSize());
	this->addChild(pLock);
	return true;
}

void Lock::UnLock()
{
	auto unlockEffect = Sprite::create("Sprite/huge_vfx0001.png");
	unlockEffect->setPosition(pLock->getPosition());
	unlockEffect->setZOrder(1);
	this->addChild(unlockEffect);

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
	unlockEffect->runAction(Sequence::create(EffectAnimate, removeanim, nullptr));

	pLock->removeAllChildrenWithCleanup(true);
}
