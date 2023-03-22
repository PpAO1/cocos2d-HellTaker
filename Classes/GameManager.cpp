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
	auto wlayer = LayerColor::create(Color4B::WHITE);
	this->addChild(wlayer);
	ui = new UI;

	ui->setPosition(Vec2(0, 0));
	ui->setAnchorPoint(Vec2(0, 0));
	ui->setZOrder(1111);
	ui->init();
	this->addChild(ui);
	return true;
}
