#include <stdlib.h>
#include <time.h>
#include "Block.h"

IMAGE* Block::imgBlock[TYPE_NUM] = {NULL, };
unsigned char Block::size = 36;

Block::Block(const Block& b)
{
	type = b.type;
	img = b.img;
	for (unsigned char i = 0; i < 4; i++)
	{
		smallBlock[i].col = b.smallBlock[i].col;
		smallBlock[i].row = b.smallBlock[i].row;
	}
}

Block& Block::operator=(const Block& b)
{
	if (this == &b) return *this;

	type = b.type;
	img = b.img;
	for (unsigned char i = 0; i < 4; i++)
	{
		smallBlock[i].col = b.smallBlock[i].col;
		smallBlock[i].row = b.smallBlock[i].row;
	}
	return *this;
}

Block::Block()
{
	if (!imgBlock[0]) //load once
	{
		IMAGE imgTmp;
		loadimage(&imgTmp, "../res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < TYPE_NUM; i++) {
			imgBlock[i] = new IMAGE;
			getimage(imgBlock[i], i * size, 0, size, size);
		}
		SetWorkingImage();
		srand((unsigned)time(NULL));
	}
	type = BlockType(rand() % TYPE_NUM);
	img = imgBlock[type];

	int blocks[7][4] = {
		1,3,5,7, // I
		0,2,3,5, // Z 1
		1,3,2,4, // Z 2
		1,3,2,5, // T
		0,1,3,5, // L
		1,5,3,4, // J
		0,1,2,3  // O
	};
	for (char i = 0; i < 4; i++) {
		smallBlock[i].row = blocks[type][i] / 2;
		smallBlock[i].col = blocks[type][i] % 2;
	}

	char rotate = rand() % 4; // random rotate
	for (char i = 0; i < rotate; i++)
	{
		this->rotate();
	}

	char minRow = 0x7F; // put block in the center
	char minCol = 0x7F;
	for (char i = 0; i < 4; i++) {
		if (minRow > smallBlock[i].row) minRow = smallBlock[i].row;
		if (minCol > smallBlock[i].col) minCol = smallBlock[i].col;
	}
	minCol -= 4;
	for (char i = 0; i < 4; i++) {
		smallBlock[i].row -= minRow;
		smallBlock[i].col -= minCol;
	}
}

void Block::draw(unsigned int leftShift, unsigned int topShift)
{
	for (int i = 0; i < 4; i++) {
		putimage(leftShift + smallBlock[i].col * size, topShift + smallBlock[i].row * size, img);
	}
}


void Block::rotate()
{
	if (Block::O == type) return;
	Point center = smallBlock[1];
	for (int i = 0; i < 4; i++) {
		if (1 == i) continue;
		Point temp = smallBlock[i];
		smallBlock[i].row = center.row - temp.col + center.col;
		smallBlock[i].col = center.col + temp.row - center.row;
	}
}

void Block::drop()
{
	for (int i = 0; i < 4; i++) {
		smallBlock[i].row += 1;
	}
}

void Block::moveLeftRight(Direction direction)
{
	for (int i = 0; i < 4; i++) {
		smallBlock[i].col += direction;
	}
}

const Point* Block::getBlockPoint() const
{
	return smallBlock;
}

const Block::BlockType Block::getBlockType() const
{
	return type;
}
