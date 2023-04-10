#include "GameManager.h"

USING_NS_CC;
using namespace std;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
	stage1StartPos = Vec2(510, 140);
}

GameManager::~GameManager()
{
}

GameManager& GameManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameManager();

	return *_instance;
}

bool GameManager::init()
{
	UI* ui = &UI::getInstance();

	ui->setPosition(Vec2(0, 0));
	ui->setAnchorPoint(Vec2(0, 0));
	ui->setZOrder(500);
	this->addChild(ui);

	isRestart = false;

	this->FileDataRead();
	return true;
}

void GameManager::FileDataRead()
{
	TextFileRead("stage1.txt", 9);
	SetPlayerPos(STAGE1_WIDTH, STAGE1_HEIGHT);
	SetObjectsPos(STAGE1_WIDTH, STAGE1_HEIGHT);
	/*switch (stage)
	{
	case Stage::Stage1:
		TextFileRead("stage1.txt", 9);
		SetPlayerPos(STAGE1_WIDTH, STAGE1_HEIGHT);
		SetObjectsPos(STAGE1_WIDTH, STAGE1_HEIGHT);
		break;
	case Stage2:
		break;
	case Stage3:
		break;
	default:
		break;
	}*/
}

void GameManager::TextFileRead(std::string str, int width)
{
	ifstream readFile;
	readFile.open(str);
	if (readFile.is_open())
	{
		int i = 0, j = 0;
		char temp = ' ';

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

				stage1Map[i][j - 1] = value;
				temp = ' ';
				continue;
			}

			temp = nObjNum;
			stage1Map[i][j] = nObjNum - '0';
			j++;

			if (j == width)
			{
				j = 0;
				i++;
			}
		}
	}
}

void GameManager::SetPlayerPos(int stageHeight, int stageWidth)
{
	for (int i = 0; i < stageHeight; i++)
	{
		for (int j = 0; j < stageWidth; j++)
		{
			if (stage1Map[i][j] == MapObject::PLAYER)
			{
				pPlayer = &Player::getInstance();
				pPlayer->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pPlayer->_mapPos = Coordinate(j, i);
				pPlayer->setAnchorPoint(Vec2(0, 0));
				pPlayer->setZOrder(2);
				this->addChild(pPlayer);
			}
		}
	}
}

void GameManager::SetObjectsPos(int stageHeight, int stageWidth)
{
	for (int i = 0; i < stageHeight; i++)
	{
		for (int j = 0; j < stageWidth; j++)
		{
			auto Obj = Sprite::create();
			string fileName = "null";

			if (stage1Map[i][j] == MapObject::SKELETON)
			{
				auto pSkeleton = &Skeleton::getInstance();
				SetObjects(pSkeleton, j, i);
				pSkeleton->_mapPos = Coordinate(j, i);
				skeletonVec.push_back(pSkeleton);
				//pSkeleton->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				//pSkeleton->setAnchorPoint(Vec2(0, 0));
				//pSkeleton->setZOrder(3);
				//this->addChild(pSkeleton);
			}
			else if (stage1Map[i][j] == MapObject::ROCK)
			{
				auto pRock = &Rock::getInctance();
				SetObjects(pRock, j, i);
				pRock->_mapPos = Coordinate(j, i);
				rockVec.push_back(pRock);
				/*pRock->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pRock->setAnchorPoint(Vec2(0, 0));
				pRock->setZOrder(3);
				this->addChild(pRock);*/
			}
			//d
			else if (stage1Map[i][j] == MapObject::SPIKE)
			{
				auto pSpike = &Spike::getInstance();
				SetObjects(pSpike, j, i);
				/*pSpike->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pSpike->setAnchorPoint(Vec2(0, 0));
				pSpike->setZOrder(3);
				this->addChild(pSpike);*/
			}
			else if (stage1Map[i][j] == MapObject::KEY)
			{
				auto pKey = &Key::getInstance();
				SetObjects(pKey, j, i);
				/*pKey->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pKey->setAnchorPoint(Vec2(0, 0));
				pKey->setZOrder(3);
				this->addChild(pKey);*/
			}
			else if (stage1Map[i][j] == MapObject::LOCK)
			{
				auto pLock = &Lock::getInstance();
				SetObjects(pLock, j, i);
				/*pLock->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pLock->setAnchorPoint(Vec2(0, 0));
				pLock->setZOrder(3);
				this->addChild(pLock);*/
			}
			else if (stage1Map[i][j] == MapObject::NPC)
			{
				auto pNpc = &Npc::getInstance();
				SetObjects(pNpc, j, i);
			}
		}
	}
}

void GameManager::Logic(int offsetX, int offsetY, int oriX, int oriY, Vec2 pos)
{
	if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::WALL)
	{
		// 캐릭터의 경로가 벽인경우 아무런 로직이 실행되지 않음
		return;
	}

	if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::EMPTY)
	{
		// 캐릭터의 경로가 빈공간일경우, 캐릭터가 이동함.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		stage1Map[oriY][oriX] = MapObject::EMPTY;
		stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::SKELETON)
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

		if (stage1Map[y + offsetY][x + offsetX] == MapObject::EMPTY)
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDamagedAnim();
			pskeleton->SkeletonMove(pos);
			pskeleton->_mapPos.x += offsetX;
			pskeleton->_mapPos.y += offsetY;
			stage1Map[y][x] = MapObject::EMPTY;
			stage1Map[y + offsetY][x + offsetX] = MapObject::SKELETON;
		}
		else
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDieAnim();
			stage1Map[y][x] = MapObject::EMPTY;
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::ROCK)
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

		if (stage1Map[y + offsetY][x + offsetX] == MapObject::EMPTY || stage1Map[y + offsetY][x + offsetX] == MapObject::GOAL)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			stage1Map[y][x] = MapObject::EMPTY;
			stage1Map[y + offsetY][x + offsetX] = MapObject::ROCK;

		}
		else if (stage1Map[y + offsetY][x + offsetX] == MapObject::SPIKE)
		{
			pPlayer->PlayerHitAnim();
			prock->RockMove(pos);
			prock->RockMoveAnim();
			prock->_mapPos.x += offsetX;
			prock->_mapPos.y += offsetY;
			stage1Map[y][x] = MapObject::EMPTY;
			stage1Map[y + offsetY][x + offsetX] = MapObject::SPIKEONROCK;
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::SPIKE)
	{
		// 캐릭터의 경로에 가시가 있을경우 이동은 되지만 피해를 입음.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		stage1Map[oriY][oriX] = MapObject::EMPTY;
		stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::SPIKEONPLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::KEY)
	{
		// 캐릭터의 경로에 열쇠가 있을경우 이동해서 열쇠를 얻음.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		pKey->KeyEating();
		stage1Map[oriY][oriX] = MapObject::EMPTY;
		stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::LOCK)
	{
		// 캐릭터의 경로에 자물쇠가 있을경우 열쇠를 먹은상태일때 이동되며 자물쇠가 풀림.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		pLock->UnLock();
		stage1Map[oriY][oriX] = MapObject::EMPTY;
		stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::GOAL)
	{
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		this->StageClear();
	}
}
//papapapapapapa

void GameManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_R:
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

void GameManager::StageClear()
{
}

void GameManager::PlayerDie()
{
	auto wlayer = LayerColor::create(Color4B::BLACK);
	wlayer->setPosition(Vec2(0, 0));
	wlayer->setAnchorPoint(Vec2(0, 0));
	wlayer->setZOrder(2);
	this->addChild(wlayer);

	pPlayer->setOpacity(0);

	auto damagedEffect = Sprite::create("Sprite/death_P1.png");
	damagedEffect->setPosition(pPlayer->getPosition());
	damagedEffect->setZOrder(1);
	this->addChild(damagedEffect);

	auto EffectAnim = Animation::create();

	EffectAnim->setDelayPerUnit(0.7f);

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

