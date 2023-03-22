#pragma once
#include <fstream>
#include <string>

#define MAP_WIDTH 28
#define MAP_HEIGHT 31

#define CELL_WIDTH 17
#define CELL_HEIGHT 17

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