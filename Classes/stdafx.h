#pragma once
#include <fstream>
#include <string>

#define STAGE1_WIDTH 10
#define STAGE1_HEIGHT 9

#define CELL_WIDTH 75
#define CELL_HEIGHT 75

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

	// ��
	bool Equare(Coordinate obj)
	{
		if ((this->x == obj.x) && (this->y == obj.y))
			return true;
		else
			return false;
	}

	// �ش� ��ü += �����ڷ� ���� �����ϵ��� ��
	Coordinate operator+= (Coordinate obj)
	{
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;

		return *this;
	}
};