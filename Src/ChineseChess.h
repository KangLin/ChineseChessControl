#pragma once

#include <string>

#include "EnumAndStructAndConst.h"
#include "GoRule.h"

class CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

	//走棋状态
	enum ENUM_WalkState { RedReadly, RedWalked, BlackReadly, BlackWalked };
	//棋盘布局:详见《象棋竞赛规则(2011)》第一章 第1条
	enum ENUM_BoardLayout {
		NoQi = 0,
		OnlyTopBlack = 1,
		OnlyBottomRed = 2,
		SwapRedBetweenBlack = 4,
		OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
		OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
		TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
		TopRedAndBottomBlack = OnlyTopRed | OnlyBottomBlack | SwapRedBetweenBlack
	};

	int GetBoardRown();
	int GetBoardColumn();

	bool GoChess(int i, int j, bool bEvent = true);
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
		Select    // 选棋
	};
	virtual int onPromptSound(PROMPT_SOUND sound) = 0;
	virtual int onPromptMessage(char* pMessage, char* pTitle = nullptr) = 0;

private:
	int Initial();

private:
	static const int m_BoardRow = 9;
	static const int m_BoardColumn = 10;

	ENUM_QiZi m_ChessBoard[m_BoardRow][m_BoardColumn]; //棋盘 m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;//棋盘布局
	ENUM_WalkState m_WalkState;    //走棋状态（红方选棋，红方走棋，黑方先棋，黑方走棋）

	int m_iBuShu;                  //走棋步数
	bool m_bFuPang;                //复盘标志

	// 上一步棋的位置
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;

	CGoRule m_GoRule;
};

