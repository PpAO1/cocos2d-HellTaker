#pragma once
#include <fstream>
#include <string>

#define STAGE1_WIDTH 9
#define STAGE1_HEIGHT 8
#define STAGE1_START_POS_X 510
#define STAGE1_START_POS_Y 140

#define CELL_WIDTH 100
#define CELL_HEIGHT 100

enum MapObject
{
	EMPTY,
	PLAYER,
	SKELETON,
	SPIKE,
	WALL,
	ROCK,
	LOCK,
	KEY,
	NPC
};

enum Stage
{
	Stage1 = 1,
	Stage2,
	Stage3
};


class Coordinate
{
public:
	int x;
	int y;
	

	Coordinate()
	{

	}

	Coordinate(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	// 비교
	bool Equare(Coordinate obj)
	{
		if ((this->x == obj.x) && (this->y == obj.y))
			return true;
		else
			return false;
	}

	// 해당 객체 += 연산자로 접근 가능하도록 함
	Coordinate operator+= (Coordinate obj)
	{
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;

		return *this;
	}
};