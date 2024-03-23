#pragma once
#include <graphics.h>
#include <conio.h>
#include <vector>
#include "Block.h"

const char SCORE_FILE[] = "score.txt";
const unsigned int LEVEL_SCORE_THR = 100;
const unsigned int DELAY_TIME_DEC = 30;
const unsigned int NORMAL_SPEED = 500;
const unsigned int FAST_SPEED = 30;
const unsigned char ROW_NUM = 20;
const unsigned char COL_NUM = 10;


class Tetris
{
private:
	static const unsigned char welcomeImgSize = 78;
	static const unsigned char clearImgSize = 12;
	unsigned dropSpeed;
	unsigned leftMargin;
	unsigned rightMargin;
	unsigned topMargin;
	unsigned bottomMargin;
	std::vector<std::vector<Block::BlockType>> map;
	IMAGE imgWelcome[welcomeImgSize];
	IMAGE imgBg;
	IMAGE imgGameOver;
	IMAGE imgClear[clearImgSize];
	unsigned char updateFlag;
	unsigned int  updateDelayThr;
	unsigned int  updateDelayTime;
	unsigned txtScore;
	unsigned txtLines;
	unsigned txtMaxScore;
	unsigned txtSpeed;
	bool gameOver;
	Block *curBlock;
	Block *nextBlock;



	void init();
	void update();
	void showWelcome();
	void handleKeyEvent();
	unsigned int getTimeDelay();
	void drop();
	void moveLeft();
	void moveRight();
	void rotate();
	bool canBlockMove();
	void solidBlock(const Block& b);
	void showMap(unsigned int leftShift, unsigned int topShift);
	void clearLines();
	void drawClearLines(unsigned char linesId[], unsigned char line);
	void showGameOver();
	void showText();
	void restart();
	void initData();

public:
	Tetris(unsigned leftMargin, unsigned rightMargin, unsigned topMargin, unsigned bottomMargin);	
	void play();	
};

