
#include "ChineseChess.h"
#include <iostream>

CChineseChess::CChineseChess()
{
	m_bPromptSound = true;
	m_bPromptMessage = true;
	SetBoardLayout(TopBlackAndBottomRed);
}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	m_WalkState = RedReadly;
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;

	return 0;
}

CChineseChess::ENUM_BoardLayout CChineseChess::GetBoardLayout()
{
	return m_BoardLayout;
}

int CChineseChess::SetBoardLayout(ENUM_BoardLayout layout)
{
	Initial();
	m_BoardLayout = layout;

    CPiece::ENUM_QiZi board[9][10];
	//初始化空棋局
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
        {
            m_ChessBoard[i][j] = CPiece::NoQiZi;
            board[i][j] = CPiece::NoQiZi;
        }
    
    if(m_Game.m_StartGame.size())
    {
        std::vector<CChessGame::strStartGame>::iterator it;
        for(it = m_Game.m_StartGame.begin(); it != m_Game.m_StartGame.end(); it++)
        {
            if((CPiece::IsRedQiZi(it->qz) && (m_BoardLayout & OnlyBottomRed))
                    || (CPiece::IsBlackQiZi(it->qz) && (m_BoardLayout & OnlyTopBlack)))
                board[it->i][it->j] = it->qz;
        }
        int nRet = m_Game.CheckGame(board);
        if(nRet) return nRet;
        
        for(i = 0; i < 9; i++)
            for(j = 0; j < 10; j++)
            {
                if(CPiece::IsExistQiZi(board[i][j]))
                {                    
                    int x, y;
                    ConvertQiPang(i, j, x, y);
                    m_ChessBoard[x][y] = board[i][j];
                }
            }
    }
    else
    {
        if (m_BoardLayout & OnlyTopBlack)
        {
            if (m_BoardLayout & SwapRedBetweenBlack)
            {
                m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::RChe;
                m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::RMa;
                m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::RXiang;
                m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::RShi;
                m_ChessBoard[4][0] = CPiece::RShuai;
                m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::RPao;
                m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::RBing;
            }
            else {
                m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::BChe;
                m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::BMa;
                m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::BXiang;
                m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::BShi;
                m_ChessBoard[4][0] = CPiece::BShuai;
                m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::BPao;
                m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::BBing;
            }
        }
        
        if (m_BoardLayout & OnlyBottomRed)
        {
            if (m_BoardLayout & SwapRedBetweenBlack)
            {
                m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::BChe;
                m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::BMa;
                m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::BXiang;
                m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::BShi;
                m_ChessBoard[4][9] = CPiece::BShuai;
                m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::BPao;
                m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::BBing;
            }
            else {
                m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::RChe;
                m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::RMa;
                m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::RXiang;
                m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::RShi;
                m_ChessBoard[4][9] = CPiece::RShuai;
                m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::RPao;
                m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::RBing;
            }
        }
    }
    
    return 0;
}

bool CChineseChess::IsValidPosition(int i, int j)
{
	if (i < 0 || i > 9 - 1 || j < 0 || j > 10 - 1)
	{   //出界
		return false;
	}
	return true;
}

int CChineseChess::EnablePromptSound(bool sound)
{
	m_bPromptSound = sound;
	return 0;
}

bool CChineseChess::getEnablePromptSound()
{
    return m_bPromptSound;
}

int CChineseChess::EnablePromptMessage(bool bMsg)
{
	m_bPromptMessage = bMsg;
	return 0;
}

bool CChineseChess::getEnablePromptMessage()
{
    return m_bPromptMessage;
}

/**
 * 清理提示，并把提示框位置设置成无效值
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param  int i：当前提示框的位置,横坐标[0-8]
 * @param  int j：当前提示框的位置,纵坐标[0-9]
 *
 * @returns An int. 0：成功；非零：失败
 */
int CChineseChess::CleanPrompt(int &i, int &j)
{
	if (-1 == i || -1 == j)
		return 0;
	int oI = i, oJ = j;
	i = -1;
	j = -1;
	onCleanPrompt(oI, oJ);
	return 0;
}

/*******************************************************************************************************
函数名：GoChess
功  能：走棋
参  数：
		 int i：棋盘格横坐标[0-8]
		 int j：棋盘格纵坐标[0-9]
		 bool bNext： TRUE：复盘；FALSE：正常下棋
		              区别是：正常下棋，保存着法到棋局中。
					          复盘则不保存
返回值：成功返回true，否则返回false。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j, bool bNext)
{
	if (IsGoChess(i, j))
	{ //走棋

		if (!bNext)
		{
			onGoChess(i, j, m_ChessBoard[i][j]);	   //事件
            int x, y;
            ConvertQiPang(i, j, x, y);
			m_Game.SaveStep(x, y, m_ChessBoard[i][j]); //保存到棋局中
		}
		
		// 显示提示框
		switch (m_WalkState)
		{
		case RedReadly:
			if (m_bPromptSound) onPromptSound(Select);

			CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;

			onDrawPrompt(i, j);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			if (m_bPromptSound) onPromptSound(Select);

			CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			onDrawPrompt(i, j);

			m_WalkState = BlackWalked;
			break;
		case BlackWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else //不能走
	{
		if (m_bPromptSound) onPromptSound();
		return false;
	}
}

/*******************************************************************************************************
函数名：IsGoChess
功  能：判断能否走棋
参  数：
		 int i：当前下棋的位置,横坐标[0-8]
		 int j：当前下棋的位置,纵坐标[0-9]
		 CPiece::ENUM_QiZi qz：当前棋子
返回值：如果可以下棋返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：10:47:40
*******************************************************************************************************/
bool CChineseChess::IsGoChess(int i, int j)
{
	if(!IsValidPosition(i, j))
	{   //出界
		return false;
	}

	switch (m_WalkState)
	{
	case RedReadly:
		return CPiece::IsRedQiZi(m_ChessBoard[i][j]) ? true : false;
	case RedWalked:
		//本方的棋,重新选取
		if (CPiece::IsRedQiZi(m_ChessBoard[i][j]))
		{
			m_Game.RevokeStep();
			m_WalkState = RedReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://将军
			if(m_bPromptSound) onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://可以走棋
			if (m_bPromptSound)
			{
				m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			}
			return true;
		case CGoRule::BEIJIANGJUN://被将
			if(m_bPromptMessage) onPromptMessage(CGoRule::BEIJIANGJUN);
			return false;
		case CGoRule::JIANGDUIMIAN://将对面
			if (m_bPromptMessage) onPromptMessage(CGoRule::JIANGDUIMIAN);
			return false;
		case CGoRule::RETURNFALSE://非法走棋
		default:
			return false;
		}

	case BlackReadly:
		return CPiece::IsBlackQiZi(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//本方的棋,重新选取
		if (CPiece::IsBlackQiZi(m_ChessBoard[i][j]))
		{
			m_Game.RevokeStep();
			m_WalkState = BlackReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://将军
			if (m_bPromptSound) onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://可以走棋
			if (m_bPromptSound)
			{
				m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			}
			return true;
		case CGoRule::BEIJIANGJUN://被将
			if (m_bPromptMessage) onPromptMessage(CGoRule::BEIJIANGJUN);
			return false;
		case CGoRule::JIANGDUIMIAN://将对面
			if (m_bPromptMessage) onPromptMessage(CGoRule::JIANGDUIMIAN);
			return false;
		case CGoRule::RETURNFALSE://非法走棋
		default:
			return false;
		}

	}

	return false;
}

/*******************************************************************************************************
函数名：NextStep
功  能：下步棋
参  数：无
返回值：走棋步数
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:19:33
*******************************************************************************************************/
int CChineseChess::NextStep()
{
	int i, j;
	CPiece::ENUM_QiZi qz;
	if (m_Game.GetNextStep(i, j, qz))
	{
		if (m_bPromptSound) onPromptSound();
		return -1;
	}
    int x, y;
    ConvertQiPang(i, j, x, y);
	if (GoChess(x, y, true))
		return 0;

	return -2;
}

/*******************************************************************************************************
函数名：PreviouStep
功  能：上步棋
参  数：无
返回值：走棋步数
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:19:51
*******************************************************************************************************/
int CChineseChess::PreviouStep()
{
	int i, j;
	CPiece::ENUM_QiZi qz;

	switch (m_WalkState)
	{
	case RedWalked:
	case BlackWalked:
		CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);
		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
		}
	case RedReadly:
	case BlackReadly:
		CleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
			return -1;
		}
        
        int x, y;
        ConvertQiPang(i, j, x, y);
		m_ChessBoard[x][y] = qz;
		m_CurrentPositionX = x;
		m_CurrentPositionY = y;
		CleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

		if (m_Game.GetPreviouStep(i, j, qz))
		{
			if (m_bPromptSound) onPromptSound();
			return -1;
		}
        ConvertQiPang(i, j, x, y);
		m_ChessBoard[x][y] = qz;
		m_PreviouPositionX = x;
		m_PreviouPositionY = y;

		if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);

		switch (m_WalkState)
		{
		case RedReadly:
		case RedWalked:
			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
		case BlackWalked:
			m_WalkState = RedReadly;
		}
		break;
	}

	return 0;
}

int CChineseChess::SaveChessGame(const char* pszFile)
{
	return m_Game.SaveChessGame(pszFile);
}

int CChineseChess::LoadChessGame(const char* pszFile)
{
	int nRet = 0;

	nRet = m_Game.LoadChessGame(pszFile);
	if (nRet) return nRet;

    SetBoardLayout(m_BoardLayout);
	return nRet;
}

int CChineseChess::SetRedName(const char* pszName)
{
	return m_Game.SetRedName(pszName);
}

std::string CChineseChess::GetRedName()
{
	return m_Game.GetRedName();
}

int CChineseChess::SetBlackName(const char* pszName)
{
	return m_Game.SetBlackName(pszName);
}

std::string CChineseChess::GetBlackName()
{
	return m_Game.GetBlackName();
}

int CChineseChess::SetStartTime(const time_t& tm)
{
	return m_Game.SetStartTime(tm);
}

time_t CChineseChess::GetStartTime()
{
	return m_Game.GetStartTime();
}

int CChineseChess::SetEndTime(const time_t& tm)
{
	return m_Game.SetEndTime(tm);
}

time_t CChineseChess::GetEndTime()
{
	return m_Game.GetEndTime();
}

int CChineseChess::SetGameTags(const char* pTags)
{
	return m_Game.SetTags(pTags);
}

std::string CChineseChess::GetGameTags()
{
	return m_Game.GetTags();
}

int CChineseChess::ConvertQiPang(const int &i, const int &j, int &x, int &y)
{
    if(m_BoardLayout & SwapRedBetweenBlack)
    {
        x = 8 - i; //9 - i - 1;
        y = 9 - j; //10 - j - 1;
        return 0;
    }
    x = i;
    y = j;
    return 0;   
}
