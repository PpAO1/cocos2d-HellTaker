#include "GameManager.h"

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

	this->FileDataRead();
	this->scheduleUpdate();
	return true;
}

void GameManager::FileDataRead()
{
	switch (index)
	{
	case 0:
		TextFileRead("stage1.txt", 9);
		SetPlayerPos(STAGE1_WIDTH, STAGE1_HEIGHT);
		SetObjectsPos(STAGE1_WIDTH, STAGE1_HEIGHT);
		MoveChance = 23;
		ui->moveChanceLabel->setString(StringUtils::format("%d", MoveChance));
		ui->stageCountLabel->setString("��");
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
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
			}
			else if (stage1Map[i][j] == MapObject::SPIKE)
			{
				auto pSpike = new Spike(MapObject::SPIKE);
				SetObjects(pSpike, j, i);
				pSpike->_mapPos = Coordinate(j, i);
				spikeVec.push_back(pSpike);
			}
			else if (stage1Map[i][j] == MapObject::MOVESPIKEDOWN)
			{
				auto pSpike = new Spike(MapObject::MOVESPIKEDOWN);
				SetObjects(pSpike, j, i);
				pSpike->_mapPos = Coordinate(j, i);
				spikeVec.push_back(pSpike);
			}
			else if (stage1Map[i][j] == MapObject::MOVESPIKEUP)
			{
				auto pSpike = new Spike(MapObject::MOVESPIKEUP);
				SetObjects(pSpike, j, i);
				pSpike->_mapPos = Coordinate(j, i);
				spikeVec.push_back(pSpike);
			}
			else if (stage1Map[i][j] == MapObject::SPIKEONROCK)
			{
				auto pSpike = new Spike(MapObject::MOVESPIKEUP);
				SetObjects(pSpike, j, i);
				pSpike->_mapPos = Coordinate(j, i);
				spikeVec.push_back(pSpike);
			}
			else if (stage1Map[i][j] == MapObject::KEY)
			{
				auto pKey = &Key::getInstance();
				SetObjects(pKey, j, i);
			}
			else if (stage1Map[i][j] == MapObject::LOCK)
			{
				auto pLock = &Lock::getInstance();
				SetObjects(pLock, j, i);
			}
			else if (stage1Map[i][j] == MapObject::NPC)
			{
				auto pNpc = new Npc(index);
				SetObjects(pNpc, j, i);
			}
		}
	}
}

void GameManager::Logic(int offsetX, int offsetY, int oriX, int oriY, Vec2 pos)
{
	if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::WALL)
	{
		// ĳ������ ��ΰ� ���ΰ�� �ƹ��� ������ ������� ����
		return;
	}

	if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::LOCK && pKey->isGetKey == false)
	{
		// ���踦 ������ ����ä�� �ڹ��迡 �����Ҷ� �ƹ��� ������ ������� ����
		return;
	}

	if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::EMPTY)
	{
		// ĳ������ ��ΰ� ������ϰ��, ĳ���Ͱ� �̵���.
		if (stage1Map[oriY][oriX] == MapObject::SPIKEONPLAYER)
		{
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			stage1Map[oriY][oriX] = MapObject::SPIKE;
			stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
		else
		{
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			stage1Map[oriY][oriX] = MapObject::EMPTY;
			stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::SKELETON)
	{
		// ĳ������ ��ο� ���̷����� �������, �� ���̷����� ã�Ƽ� ��ħ.
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

			if (stage1Map[oriY][oriX] == MapObject::SPIKEONPLAYER)
			{
				// ���̷����� ��ĥ�� �������� ������� ���ظ� �԰� ������ ��ȸ�� �ϳ� �� ����.
				pPlayer->PlayerDamagedAnim();
				MoveChance--;
			}
		}
		else
		{
			pPlayer->PlayerHitAnim();
			pskeleton->SkeletonDieAnim();
			stage1Map[y][x] = MapObject::EMPTY;

			if (stage1Map[oriY][oriX] == MapObject::SPIKEONPLAYER)
			{
				// ���̷����� ��ĥ�� �������� ������� ���ظ� �԰� ������ ��ȸ�� �ϳ� �� ����.
				pPlayer->PlayerDamagedAnim();
				MoveChance--;
			}
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::ROCK)
	{
		// ĳ������ ��ο� ������ ������� ������ ��ħ, ���� �� �ڿ� �ٸ� ������Ʈ�� �ִٸ� �������� ����
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

			if (stage1Map[oriY][oriX] == MapObject::SPIKEONPLAYER)
			{
				// ������ ��ĥ�� �������� ������� ���ظ� �԰� ������ ��ȸ�� �ϳ� �� ����.
				pPlayer->PlayerDamagedAnim();
				MoveChance--;
			}
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
		else if (stage1Map[y + offsetY][x + offsetX] == MapObject::ROCK)
		{
			pPlayer->PlayerHitAnim();
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::SPIKE)
	{
		Spike* pspike;
		for (int i = 0; i < spikeVec.size(); i++)
		{
			auto spike = spikeVec[i];

			if (spike->_mapPos.x == oriX + offsetX && spike->_mapPos.y == oriY + offsetY)
			{
				pspike = spike;
				break;
			}
		}
		
		if (pspike->isMove == false)
		{
			// ĳ������ ��ο� �������� �ʴ°��ð� ������� ���ظ� ����.
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			pPlayer->PlayerDamagedAnim();
			stage1Map[oriY][oriX] = MapObject::EMPTY;
			stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::SPIKEONPLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
		else if (pspike->isMove == true && pspike->isUp == true)
		{
			// ĳ������ ��ο� �����̴� ���ð� �ö��������� �̵��� �� ���ð� �������鼭 ���ظ� ���� ����.
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			stage1Map[oriY][oriX] = MapObject::EMPTY;
			stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::SPIKEONPLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
		else if (pspike->isMove == true && pspike->isUp == false)
		{
			// ĳ������ ��ο� �����̴� ���ð� ������������� �̵��� �� ���ð� �ö���鼭 ���ظ� ����.
			pPlayer->PlayerMoveAnim();
			pPlayer->PlayerMove(pos);
			pPlayer->PlayerDamagedAnim();
			stage1Map[oriY][oriX] = MapObject::EMPTY;
			stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::SPIKEONPLAYER;
			pPlayer->_mapPos.x += offsetX;
			pPlayer->_mapPos.y += offsetY;
		}
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::KEY)
	{
		// ĳ������ ��ο� ���谡 ������� �̵��ؼ� ���踦 ����.
		pPlayer->PlayerMoveAnim();
		pPlayer->PlayerMove(pos);
		pKey->KeyEating();
		stage1Map[oriY][oriX] = MapObject::EMPTY;
		stage1Map[oriY + offsetY][oriX + offsetX] = MapObject::PLAYER;
		pPlayer->_mapPos.x += offsetX;
		pPlayer->_mapPos.y += offsetY;
	}
	else if (stage1Map[oriY + offsetY][oriX + offsetX] == MapObject::LOCK && pKey->isGetKey == true)
	{
		// ĳ������ ��ο� �ڹ��谡 ������� ���踦 ���������϶� �̵��Ǹ� �ڹ��谡 Ǯ��.
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

void GameManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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

void GameManager::PlayerDie(float f)
{
	
	auto wlayer = LayerColor::create(Color4B(2,2,27,255));
	wlayer->setPosition(Vec2(0, 0));
	wlayer->setAnchorPoint(Vec2(0, 0));
	wlayer->setZOrder(6);
	this->addChild(wlayer);

	pPlayer->setOpacity(0);

	auto damagedEffect = Sprite::create("Sprite/death_P1.png");
	damagedEffect->setPosition(pPlayer->getPosition()); // �÷��̾��� ��ġ�� �� �ҷ���..; �̻��� �̰�
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

void GameManager::update(float f)
{
	if (MoveChance == 0)
		scheduleOnce(schedule_selector(GameManager::PlayerDie), 0.01f);
}

