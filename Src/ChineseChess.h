/**
 * @file ChineseChess.h.
 *
 * 中国象棋类
 * 
 */
 
#ifndef _CHINESE_CHESS_H_KL_2020_05_13__
#define _CHINESE_CHESS_H_KL_2020_05_13__

#pragma once

#include "GoRule.h"
#include "ChessGame.h"

#include "chinesechess_export.h"

/**
 * 中国象棋类
 * - 实现中国象棋的基本规则
 * - 实现复盘  
 * - 实现复盘棋局  
 * 
 * 界面部分由相应的界面派生类实现相应的虚拟函数
 * 
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CHINESECHESS_EXPORT CChineseChess
{
public:
	CChineseChess();
	virtual ~CChineseChess();

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

	/**
	 * Go chess
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/17
	 *
     * @param  int i：当前下棋的位置,横坐标[0-8]
     * @param  int j：当前下棋的位置,纵坐标[0-9]
	 * @param  bNext (Optional) 指示是否是在NextStep中调用
	 * 				 如果是在 NextStep 中调用，则是在复盘
	 * 				 如果不是。则是在正常下棋
	 *
	 * @returns True if it succeeds, false if it fails.
	 */
	bool GoChess(int i, int j, bool bNext = false);	//走棋

	// 复盘操作
	int NextStep();	   //下一步
	int PreviouStep(); //上一步

	//保存棋局
	int SaveChessGame(const char* pszFile);
	int LoadChessGame(const char* pszFile);

	int EnablePromptSound(bool sound = true);
	int EnablePromptMessage(bool bMsg = true);

protected:
	// 下列虚拟函数由界面实现类完成
	
	// 提示音
	enum PROMPT_SOUND {
		JiangJun, // 将军
		Eat,      // 吃子
		Go,       // 走棋
		NoGo,     // 不能走
		Select    // 选棋
	};
	virtual int onPromptSound(PROMPT_SOUND sound = NoGo) = 0;
	// 提示错误消息
	virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val) = 0;
	// 清除提示框
	virtual int onCleanPrompt(int i, int j) = 0;
	// 画提示框
	virtual int onDrawPrompt(int i, int j) = 0;
	// 走棋事件
	// @see 棋盘描述
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;

private:
	// 判断当前着法是否合法
	bool IsGoChess(int i, int j);

	CGoRule m_GoRule;  //下棋规则
	CChessGame m_Game; //棋局

	bool m_bPromptSound;
	bool m_bPromptMessage;

protected:
	/*
	    @brief 棋盘描述

	    [0][0] ------------------> i 或 x 方向
		      |
			  |
			  |
			  |
			  |
			  |
			 \|/                 [9][10]
			  
	      j 或 y 方向

	*/
	CPiece::ENUM_QiZi m_ChessBoard[9][10]; //棋盘 m_ChessBoard[i][j]
	ENUM_BoardLayout m_BoardLayout;		   //棋盘布局

	//走棋状态
	typedef enum _ENUM_WalkState {
		RedReadly,
		RedWalked,
		BlackReadly,
		BlackWalked
	} ENUM_WalkState;			
	ENUM_WalkState m_WalkState;	//走棋状态（红方选棋，红方走棋，黑方先棋，黑方走棋）

	// 提示框
	// 上一步棋的位置
	int m_PreviouPositionX;
	int m_PreviouPositionY;
	int m_CurrentPositionX;
	int m_CurrentPositionY;
	int CleanPrompt(int &i, int &j); //清理指定位置的提示框

	bool IsValidPosition(int i, int j);

	int Initial();
	
};

#endif //_CHINESE_CHESS_H_KL_2020_05_13__
