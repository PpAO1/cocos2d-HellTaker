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
	switch (Stage)
	{
	case Stage1:
		break;
	case Stage2:
		break;
	case Stage3:
		break;
	default:
		break;
	}
}
