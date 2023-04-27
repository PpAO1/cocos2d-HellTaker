#pragma once
#include <fstream>
#include <string>

#define STAGE1_WIDTH 8
#define STAGE1_HEIGHT 9

#define STAGE2_WIDTH 8
#define STAGE2_HEIGHT 9

#define STAGE3_HEIGHT 10
#define STAGE3_WIDTH 9

#define STAGE4_HEIGHT 10
#define STAGE4_WIDTH 7

#define STAGE1_2_START_POS_X 560
#define STAGE1_2_START_POS_Y 210

#define STAGE3_START_POS_X 510
#define STAGE3_START_POS_Y 130

#define STAGE4_START_POS_X 510
#define STAGE4_START_POS_Y 130

#define CELL 100


enum MapObject
{
	EMPTY = 0,
	PLAYER = 1,
	SKELETON = 2,
	SPIKE = 3,
	WALL = 4,
	ROCK = 5,
	LOCK = 6,
	KEY = 7,
	NPC = 8,
	GOAL = 9,
	SPIKEONROCK = 10,
	SPIKEONPLAYER = 11,
};

enum Stage
{
	Stage1,
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
	Coordinate operator-= (Coordinate obj)
	{
		this->x = this->x - obj.x;

		this->y = this->y - obj.y;

		return *this;
	}
};