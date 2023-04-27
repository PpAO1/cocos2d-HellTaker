#include "GameManager.h"
#include "MainCutScene00.h"

USING_NS_CC;
using namespace std;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8");
#endif

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
	stage1StartPos = Vec2(510, 140);

}

GameManager::GameManager(int index)
{
	this->index = index;
	GameManager();
}

GameManager::~GameManager()
{
}

GameManager& GameManager::getInstance(int index)
{
	if (_instance == NULL)
		_instance = new GameManager(index);

	return *_instance;
}

void GameManager::ReleaseInstance()
{
	delete(_instance);
	_instance = NULL;
}

bool GameManager::init()
{
	ui = &UI::getInstance();

	ui->setPosition(Vec2(0, 0));
	ui->setAnchorPoint(Vec2(0, 0));
	ui->setZOrder(500);
	this->addChild(ui);

	isRestart = false;
	pressF = false;
	isClear = false;
	isGonextMap = false;

	this->FileDataRead();
	return true;
}

void GameManager::FileDataRead()
{
	for (int i = 0;i < mapStage.size();++i)
	{
		mapStage[i].clear();
	}
	mapStage.clear();

	switch (index)
	{
	case 0:
		TextFileRead("stage1.txt", STAGE1_HEIGHT, STAGE1_WIDTH);
		SetPlayerPos(STAGE1_WIDTH, STAGE1_HEIGHT, STAGE1_2_START_POS_X, STAGE1_2_START_POS_Y);
		SetObjectsPos(STAGE1_WIDTH, STAGE1_HEIGHT);
		MoveChance = 23;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
		ui->stageCountLabel->setString("Ⅰ");
		break;
	case 1:
		TextFileRead("stage2.txt", STAGE2_HEIGHT, STAGE2_WIDTH);
		SetPlayerPos(STAGE2_WIDTH, STAGE2_HEIGHT, STAGE1_2_START_POS_X, STAGE1_2_START_POS_Y);
		SetObjectsPos(STAGE2_WIDTH, STAGE2_HEIGHT);
		MoveChance = 24;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
		ui->stageCountLabel->setString("Ⅱ");
		break;
	case 2:
		TextFileRead("stage3.txt", STAGE3_HEIGHT, STAGE3_WIDTH);
		SetPlayerPos(STAGE3_WIDTH, STAGE3_HEIGHT, STAGE3_START_POS_X, STAGE3_START_POS_Y);
		SetObjectsPos(STAGE3_WIDTH, STAGE3_HEIGHT);
		MoveChance = 32;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
		ui->stageCountLabel->setString("Ⅲ");
		break;
	case 3:
		TextFileRead("stage4.txt", STAGE4_HEIGHT, STAGE4_WIDTH);
		SetPlayerPos(STAGE4_WIDTH, STAGE4_HEIGHT, STAGE4_START_POS_X, STAGE4_START_POS_Y);
		SetObjectsPos(STAGE4_WIDTH, STAGE4_HEIGHT);
		MoveChance = 23;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
		ui->stageCountLabel->setString("Ⅳ");
		break;
	default:
		break;
	}
}

void GameManager::TextFileRead(std::string str, int width, int height)
{
	ifstream readFile;
	readFile.open(str);
	for (int i = 0; i < height;++i) {
		std::vector<int> v;
		mapStage.push_back(v);
	}

	if (readFile.is_open())
	{
		int i = 0, j = 0;
		char temp = ' ';
		/*
			std::vector<int> v;
			mapStage.push_back(v);
			mapStage.push_back(v);
			mapStage.push_back(v);
			mapStage.push_back(v);
			mapStage.push_back(v);
			mapStage.push_back(v);
			mapStage.push_back(v);*/

		while (!readFile.eof())
		{
			char nObjNum;

			readFile.get(nObjNum);

			if (nObjNum == ' ' || nObjNum == '\n') {
				temp = ' ';
				continue;
			}
			else if (temp != ' ') {
				char array[2];
				array[0] = temp;
				array[1] = nObjNum;

				std::string str = std::string(array);

				auto value = stoi(str);

				mapStage[i][j - 1] = value;
				temp = ' ';
				continue;
			}

			temp = nObjNum;
			mapStage[i].push_back(nObjNum - '0');

			//mapStage[i][j] = nObjNum - '0';
			j++;

			if (j == width)
			{
				j = 0;
				i++;
				if (i == height)
				{
					break;
				}
			}
		}
	}
}

void GameManager::SetPlayerPos(int stageHeight, int stageWidth, int startx, int starty)
{
	for (int i = 0; i < stageHeight; i++)
	{
		for (int j = 0; j < stageWidth; j++)
		{
			if (mapStage[i][j] == MapObject::PLAYER)
			{
				pPlayer = &Player::getInstance();
				pPlayer->setPosition((startx + (j * CELL)), (starty + (i * CELL)));
				pPlayer->_mapPos = Coordinate(j, i);
				origin = Coordinate(j, i);
				pPlayer->setAnchorPoint(Vec2(0, 0));
				pPlayer->setZOrder(5);
				this->addChild(pPlayer);
			}
		}
	}
}

void GameManager::SetObjectsPos(int stageHeight, int stageWidth)
{
	int startX, startY = 0;

	switch (index)
	{
	case 0:
		startX = STAGE1_2_START_POS_X;
		startY = STAGE1_2_START_POS_Y;
		break;
	case 1:
		startX = STAGE1_2_START_POS_X;
		startY = STAGE1_2_START_POS_Y;
		break;
	case 2:
		startX = STAGE3_START_POS_X;
		startY = STAGE3_START_POS_Y;
		break;
	case 3:
		startX = STAGE4_START_POS_X;
		startY = STAGE4_START_POS_Y;
		break;
	default:
		break;
	}

	for (int i = 0; i < stageHeight; i++)
	{
		for (int j = 0; j < stageWidth; j++)
		{
			auto Obj = Sprite::create();
			string fileName = "null";

			if (mapStage[i][j] == MapObject::SKELETON)
			{
				auto pSkeleton = &Skeleton::getInstance();
				SetObjects(pSkeleton, j, i,startX,startY);
				pSkeleton->_mapPos = Coordinate(j, i);
				skeletonVec.push_back(pSkeleton);
				//pSkeleton->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				//pSkeleton->setAnchorPoint(Vec2(0, 0));
				//pSkeleton->setZOrder(3);
				//this->addChild(pSkeleton);
			}
			else if (mapStage[i][j] == MapObject::ROCK)
			{
				auto pRock = &Rock::getInctance();
				SetObjects(pRock, j, i, startX, startY);
				pRock->setZOrder(4);
				pRock->_mapPos = Coordinate(j, i);
				rockVec.push_back(pRock);
			}
			else if (mapStage[i][j] == MapObject::SPIKE)
			{
				auto pSpike = new Spike(MapObject::SPIKE);
				SetObjects(pSpike, j, i, startX, startY);
			}
			else if (mapStage[i][j] == MapObject::SPIKEONROCK)
			{
				auto pSpike = new Spike(MapObject::SPIKE);
				SetObjects(pSpike, j, i, startX, startY);

				auto pRock = &Rock::getInctance();
				SetObjects(pRock, j, i, startX, startY);
				pRock->setZOrder(4);
				pRock->_mapPos = Coordinate(j, i);
				rockVec.push_back(pRock);
			}
			else if (mapStage[i][j] == MapObject::KEY)
			{
				auto pKey = new Key;
				SetObjects(pKey, j, i, startX, startY);
			}
			else if (mapStage[i][j] == MapObject::LOCK)
			{
				auto pLock = new Lock;
				SetObjects(pLock, j, i, startX, startY);
			}
			else if (mapStage[i][j] == MapObject::NPC)
			{
				pNpc = new Npc(index);
				SetObjects(pNpc, j, i, startX, startY);
			}
		}
	}
}

void GameManager::Logic(int offsetX, int offsetY, int oriX, int oriY, Vec2 pos)
{
	if (MoveChance <= 0)
	{
		this->PlayerDie();
	}

	if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::WALL)
	{
		// 캐릭터의 경로가 벽인경우 아무런 로직이 실행되지 않음
		return;
	}

	if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::LOCK && pKey->isGetKey == false)
	{
		// 열쇠를 가지지 않은채로 자물쇠에 접근할때 아무런 로직이 실행되지 않음
		return;
	}

	if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::EMPTY)
	{
		// 캐릭터의 경로가 빈공간일경우, 캐릭터가 이동함.
		if (mapStage[oriY][oriX] == MapObject::SPIKEONPLAYER)
		{
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			mapStage[oriY][oriX] = MapObject::SPIKE;
			mapStage[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
		else
		{
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			mapStage[oriY][oriX] = MapObject::EMPTY;
			mapStage[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::SKELETON)
	{
		// 캐릭터의 경로에 스켈레톤이 있을경우, 그 스켈레톤을 찾아서 밀침.
		Skeleton* pskeleton;
		for (int i = 0; i < skeletonVec.size(); i++)
		{
			auto skeleton = skeletonVec[i];

			if (skeleton->_mapPos.x == oriX + offsetX && skeleton->_mapPos.y == oriY + offsetY)
			{
				pskeleton = skeleton;
				break;
			}
		}
		auto x = pskeleton->_mapPos.x;
		auto y = pskeleton->_mapPos.y;

		if (mapStage[y + offsetY][x + offsetX] == MapObject::EMPTY)
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDamagedAnim();
			pskeleton->SkeletonMove(pos);
			pskeleton->_mapPos.x += offsetX;
			pskeleton->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::EMPTY;
			mapStage[y + offsetY][x + offsetX] = MapObject::SKELETON;
		}
		else if (mapStage[y + offsetY][x + offsetX] == MapObject::SPIKE)
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDamagedAnim();
			pskeleton->SkeletonMove(pos);
			pskeleton->SkeletonDieAnim(pos);
			pskeleton->_mapPos.x += offsetX;
			pskeleton->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::EMPTY;
		}
		else
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDieAnim(Vec2(0, 0));
			mapStage[y][x] = MapObject::EMPTY;
		}
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::ROCK)
	{
		// 캐릭터의 경로에 바위가 있을경우 바위를 밀침, 가시 외 뒤에 다른 오브젝트가 있다면 밀쳐지지 않음
		Rock* prock;
		for (int i = 0; i < rockVec.size();++i)
		{
			auto rock = rockVec[i];

			if (rock->_mapPos.x == oriX + offsetX && rock->_mapPos.y == oriY + offsetY)
			{
				prock = rock;
				break;
			}
		}
		auto x = prock->_mapPos.x;
		auto y = prock->_mapPos.y;

		if (mapStage[y + offsetY][x + offsetX] == MapObject::EMPTY || mapStage[y + offsetY][x + offsetX] == MapObject::GOAL)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::EMPTY;
			mapStage[y + offsetY][x + offsetX] = MapObject::ROCK;
		}
		else if (mapStage[y + offsetY][x + offsetX] == MapObject::SPIKE)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::EMPTY;
			mapStage[y + offsetY][x + offsetX] = MapObject::SPIKEONROCK;
		}
		else
		{
			pPlayer->PlayerHitAnim();
		}
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::SPIKE)
	{
		// 캐릭터의 경로에 움직이지 않는가시가 있을경우 피해를 입음.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		mapStage[oriY][oriX] = MapObject::EMPTY;
		mapStage[oriY + offsetY][oriX + offsetX] = MapObject::SPIKEONPLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::SPIKEONROCK)
	{
		// 캐릭터의 경로에 바위가 있을경우 바위를 밀침, 가시 외 뒤에 다른 오브젝트가 있다면 밀쳐지지 않음
		Rock* prock;
		for (int i = 0; i < rockVec.size(); ++i)
		{
			auto rock = rockVec[i];

			if (rock->_mapPos.x == oriX + offsetX && rock->_mapPos.y == oriY + offsetY)
			{
				prock = rock;
				break;
			}
		}
		auto x = prock->_mapPos.x;
		auto y = prock->_mapPos.y;

		if (mapStage[y + offsetY][x + offsetX] == MapObject::EMPTY || mapStage[y + offsetY][x + offsetX] == MapObject::GOAL)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::SPIKE;
			mapStage[y + offsetY][x + offsetX] = MapObject::ROCK;
		}
		else if (mapStage[y + offsetY][x + offsetX] == MapObject::SPIKE)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			mapStage[y][x] = MapObject::SPIKE;
			mapStage[y + offsetY][x + offsetX] = MapObject::SPIKEONROCK;
		}
		else
		{
			pPlayer->PlayerHitAnim();
		}
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::KEY)
	{
		// 캐릭터의 경로에 열쇠가 있을경우 이동해서 열쇠를 얻음.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		pKey->KeyEating();
		mapStage[oriY][oriX] = MapObject::EMPTY;
		mapStage[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::LOCK && pKey->isGetKey == true)
	{
		// 캐릭터의 경로에 자물쇠가 있을경우 열쇠를 먹은상태일때 이동되며 자물쇠가 풀림.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		pLock->UnLock();
		mapStage[oriY][oriX] = MapObject::EMPTY;
		mapStage[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (mapStage[oriY + offsetY][oriX + offsetX] == MapObject::GOAL)
	{
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		isClear = true;
		scheduleOnce(schedule_selector(GameManager::StageClear), 0.4f);

		
	}

	if (mapStage[pPlayer->_mapPos.y][pPlayer->_mapPos.x] == MapObject::SPIKEONPLAYER)
	{
		// 캐릭터의 행동 후에도 플레이어가 가시위에 있다면 데미지를 입음.
		scheduleOnce(schedule_selector(GameManager::Damaged), 0.1f);
		MoveChance--;
	}

	if (MoveChance <= 1)
	{
		--MoveChance;
		ui->moveChanceLabel->setString("X");
	}
	else
	{
		--MoveChance;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
	}
}

void GameManager::Damaged(float f)
{
	pPlayer->PlayerDamagedAnim();
}

void GameManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (isClear == false)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_R:
			pressF = true;
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->Logic(0, 1, pPlayer->_mapPos.x, pPlayer->_mapPos.y, Vec2(0, 100));
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->Logic(0, -1, pPlayer->_mapPos.x, pPlayer->_mapPos.y, Vec2(0, -100));
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->Logic(-1, 0, pPlayer->_mapPos.x, pPlayer->_mapPos.y, Vec2(-100, 0));
			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->Logic(1, 0, pPlayer->_mapPos.x, pPlayer->_mapPos.y, Vec2(100, 0));
			break;
		}
	}
}

void GameManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_R:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	}
}

void GameManager::onEnter()
{
	Layer::onEnter();

	_listener = EventListenerKeyboard::create();

	_listener->onKeyPressed = CC_CALLBACK_2(GameManager::onKeyPressed, this);
	_listener->onKeyReleased = CC_CALLBACK_2(GameManager::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void GameManager::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Layer::onExit();
}

void GameManager::StageClear(float f)
{
	auto pScene = MainCutScene00::createScene();
	Director::getInstance()->pushScene(pScene);
	pPlayer->GOAL();
	pNpc->NpcGoal();

	scheduleOnce(schedule_selector(GameManager::NextStage), 3.5f);
}

void GameManager::PlayerDie()
{

	auto wlayer = LayerColor::create(Color4B(2, 2, 27, 255));
	wlayer->setPosition(Vec2(0, 0));
	wlayer->setAnchorPoint(Vec2(0, 0));
	wlayer->setZOrder(6);
	this->addChild(wlayer);

	pPlayer->setOpacity(0);

	int x = (pPlayer->_mapPos.x - origin.x) * 100;
	int y = (pPlayer->_mapPos.y - origin.y) * 100;
	auto tempPos = pPlayer->getPosition();

	tempPos.x += x;
	tempPos.y += y + 200;


	auto damagedEffect = Sprite::create("Sprite/death_P1.png");
	damagedEffect->setAnchorPoint(Vec2(0.5f, 0.5f));
	damagedEffect->setPosition(tempPos);
	damagedEffect->setZOrder(7);
	this->addChild(damagedEffect);

	auto EffectAnim = Animation::create();

	EffectAnim->setDelayPerUnit(0.1f);

	char str3[100] = { 0, };

	for (int i = 1; i < 19; i++)
	{
		sprintf(str3, "Sprite/death_P%d.png", i);
		EffectAnim->addSpriteFrameWithFile(str3);
	}

	auto EffectAnimate = Animate::create(EffectAnim);
	RemoveSelf* removeanim = RemoveSelf::create(EffectAnimate);
	damagedEffect->runAction(Sequence::create(EffectAnimate, removeanim, nullptr));

	isRestart = true;
}

void GameManager::NextStage(float f)
{
	isGonextMap = true;
}

