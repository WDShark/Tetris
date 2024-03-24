#include <stdio.h> //for sprintf
#include <fstream>
#include <Windows.h>
#include <mmsystem.h> // for music, need include windows first
#include "Tetris.h"

#pragma comment(lib, "winmm.lib") //for music

void Tetris::showWelcome()
{
	char stopFlag = 0;
	const int x = 200;
	const int y = 541;
	initgraph(878, 1072);

	setcolor(RGB(180, 180, 180));

	LOGFONT f;
	gettextstyle(&f); //get font config
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT); // 透明背景

	while (1)
	{
		for (unsigned char i = 0; i < welcomeImgSize; i++)
		{
			putimage(0, 0, &imgWelcome[i]);
			outtextxy(x, y, "press any key to start");
			Sleep(80);
			if (_kbhit())
			{
				_getch();//clear receive
				stopFlag = 1;
				break;
			}
		}
		if (stopFlag) break;
	}
	
	closegraph();
}

void Tetris::handleKeyEvent()
{
	if (_kbhit())
	{
		char c = _getch();
		updateFlag = 1;
		switch (c)
		{
		case 72:
		case 'w':
			rotate();
			break;
		case 75:
		case 'a':
			moveLeft();
			break;
		case 77:
		case 'd':
			moveRight();
			break;
		case 80:
		case 's':
			updateDelayThr = FAST_SPEED;
			break;
		case 27:
			exit(0);
			break;//esc
		case ' ':
			while (_getch() != ' ');
			break;
		}
	}
}

unsigned int Tetris::getTimeDelay()
{
	static unsigned long long lastCnt = 0;
	unsigned int rst = 0;
	unsigned long long cnt = GetTickCount();
	if(!lastCnt)
	{
		rst = 0;
	}
	else
	{
		rst = (unsigned)(cnt - lastCnt);
	}
	lastCnt = cnt;
	
	return rst;
}

void Tetris::drop()
{
	Block temp = *curBlock;
	curBlock->drop();
	if (!canBlockMove())
	{
		//*curBlock = temp;
		solidBlock(temp);
		delete curBlock;
		curBlock = nextBlock;
		if (!canBlockMove())
		{
			gameOver = true;
			return;
		}
		nextBlock = new Block;
		clearLines();
	}
	updateDelayThr = dropSpeed;
}

void Tetris::moveLeft()
{
	Block temp = *curBlock;
	curBlock->moveLeftRight(Block::LEFT);
	if (!canBlockMove())
	{
		*curBlock = temp;
	}
}

void Tetris::moveRight()
{
	Block temp = *curBlock;
	curBlock->moveLeftRight(Block::RIGHT);
	if (!canBlockMove())
	{
		*curBlock = temp;
	}
}

void Tetris::rotate()
{
	Block temp = *curBlock;
	curBlock->rotate();
	if (!canBlockMove())
	{
		*curBlock = temp;
	}
}

bool Tetris::canBlockMove()
{
	const Point* blockPoint = curBlock->getBlockPoint();
	for (unsigned char i = 0; i < 4; i++)
	{
		if (blockPoint[i].row < 0 || blockPoint[i].row >= ROW_NUM \
			|| blockPoint[i].col < 0 || blockPoint[i].col >= COL_NUM\
			|| Block::NO_TYPE != map[blockPoint[i].row][blockPoint[i].col])
			return false;
	}
	return true;
}

void Tetris::solidBlock(const Block& b)
{
	const Point* blockPoint = b.getBlockPoint();
	Block::BlockType type = b.getBlockType();
	for (unsigned char i = 0; i < 4; i++)
	{
		map[blockPoint[i].row][blockPoint[i].col] = type;
	}
}

void Tetris::showMap(unsigned int leftShift, unsigned int topShift)
{
	for (char i = ROW_NUM - 1; i >= 0; i--)
	{
		unsigned char cnt = 0;
		for (unsigned char j = 0; j < COL_NUM; j++)
		{
			if (Block::NO_TYPE != map[i][j])
			{
				cnt++;
				putimage(leftShift + j * Block::size, topShift + i * Block::size, Block::imgBlock[map[i][j]]);
			}
		}	
		if (!cnt) return;
	}
}

static char g_score[4] = {10, 30, 50, 80};
void Tetris::clearLines()
{
	char k = ROW_NUM - 1;
	char i = ROW_NUM - 1;
	unsigned char lines = 0;
	unsigned char lineId[4];
	for (i = ROW_NUM - 1; i >= 0; i--)
	{
		unsigned char cnt = 0;
		for (unsigned char j = 0; j < COL_NUM; j++)
		{
			if (Block::NO_TYPE != map[i][j])
			{
				cnt++;
			}
			map[k][j] = map[i][j];
		}
		if (COL_NUM == cnt) // full line
		{
			lineId[lines++] = i;
		}
		else if(0 == cnt) // empty line
		{
			k--;
			break;
		}
		else
		{
			k--;
		}
	}

	for (; k > i; k--) // 填补空白
	{
		for (unsigned char j = 0; j < COL_NUM; j++)
		{
			map[k][j] = Block::NO_TYPE;
		}
	}
	
	if (lines)
	{
		//绘制消失动画
		drawClearLines(lineId, lines);
		txtLines += lines;
		txtScore += g_score[lines-1];
		txtSpeed = (txtScore + LEVEL_SCORE_THR - 1) / LEVEL_SCORE_THR;
		dropSpeed = NORMAL_SPEED - DELAY_TIME_DEC * (txtSpeed - 1);
	}
}

void Tetris::drawClearLines(unsigned char linesId[], unsigned char line)
{
	mciSendString("play ../res/xiaochu2.mp3 repeat", 0, 0, 0);
	for (unsigned char j = 0; j < clearImgSize; j++)
	{
		for (unsigned char i = 0; i < line; i++)
		{
			putimage(leftMargin, topMargin + linesId[i] * Block::size, &imgClear[j]);
		}
		Sleep(80);
	}
	mciSendString("stop ../res/xiaochu2.mp3", 0, 0, 0);
}

void Tetris::showGameOver()
{
	mciSendString("stop ../res/bg.mp3", 0, 0, 0);
	mciSendString("play ../res/over.mp3", 0, 0, 0);
	putimage(leftMargin, 430, &imgGameOver);
	outtextxy(leftMargin-90, 490, "press any key to restart");
	_getch();
}

void Tetris::showText()
{
	setcolor(RGB(180, 180, 180));

	LOGFONT f;
	gettextstyle(&f); //get font config
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT); // 透明背景

	char txt[20];

	sprintf_s(txt, sizeof(txt), "%d", txtScore);
	outtextxy(668, 730, txt);

	sprintf_s(txt, sizeof(txt), "%d", txtMaxScore);
	outtextxy(668, 815, txt);

	sprintf_s(txt, sizeof(txt), "%d", txtSpeed);
	outtextxy(192 - f.lfWidth * ((int)strlen(txt) - 1), 730, txt);

	sprintf_s(txt, sizeof(txt), "%d", txtLines);
	outtextxy(192 - f.lfWidth * ((int)strlen(txt) - 1), 815, txt);
}

void Tetris::restart()
{
	//clear
	delete curBlock;
	//delete nextBlock; // no next block when game over
	for (unsigned char i = 0; i < ROW_NUM; i++)
	{
		for (unsigned char j = 0; j < COL_NUM; j++)
		{
			map[i][j] = (Block::NO_TYPE);
		}
	}

	initData();

	//out put
	mciSendString("play ../res/bg.mp3 repeat", 0, 0, 0);
	initgraph(938, 896);
	putimage(0, 0, &imgBg);

}

void Tetris::initData()
{
	//initialize data
	updateFlag = 0;
	updateDelayTime = 0;
	updateDelayThr = dropSpeed;
	gameOver = false;
	txtScore = 0;
	txtLines = 0;
	txtMaxScore = 0;
	txtSpeed = 1;
	dropSpeed = NORMAL_SPEED;

	std::ifstream file(SCORE_FILE);
	if (file.is_open())
	{
		file >> txtMaxScore;
	}

	curBlock = new Block;
	nextBlock = new Block;
}

void Tetris::init()
{
	initData();

	for (unsigned char i = 0; i < ROW_NUM; i++)
	{
		std::vector<Block::BlockType> temp;
		for (unsigned char j = 0; j < COL_NUM; j++)
		{
			temp.push_back(Block::NO_TYPE);
		}
		map.push_back(temp);
	}

	//load welcome image
	char imgName[50];
	for (unsigned char i = 0; i < welcomeImgSize; i++)
	{
		sprintf_s(imgName, "../res/welcome/welcome (%d).png", i+1);
		loadimage(&imgWelcome[i], imgName);// 要把项目属性改成使用多字符集才行
	}

	//load clear image
	for (unsigned char i = 0; i < clearImgSize; i++)
	{
		sprintf_s(imgName, "../res/tx/%d.png", i);
		IMAGE imgTmp;
		loadimage(&imgTmp, imgName);
		SetWorkingImage(&imgTmp);
		getimage(&imgClear[i], 6, 56, 360, 36);
		SetWorkingImage();
		//loadimage(&imgClear[i], imgName);// 要把项目属性改成使用多字符集才行
	}

	//load background image
	loadimage(&imgBg, "../res/bg2.png");// 要把项目属性改成使用多字符集才行，不然要在文件名前加L

	//load game over
	loadimage(&imgGameOver, "../res/over.png");// 要把项目属性改成使用多字符集才行，不然要在文件名前加L

	//out put
	mciSendString("play ../res/bg.mp3 repeat", 0, 0, 0);
	showWelcome();
	initgraph(938, 896);
	putimage(0, 0, &imgBg);
}

Tetris::Tetris(unsigned leftMargin, unsigned rightMargin, unsigned topMargin, unsigned bottomMargin)
{
	this->leftMargin	  = leftMargin	 ;
	this->rightMargin	  = rightMargin	 ;
	this->topMargin		  = topMargin	 ;
	this->bottomMargin	  = bottomMargin ;

	init();
}

void Tetris::play()
{
	while (1)
	{
		handleKeyEvent();

		updateDelayTime += getTimeDelay();
		if (updateDelayTime > updateDelayThr)
		{
			updateDelayTime = 0;
			updateFlag = 1;
			drop();
		}

		if (updateFlag)
		{
			updateFlag = 0;
			update();
			if (gameOver)
			{
				if (txtScore > txtMaxScore)
				{
					std::ofstream file(SCORE_FILE);
					if (file.is_open())
					{
						file << txtScore;
					}
				}
				showGameOver();
				restart();
			}
		}
	}
}

void Tetris::update()
{
	//show whole image
	BeginBatchDraw();

	putimage(0, 0, &imgBg);
	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(rightMargin - Block::size, topMargin + Block::size);
	showMap(leftMargin, topMargin);
	showText();

	EndBatchDraw();

}
