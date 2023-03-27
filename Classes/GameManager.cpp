#include "GameManager.h"

USING_NS_CC;
using namespace std;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{

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
	ui = new UI;

	ui->setPosition(Vec2(0, 0));
	ui->setAnchorPoint(Vec2(0, 0));
	ui->setZOrder(500);
	ui->init();
	this->addChild(ui);
	return true;
}

void GameManager::FileDataRead()
{
	switch (stage)
	{
	case Stage1:
		TextFileRead("Stage1.txt", 10);
		break;
	case Stage2:
		break;
	case Stage3:
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
			}
			else if (stage1Map[i][j] == MapObject::SPIKE)
			{
				Spike* pSpike = &Spike::getInstance();
			}
			else if (stage1Map[i][j] == MapObject::ROCK)
			{
				
			}
			else if (stage1Map[i][j] == MapObject::KEY)
			{
				fileName = "Key.png";
			}
			else if (stage1Map[i][j] == MapObject::LOCK)
			{
				fileName = "Lock.png";
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


