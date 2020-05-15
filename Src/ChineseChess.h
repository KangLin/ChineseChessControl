#ifndef _CHINESE_CHESS_H_KL_2020_05_13__
#define _CHINESE_CHESS_H_KL_2020_05_13__

#pragma once

#include <string>
#include <vector>

#include "EnumAndStructAndConst.h"
#include "GoRule.h"

class CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

	//走棋状态
	typedef enum _ENUM_WalkState {
		RedReadly,
		RedWalked,
		BlackReadly,
		BlackWalked
	} ENUM_WalkState;

	//棋盘布局:详见《象棋竞赛规则(2011)》第一章 第1条
	typedef enum  _ENUM_BoardLayout{
		NoQi = 0,
		OnlyTopBlack = 1,
		OnlyBottomRed = 2,
		SwapRedBetweenBlack = 4,
		OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
		OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
		TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
		TopRedAndBottomBlack = TopBlackAndBottomRed | SwapRedBetweenBlack
	} ENUM_BoardLayout;
	int SetBoardLayout(ENUM_BoardLayout layout);
	int GetBoard(int &row, int &col);
	int GetBoardRow();
	int GetBoardColumn();

	bool GoChess(int i, int j);
	bool IsGoChess(int i, int j);
	//int NextStep();                              //下一步
	//int PreviouStep();                           //上一步
	//int ReStart();                               //重新开始
	//int SaveChess(char* pFileName);          //保存棋局
	//int LoadChess(char* pFileName);          //装载棋局，并设置为结束状态
	//int LoadChessStart(char* pFileName);     //装载棋局，并设置为开始状态

protected:
	enum PROMPT_SOUND {
		JiangJun, // 将军
		Eat,      // 吃子
		Go,       // 走棋
		NoGo,     // 不能走
		Select    // 选棋
	};
	virtual int onPromptSound(PROMPT_SOUND sound) = 0;
	virtual int onPromptMessage(char* pMessage, char* pTitle = nullptr) = 0;

	virtual int onCleanPrompt(int i, int j) = 0;
	virtual int onDrawPrompt(int i, int j) = 0;
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;

private:
	int Initial();
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma = BianMa);
	bool IsValidPosition(int i, int j);

	/*
	    棋盘描述

	     (0,0) ------------------> i 或 x 方向
		      |
			  |
			  |
			  |
			  |
			  |
			 \|/
			  
	      j 或 y 方向

	*/
	static const int m_BoardRow = 10;
	static const int m_BoardColumn = 9;
	CPiece::ENUM_QiZi m_ChessBoard[m_BoardColumn][m_BoardRow]; //棋盘 m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;//棋盘布局
	ENUM_WalkState m_WalkState;    //走棋状态（红方选棋，红方走棋，黑方先棋，黑方走棋）

	// 上一步棋的位置
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;

	int m_iBuShu;                  //走棋步数
	bool m_bFuPang;                //复盘标志
	std::vector<int> m_QiJu;       //棋局

	CGoRule m_GoRule;
};

#endif //_CHINESE_CHESS_H_KL_2020_05_13__
