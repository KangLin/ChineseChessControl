 
#ifndef CHESS_GAME_KL_2020_05_15_
#define CHESS_GAME_KL_2020_05_15_

#pragma once

#include <vector>
#include <string>
#include <map>
#include <time.h>
#include "Piece.h"
#include "chinesechess_export.h"

/**
 * 棋局类
 * 完成棋局的加载、保存、复盘等对棋局的操作
 * 注意：棋盘布局:详见《象棋竞赛规则(2011)》第一章 第1条
 *      红棋在下，黑棋在上，左上角为[0][0]，右下角为[9][10]

        棋盘位置
        @code

	    [0][0] ------------------> i 或 x 方向
		      |
			  |
			  |
			  |       [i][j]
			  |
			  |
			 \|/                 [9][10]
			  |
	      j 或 y 方向

       @endcode

   行棋，红方先行：详见《象棋竞赛规则(2011)》第一章 第2条
 * @author 康林 <kl222@126.com>
 * @date 2020/5/17
 */
class CHINESECHESS_EXPORT CChessGame
{
public:
	CChessGame();
	virtual ~CChessGame();

    // 保存一步
	// 调整棋局存储大小，用于保存棋局
	int SaveStep(int i, int j,
                 CPiece::ENUM_QiZi qz,
                 const char* pDescript = nullptr,
                 time_t tm = time(nullptr)); //保存当前步
	int RevokeStep();						 //撤回当前步

	// 只移动指针位置，不改变棋局存储大小。用于复盘
    int GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz); //得到上一步
	int GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz);    //得到下一步

	time_t GetStartTime();
	int SetStartTime(const time_t &t);
	time_t GetEndTime();
	int SetEndTime(const time_t &t);

	std::string GetRedName();
	int SetRedName(const char* pszName);
	std::string GetBlackName();
	int SetBlackName(const char* pszName);
    
    std::string GetTag(const std::string &szpTag);
    int AddTag(const std::string &szTag, const std::string &szVal);

#define MAX_STRING_BUFFER 33
#define APPNAME "Chinese chess control"
#define AUTHOR "Author: Kang Lin (kl222@126.com)"

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
		int iBuShu;							 //步数，在SaveChess中设置，注意：为网络字节序
	};										 

	/**
	 * Saves the chess game
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/19
	 *
	 * @param  pFileName Filename of the file.
	 *
	 * @returns An int.
	 */
	int SaveChessGame(const char* pFileName);	//保存棋局
    int LoadChessGame(const char* pFileName);	//装载棋局，并设置为结束状态
    
    enum _SavePgnFormat
    {
        ICCS,
        Chinese,
        WXF
    };
    int SaveChessGamePgn(const char* pFileName, _SavePgnFormat f = Chinese);
    int LoadChessGamePgn(const char* pFileName, _SavePgnFormat f = Chinese);
    
    //开局
    struct strStartGame
    {
        int i;
        int j;
        CPiece::ENUM_QiZi qz;
    };
    std::vector<strStartGame> m_StartGame; // 棋盘开局
    /// 检测布局是否合法, 使用标准棋盘布局，红下黑上
    static int CheckGame(const CPiece::ENUM_QiZi board[][10]);
    /**
     * @brief 得到开局棋盘布局
     * @param board 返回开局棋盘布局
     * @return 成功，返回0，失败，返回非0
     */
    int GetStartGameBoard(/*[out]*/CPiece::ENUM_QiZi board[][10]);

private:
	struct strCODE{
		char step[3];           //棋子和相应的位置 @see QiZiBianMa
	};
	struct strStep {
		strCODE code;
        time_t tm;              //走棋时间
		std::string szDescript; //这一步的描述信息
	};
	typedef enum _ENUM_BianMa {
		BianMa, 
		JieMa
	} ENUM_BianMa;
	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma = BianMa);

	int WriteStringToFile(std::ofstream &o, std::string &s);
	int ReadStringFromFile(std::ifstream &i, std::string &s);

	int m_nIndex;					  //走棋步数
	bool m_bFuPang;					  //复盘标志
	std::vector<strStep> m_ChessGame; //棋局

	time_t m_tmStart;			      //开始时间
	time_t m_tmEnd;				      //结束时间
	std::string m_szRedName;		  //红方名
	std::string m_szBlackName;		  //黑方名
	std::map<std::string, std::string> m_Tags; //保存棋局的标签部分，标签用来描述此局的信息

};

#endif //CHESS_GAME_KL_2020_05_15_
