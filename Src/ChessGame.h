
#ifndef _CHESS_GAME_KL_2020_05_15_
#define _CHESS_GAME_KL_2020_05_15_

#pragma once

#include "Piece.h"
#include <vector>

class CChessGame
{
public:
	CChessGame();
	virtual ~CChessGame();

	int SaveStep(int i, int j, CPiece::ENUM_QiZi qz); //保存当前步
	int RevokeStep();								  //撤回当前步

    int GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz); //得到上一步
	int GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz);	   //得到下一步

//int ReStart();                               //重新开始
//int SaveChess(char* pFileName);          //保存棋局
//int LoadChess(char* pFileName);          //装载棋局，并设置为结束状态
//int LoadChessStart(char* pFileName);     //装载棋局，并设置为开始状态

private:
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, INT32 *Code, ENUM_BianMa bianma = BianMa);

	int m_nIndex;				  //走棋步数
	bool m_bFuPang;				  //复盘标志
	std::vector<int> m_ChessGame; //棋局

};

#endif //_CHESS_GAME_KL_2020_05_15_