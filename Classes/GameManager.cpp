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
		while (!readFile.eof())
		{
			char nObjNum;

			readFile.get(nObjNum);

			if (nObjNum == ' ' || nObjNum == '\n')
				continue;

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
				Player* pPlayer = &Player::getInstance();
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
				Skeleton* pSkeleton = &Skeleton::getInstance();
				pSkeleton->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pSkeleton->setAnchorPoint(Vec2(0, 0));
				pSkeleton->setZOrder(3);
				this->addChild(pSkeleton);
			}
			else if (stage1Map[i][j] == MapObject::SPIKE)
			{
				Spike* pSpike = &Spike::getInstance();
				pSpike->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pSpike->setAnchorPoint(Vec2(0, 0));
				pSpike->setZOrder(3);
				this->addChild(pSpike);
			}
			else if (stage1Map[i][j] == MapObject::ROCK)
			{
				Rock* pRock = &Rock::getInctance();
				pRock->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pRock->setAnchorPoint(Vec2(0, 0));
				pRock->setZOrder(3);
				this->addChild(pRock);
			}
			else if (stage1Map[i][j] == MapObject::KEY)
			{
				Key* pKey = &Key::getInstance();
				pKey->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pKey->setAnchorPoint(Vec2(0, 0));
				pKey->setZOrder(3);
				this->addChild(pKey);
			}
			else if (stage1Map[i][j] == MapObject::LOCK)
			{
				Lock* pLock = &Lock::getInstance();
				pLock->setPosition((STAGE1_START_POS_X + (j * CELL)), (STAGE1_START_POS_Y + (i * CELL)));
				pLock->setAnchorPoint(Vec2(0, 0));
				pLock->setZOrder(3);
				this->addChild(pLock);
			}
			else if (stage1Map[i][j] == MapObject::NPC)
			{
				fileName = "Stage1NPC.png";
			}

			if (fileName != "null")
			{
				Obj->setTexture(fileName);
				//Obj->setPosition();
				Obj->setAnchorPoint(Vec2(0, 0));
				Obj->setZOrder(2);
				this->addChild(Obj);
			}
		}
	}
}


