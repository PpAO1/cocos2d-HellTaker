#include "Prologue2.h"
#include "Prologue.h"
#include "MainScene00.h"
//#include "MainScene01.h"
//#include "MainScene02.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

USING_NS_CC;

Scene* Prologue2::createScene()
{
	return Prologue2::create();
}

bool Prologue2::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_enter = _up = _down = false;
	
	order = prologueEnum::OPENING1; //애니메이션 순서

	menuOrder = chapterOrder = 0; //메뉴선택 숫자
	

	auto wlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(wlayer);
	menuLayer = Layer::create();
	this->addChild(menuLayer);
	chapterLayer = Layer::create();
	this->addChild(chapterLayer);
	

	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);
	TTFConfig ttfconfig2("Font/The_Jamsil_6_ExtraBold.ttf", 40);
	button = Sprite::create("Sprite/booper001.png");
	button->setColor(Color3B(255,102,102));
	button->setPosition(960, 200);
	this->addChild(button);

	plabel = Label::createWithTTF(ttfconfig, "당신은 공허에 휩싸인 것을 느꼈다.\n계속 하려면 [ENTER]키를 누르시오.",TextHAlignment::CENTER);
	plabel->setTextColor(Color4B::WHITE);
	plabel->setPosition(960, 270);
	this->addChild(plabel);

	plabel2 = Label::createWithTTF(ttfconfig2, "◀   위대한 파리 베엘제붑   ▶");
	plabel2->setTextColor(Color4B(255, 102, 102, 255));
	plabel2->setPosition(960, 350);
	plabel2->setOpacity(0);
	plabel2->setZOrder(2);
	this->addChild(plabel2);

	pbackground1 = Sprite::create("Texture2D/dialogueBG_abyss02.png");
	pbackground1->setPosition(0, 400);
	pbackground1->setAnchorPoint(Point(0, 0));
	this->addChild(pbackground1);

	pbackground2 = Sprite::create("Texture2D/dialogueBG_abyss02.png");
	pbackground2->setPosition(2032, 400);
	pbackground2->setAnchorPoint(Point(0, 0));
	this->addChild(pbackground2);

	this->RepeatBackground();
	this->ButtonAnim();
	this->scheduleUpdate();

	return true;

}

void Prologue2::SetMenuLabel(cocos2d::TTFConfig& ttfconfig, cocos2d::Label* label,std::string text, cocos2d::Vec2 pos)
{
	label = Label::createWithTTF(ttfconfig, text);
	label->setTextColor(Color4B::WHITE);
	label->setPosition(pos);
}

void Prologue2::ButtonAnim()
{
	auto animation = Animation::create();

	animation->setDelayPerUnit(0.05f);

	char str[100] = { 0 };
	for (int i = 2; i < 20;i++)
	{
		sprintf(str, "Sprite/booper00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	for (int i = 19; i > 3; i--)
	{
		sprintf(str, "Sprite/booper00%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	button->runAction(rep);
}

void Prologue2::RepeatBackground()
{
	auto bgmove = MoveBy::create(13, Vec2(-2032, 0));
	auto bgplace = Place::create(Vec2(0, 400));
	auto bgaction = Sequence::create(bgmove, bgplace, nullptr);
	auto bgactionForever = RepeatForever::create(bgaction);
	pbackground1->runAction(bgactionForever);

	auto bgmove2 = MoveBy::create(13, Vec2(-2032, 0));
	auto bgplace2 = Place::create(Vec2(2032, 400));
	auto bgaction2 = Sequence::create(bgmove2, bgplace2, nullptr);
	auto bgactionForever2 = RepeatForever::create(bgaction2);
	pbackground2->runAction(bgactionForever2);
}

void Prologue2::update(float f)
{
	if (_enter == true && order == prologueEnum::OPENING1)
	{
		scheduleOnce(schedule_selector(Prologue2::Opening1),0.01f);
	}

	if (_enter == true && order == prologueEnum::OPENING2)
	{
		scheduleOnce(schedule_selector(Prologue2::Opening2), 0.01f);
	}

	if (_enter == true && order == prologueEnum::MENUCHOICE && menuOrder == 0)
	{
		scheduleOnce(schedule_selector(Prologue2::Start0), 0.01f);
	}

	if (_enter == true && order == prologueEnum::MENUCHOICE && menuOrder == 1)
	{
		scheduleOnce(schedule_selector(Prologue2::ChapterChoice), 0.01f);
	}

	if (_enter == true && order == prologueEnum::MENUCHOICE && menuOrder == 2)
	{
		scheduleOnce(schedule_selector(Prologue2::GameExit), 0.01f);
	}

	if (_enter == true && order == prologueEnum::START1)
	{
		scheduleOnce(schedule_selector(Prologue2::Start1), 0.01f);
	}

	if (_enter == true && order == prologueEnum::START2)
	{
		scheduleOnce(schedule_selector(Prologue2::Start2), 0.01f);
	}

	if (_enter == true && order == prologueEnum::START3)
	{
		scheduleOnce(schedule_selector(Prologue2::Start3), 0.01f);
	}

	if (_enter == true && order == prologueEnum::START4)
	{
		scheduleOnce(schedule_selector(Prologue2::Start4), 0.01f);
	}

	if (_enter == true && order == prologueEnum::START5)
	{
		scheduleOnce(schedule_selector(Prologue2::Start5), 0.01f);
	}

	if (_enter == true && order == prologueEnum::GAMESTART)
	{
		scheduleOnce(schedule_selector(Prologue2::GameStart), 0.01f);
	}
}

void Prologue2::Opening1(float f)
{
	order = prologueEnum::OPENING2;

	plabel->setString("반갑네 인간이여. 나를 괘념치 말게.\n그저 오랜 친구 베엘제붑일세");
	plabel2->setOpacity(255);

	beel_fly = Sprite::create("Texture2D/beel_fly.png");
	beel_fly->setPosition(1920, 400);
	beel_fly->setAnchorPoint(Point(0, 0));
	auto beelMove = MoveTo::create(0.25f, Vec2(50, 400));
	this->addChild(beel_fly);
	beel_fly->runAction(beelMove);

}

void Prologue2::Opening2(float f)
{
	order = prologueEnum::MENUCHOICE;
	button->setOpacity(0);
	plabel->setOpacity(0);

	SetMenu();

	auto menuButtonMove = MoveBy::create(0.25f, Vec2(0, 300));

	menuLayer->runAction(menuButtonMove);
}

void Prologue2::Start0(float f)
{
	order = prologueEnum::START1;
	button->setOpacity(255);
	plabel->setString("또 헬테이커의 이야기를 들려달라고? 재미있군...");
	plabel->setOpacity(255);
	menuLayer->removeAllChildrenWithCleanup(true);
}

void Prologue2::Start1(float f)
{
	order = prologueEnum::START2;
	plabel->setString("혹시 해설자가 필요하진 않은가?");
}

void Prologue2::Start2(float f)
{
	order = prologueEnum::START3;
	beel_fly->setOpacity(0);
	pbackground1->setOpacity(0);
	pbackground2->setOpacity(0);

	plabel->setString("허락해준다면 참 고맙겠어.");
}

void Prologue2::Start3(float f)
{
	order = prologueEnum::START4;
	plabel2->setOpacity(0);
	cutScene1 = Sprite::create("Sprite/cutscene_0002_Group-2.png");
	cutScene1->setPosition(960, 680);

	this->addChild(cutScene1);
	plabel->setString("어느날 당신은 악마들로 가득찬 하렘을\n꿈꾸고 일어났네");
}

void Prologue2::Start4(float f)
{
	order = prologueEnum::START5;
	cutScene1->setVisible(0);
	cutScene2 = Sprite::create("Sprite/cutscene_0003_Group-3-copy-2.png");
	cutScene2->setPosition(960, 680);
	this->addChild(cutScene2);
	plabel->setString("하지만 결코 이루기 쉽지 않은 꿈이지. \n어쩌면 네 목숨을 앗아갈지도 모르고.");
}

void Prologue2::Start5(float f)
{
	order = prologueEnum::GAMESTART;
	cutScene2->setVisible(0);
	cutScene3 = Sprite::create("Sprite/cutscene_0004_Layer-273-copy.png");
	cutScene3->setPosition(960, 680);
	this->addChild(cutScene3);
	plabel->setString("\"악마 하렘이 달렸다면, 그 어떤 대가도 싸지.\"\n그리하여 당신은 지옥으로 모험을 떠났네.");
}

void Prologue2::Start6(float f)
{
	order = prologueEnum::EXIT;
	button->setOpacity(255);
	plabel->setString("나도 수 없이 시도 해봤지만 아직 제대로 성공한 적이 없지.");
	plabel->setOpacity(255);
	menuLayer->removeAllChildrenWithCleanup(true);
}

void Prologue2::GameExit(float f)
{
	//게임종료
}

void Prologue2::ChapterChoice(float f)
{
	order = prologueEnum::GAMESTART;
	menuLayer->removeAllChildrenWithCleanup(true);
	SetChapterSelectMenu();

	auto layerAction = MoveTo::create(0.25f, Vec2(0, 300));
	chapterLayer->runAction(layerAction);
}

void Prologue2::GameStart(float f)
{
	if (chapterOrder == 0)
	{

		auto pScene = MainScene00::create();
		_director->getTextureCache()->removeUnusedTextures();
		Director::getInstance()->replaceScene(pScene);
	}
	/*else if (chapterOrder == 1)
	{
		auto pScene = MainScene01::create();
		_director->getTextureCache()->removeUnusedTextures();
		this->removeAllChildrenWithCleanup(true);
		Director::getInstance()->replaceScene(pScene);
	}
	else if (chapterOrder == 2)
	{
		auto pScene = MainScene02::create();
		_director->getTextureCache()->removeUnusedTextures();
		this->removeAllChildrenWithCleanup(true);
		Director::getInstance()->replaceScene(pScene);
	}*/
}

void Prologue2::SetMenu()
{
	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);

	menuButton = Sprite::create("Sprite/button0003.png");
	menuButton->setColor(Color3B(255, 102, 102));
	menuButton->setPosition(960, -50);

	menuButton2 = Sprite::create("Sprite/button0003.png");
	menuButton2->setColor(Color3B(255, 204, 204));
	menuButton2->setPosition(960, -140);

	menuButton3 = Sprite::create("Sprite/button0003.png");
	menuButton3->setColor(Color3B(255, 204, 204));
	menuButton3->setPosition(960, -230);

	auto menuLabel1 = Label::createWithTTF(ttfconfig, "새 게임");
	menuLabel1->setTextColor(Color4B::WHITE);
	menuLabel1->setPosition(menuButton->getPosition());

	auto menuLabel2 = Label::createWithTTF(ttfconfig, "챕터 선택");
	menuLabel2->setTextColor(Color4B::WHITE);
	menuLabel2->setPosition(menuButton2->getPosition());

	auto menuLabel3 = Label::createWithTTF(ttfconfig, "나가기");
	menuLabel3->setTextColor(Color4B::WHITE);
	menuLabel3->setPosition(menuButton3->getPosition());

	menuLayer->addChild(menuLabel1);
	menuLayer->addChild(menuLabel2);
	menuLayer->addChild(menuLabel3);
	menuLayer->addChild(menuButton);
	menuLayer->addChild(menuButton2);
	menuLayer->addChild(menuButton3);
}

void Prologue2::SetChapterSelectMenu()
{
	TTFConfig ttfconfig("Font/The_Jamsil_3_Regular.ttf", 30);

	auto chapterSprite0 = Sprite::create("Texture2D/W_chapterSelect.png");
	chapterSprite0->setPosition(Vec2(960, -20));

	auto chapterSprite1 = Sprite::create("Texture2D/W_chapterSelect.png");
	chapterSprite1->setFlippedY(true);
	chapterSprite1->setPosition(Vec2(960, -130));

	chapterButton0 = Sprite::create("Texture2D/W_chapter1.png");
	chapterButton0->setColor(Color3B::WHITE);
	chapterButton0->setPosition(Vec2(840, -75));
	chapterButton0->setOpacity(255);

	chapterButton1 = Sprite::create("Texture2D/W_chapter1.png");
	chapterButton1->setColor(Color3B::WHITE);
	chapterButton1->setPosition(Vec2(960, -75));
	chapterButton1->setOpacity(100);

	chapterButton2 = Sprite::create("Texture2D/W_chapter1.png");
	chapterButton2->setColor(Color3B::WHITE);
	chapterButton2->setPosition(Vec2(1080, -75));
	chapterButton2->setOpacity(100);

	Vec2 pos = Vec2(chapterButton0->getBoundingBox().size.width * 0.5, chapterButton0->getBoundingBox().size.height * 0.5);

	chapterLabel0 = Label::createWithTTF(ttfconfig, "Ⅰ");
	chapterLabel0->setTextColor(Color4B::WHITE);
	chapterLabel0->setPosition(pos);
	chapterLabel0->setOpacity(255);
	chapterButton0->addChild(chapterLabel0);

	chapterLabel1 = Label::createWithTTF(ttfconfig, "Ⅱ");
	chapterLabel1->setTextColor(Color4B::WHITE);
	chapterLabel1->setPosition(pos);
	chapterLabel1->setOpacity(100);
	chapterButton1->addChild(chapterLabel1);

	chapterLabel2 = Label::createWithTTF(ttfconfig, "Ⅲ");
	chapterLabel2->setTextColor(Color4B::WHITE);
	chapterLabel2->setPosition(pos);
	chapterLabel2->setOpacity(100);
	chapterButton2->addChild(chapterLabel2);

	chapterPlabel0 = Label::createWithTTF(ttfconfig, "ChapterⅠ - 피곤한 악마");
	chapterPlabel0->setTextColor(Color4B::WHITE);
	chapterPlabel0->setPosition(Vec2(960, -180));

	chapterLayer->addChild(chapterSprite0);
	chapterLayer->addChild(chapterSprite1);
	chapterLayer->addChild(chapterButton0);
	chapterLayer->addChild(chapterButton1);
	chapterLayer->addChild(chapterButton2);
	chapterLayer->addChild(chapterPlabel0);
}




void Prologue2::onEnter()
{
	Scene::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(Prologue2::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(Prologue2::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
	
}

void Prologue2::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Scene::onExit();
}

void Prologue2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
		_enter = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (order == prologueEnum::MENUCHOICE)
		{
			switch (menuOrder)
			{
			case 0:
				//3, 2, 1 
				SetMenuColor(Color3B(255, 102, 102), Color3B(255, 204, 204), Color3B(255, 204, 204),2);
				break;
			case 1:
				SetMenuColor(Color3B(255, 204, 204), Color3B(255, 204, 204), Color3B(255, 102, 102), 0);
				break;
			case 2:
				SetMenuColor(Color3B(255, 204, 204), Color3B(255, 102, 102), Color3B(255, 204, 204), 1);
				break;
			default:
				break;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (order == prologueEnum::MENUCHOICE)
		{
			switch (menuOrder)
			{
			case 0:
				SetMenuColor(Color3B(255, 204, 204), Color3B(255, 102, 102), Color3B(255, 204, 204), 1);
				break;
			case 1:
				SetMenuColor(Color3B(255, 102, 102), Color3B(255, 204, 204), Color3B(255, 204, 204), 2);
				break;
			case 2:
				SetMenuColor(Color3B(255, 204, 204), Color3B(255, 204, 204), Color3B(255, 102, 102), 0);
				break;
			default:
				break;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (order == prologueEnum::GAMESTART)
		{
			switch (chapterOrder)
			{
			case 0:
				SetChapterMenuColor(chapterButton2, chapterButton1, chapterButton0, chapterLabel2, chapterLabel1, chapterLabel0, 2, "ChapterⅢ - 세 쌍둥이 악마");
				break;
			case 1:
				SetChapterMenuColor(chapterButton0, chapterButton1, chapterButton2, chapterLabel0, chapterLabel1, chapterLabel2, 0, "ChapterⅠ - 피곤한 악마");
				break;
			case 2:
				SetChapterMenuColor(chapterButton1, chapterButton0, chapterButton2, chapterLabel1, chapterLabel0, chapterLabel2, 1, "ChapterⅡ - 음란한 악마");
				break;
			default:
				break;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (order == prologueEnum::GAMESTART)
		{
			switch (chapterOrder)
			{
			case 0:
				SetChapterMenuColor(chapterButton1, chapterButton0, chapterButton2, chapterLabel1, chapterLabel0, chapterLabel2, 1, "ChapterⅡ - 음란한 악마");
				break;
			case 1:
				SetChapterMenuColor(chapterButton2, chapterButton1, chapterButton0, chapterLabel2, chapterLabel1, chapterLabel0, 2, "ChapterⅢ - 세 쌍둥이 악마");
				break;
			case 2:
				SetChapterMenuColor(chapterButton0, chapterButton1, chapterButton2, chapterLabel0, chapterLabel1, chapterLabel2, 0, "ChapterⅠ - 피곤한 악마");
			default:
				break;
			}
		}
		break;
	}
}

void Prologue2::SetMenuColor(Color3B color1, Color3B color2, Color3B color3, int index)
{
	menuButton3->setColor(color1);
	menuButton2->setColor(color2);
	menuButton->setColor(color3);
	menuOrder = index;
}

void Prologue2::SetChapterMenuColor(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2, cocos2d::Sprite* sprite3, cocos2d::Label* label1, cocos2d::Label* label2, cocos2d::Label* label3, int index, std::string str)
{
	sprite1->setOpacity(255);
	sprite2->setOpacity(100);
	sprite3->setOpacity(100);
	label1->setOpacity(255);
	label2->setOpacity(100);
	label3->setOpacity(100);
	chapterOrder = index;
	chapterPlabel0->setString(str);
}

void Prologue2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
		_enter = false;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_up = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_down = false;
		break;
	}
}
