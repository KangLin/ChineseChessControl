﻿/**
 * 棋局类
 */
 
#ifndef _CHESS_GAME_KL_2020_05_15_
#define _CHESS_GAME_KL_2020_05_15_

#pragma once

#include <vector>
#include <string>
#include <time.h>
#include "Piece.h"
#include "chinesechess_export.h"

/**
 * 棋局
 * 完成棋局的加载、保存、复盘
 * 注意：棋盘布局:详见《象棋竞赛规则(2011)》第一章 第1条
 *      红棋在下，黑棋在下，
 * 	
        棋盘位置

	    [0][0] ------------------> i 或 x 方向
		      |
			  |
			  |
			  |
			  |
			  |
			 \|/                 [9][10]
			  
	      j 或 y 方向

	
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CHINESECHESS_EXPORT CChessGame
{
public:
	CChessGame();
	virtual ~CChessGame();

	// 调整棋局存储大小，用于保存棋局
	int SaveStep(char i, char j,
                 CPiece::ENUM_QiZi qz,
                 const char* pDescript = nullptr,
                 time_t tm = time(nullptr)); //保存当前步
	int RevokeStep();						 //撤回当前步

	// 只移动指针位置，不改变棋局存储大小。用于复盘
    int GetPreviouStep(char &i, char &j, CPiece::ENUM_QiZi &qz); //得到上一步
	int GetNextStep(char &i, char &j, CPiece::ENUM_QiZi &qz);    //得到下一步

	time_t GetStartTime();
	int SetStartTime(const time_t &t);
	time_t GetEndTime();
	int SetEndTime(const time_t &t);

	std::string GetRedName();
	int SetRedName(const char* pszName);
	std::string GetBlackName();
	int SetBlackName(const char* pszName);

	std::string GetTags();
	int SetTags(const char* pTags);

#define MAX_STRING_BUFFER 33
#define APPNAME  "Chinese chess control"
#define AUTHOR "Author: Kang Lin (kl222@126.com)"

	enum GAME_TYPE
	{
		NORMAL = 1, //正常开局
		CHANGJU = 2 //残局
	};

	//文件头
	struct strFileHead {
		char szAppName[MAX_STRING_BUFFER];    //程序名,在Restart中设置
		char szAuthor[MAX_STRING_BUFFER];     //程序作者：康林,在Restart中设置
		char dwVersion;                       //版本,在Restart中设置
	};
    //注意：为网络字节序
	struct strFile {
		strFileHead head;					 
		time_t timeStart;				     //开始下棋的时间,在Restart中设置，注意：为网络字节序
		time_t timeEnd;					     //结束下棋的时间,在Restart中设置，注意：为网络字节序
		char szRedName[MAX_STRING_BUFFER];	 //红方用户名
		char szBlackName[MAX_STRING_BUFFER]; //黑方用户名
		char GameType;						 //棋局类型
		int iBuShu;							 //步数，在SaveChess中设置，注意：为网络字节序
		char boardLayout;					 //棋盘布局(CChineseChess::ENUM_BoardLayout)
	};										 

	/**
	 * Saves the chess game
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/19
	 *
	 * @param  pFileName Filename of the file.
	 * @param  layout    棋盘布局(CChineseChess::ENUM_BoardLayout)
	 *
	 * @returns An int.
	 */
	int SaveChessGame(const char* pFileName, char layout);	//保存棋局
    int LoadChessGame(const char* pFileName, char &layout);	//装载棋局，并设置为结束状态

private:
	struct strCODE{
		char code[3];           //棋子和相应的位置 @see QiZiBianMa
	};
	struct strStep {
		strCODE code;
        time_t tm;
		std::string szDescript; //这一步的描述信息
	};
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(char *i, char *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma = BianMa);

	int WriteStringToFile(std::ofstream &o, std::string &s);
	int ReadStringFromFile(std::ifstream &i, std::string &s);

	int m_nIndex;					  //走棋步数
	bool m_bFuPang;					  //复盘标志
	std::vector<strStep> m_ChessGame; //棋局

	time_t m_tmStart;			      //开始时间
	time_t m_tmEnd;				      //结束时间
	std::string m_szRedName;		  //红方名
	std::string m_szBlackName;		  //黑方名
	std::string m_szTags;             //保存棋局的标签部分，标签用来描述此局的信息
};

#endif //_CHESS_GAME_KL_2020_05_15_
