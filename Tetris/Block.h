#pragma once
#include <graphics.h>

struct Point
{
	char row;
	char col;
};

class Block
{
public:
	enum Direction
	{
		LEFT = -1,
		RIGHT = 1,
	};
	enum BlockType
	{
		NO_TYPE = -1,
		I = 0,
		Z1,
		Z2,
		T,
		L,
		J,
		O,
		TYPE_NUM
	};

private:
	BlockType type;
	Point smallBlock[4];
	IMAGE* img;

public:
	static IMAGE* imgBlock[TYPE_NUM];
	static unsigned char size;

	Block();
	Block(const Block& b);
	Block& operator=(const Block& b);
	void draw(unsigned int leftShift, unsigned int topShift);
	void rotate();
	void drop();
	void moveLeftRight(Direction direction);
	const Point* getBlockPoint() const;
	const BlockType getBlockType() const;
};

