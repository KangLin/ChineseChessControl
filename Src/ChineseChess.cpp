
#include "stdafx.h"
#include "ChineseChess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CChineseChess::CChineseChess()
{
	Initial();
}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	SetBoardLayout(TopBlackAndBottomRed);
	m_WalkState = RedReadly;
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;
	m_iBuShu = -1;
	m_bFuPang = false;
	return 0;
}

int CChineseChess::GetBoard(int &row, int &col)
{
	row = GetBoardRow();
	col = GetBoardColumn();
	return 0;
}
int CChineseChess::GetBoardRow()
{
	return m_BoardRow;
}

int CChineseChess::GetBoardColumn()
{
	return m_BoardColumn;
}

int CChineseChess::SetBoardLayout(ENUM_BoardLayout layout)
{
	m_BoardLayout = layout;

	//初始化空棋局
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			m_ChessBoard[i][j] = NoQiZi;

	
	if (m_BoardLayout & OnlyTopBlack)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = RChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = RMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = RXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = RShi;
			m_ChessBoard[4][0] = RShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = RPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = RBing;
		}
		else {
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = BChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = BMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = BXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = BShi;
			m_ChessBoard[4][0] = BShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = BPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = BBing;
		}
	}

	if (m_BoardLayout & OnlyBottomRed)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = BChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = BMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = BXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = BShi;
			m_ChessBoard[4][9] = BShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = BPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = BBing;
		}
		else {
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = RChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = RMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = RXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = RShi;
			m_ChessBoard[4][9] = RShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = RPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = RBing;
		}
	}


	return 0;
}

/*******************************************************************************************************
函数名：QiZiBianMa
功  能：棋子编解码
参  数：
		 int *i：棋盘横坐标[0-8]
		 int *j：棋盘纵坐标[0-9]
		 ENUM_QiZi *QZ：棋子
		 int *Code：棋子编码
		 ENUM_BianMa：枚举常量（BianMa:编码(默认值)，JieMa：解码）
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-2
时  间：7:36:32
*******************************************************************************************************/
int CChineseChess::QiZiBianMa(int *i, int *j, ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		int val;
		if (*QZ != NoQiZi)
		{
			val = sig(*QZ) * (*i + *j * 10 + abs(*QZ) * 100);
		}
		else
		{
			val = *i + *j * 10;
		}
		*Code = val;
		return val;
		break;
	case JieMa:
		*QZ = (ENUM_QiZi)(*Code / 100);
		//TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
		int v;
		v = abs(*Code) % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
		break;
	}
	return 0;
}

bool CChineseChess::IsValidPosition(int i, int j)
{
	if (i < 0 || i > m_BoardRow - 1 || j < 0 || j > m_BoardColumn - 1)
	{   //出界
		return false;
	}
	return true;
}

/*******************************************************************************************************
函数名：GoChess
功  能：走棋
参  数：
		 int i：棋盘格横坐标[0-8]
		 int j：棋盘格纵坐标[0-9]
返回值：成功返回true，否则返回false。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j)
{
	int code;
	if (IsGoChess(i, j))
	{ //走棋

		onGoChess(i, j, m_ChessBoard[i][j]); //事件

		QiZiBianMa(&i, &j, &m_ChessBoard[i][j], &code);
		m_iBuShu++;
		if (!m_bFuPang)
		{   //保存到棋局中
			if (m_iBuShu < m_QiJu.size())
			{
				m_QiJu[m_iBuShu] = code;
			}
			else//下棋
			{
				m_QiJu.push_back(code);//保存到棋局中
			}
		}

		// 显示提示框
		switch (m_WalkState)
		{
		case RedReadly:
			onPromptSound(Select);

			if(IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
				onCleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			if(IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
				onCleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			m_CurrentPositionX = -1;
			m_CurrentPositionY = -1;

			onDrawPrompt(i, j);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = NoQiZi;

			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);
			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			onPromptSound(Select);

			if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
				onCleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			if (IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
				onCleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			m_CurrentPositionX = -1;
			m_CurrentPositionY = -1;
			onDrawPrompt(i, j);

			m_WalkState = BlackWalked;
			break;
		case BlackWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = NoQiZi;

			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);
			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else//不能走
	{
		onPromptSound(NoGo);
		return false;
	}
}

/*******************************************************************************************************
函数名：IsGoChess
功  能：判断能否走棋
参  数：
		 int i：当前下棋的位置,横坐标[0-8]
		 int j：当前下棋的位置,纵坐标[0-9]
		 ENUM_QiZi qz：当前棋子
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
		return RQi == m_GoRule.GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
		break;
	case RedWalked:
		//本方的棋,重新选取
		if (m_GoRule.GetQiZiSide(m_ChessBoard[i][j]) == RQi)
		{
			m_iBuShu--;//重定义棋时存在上一位置
			m_WalkState = RedReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://将军
			onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://可以走棋
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case CGoRule::BEIJIANGJUN://被将
			onPromptMessage("这步棋不能走，否则你要输了。", "被将军");
			return false;
		case CGoRule::JIANGDUIMIAN://将对面
			onPromptMessage("这步棋不能走，否则你要输了。", "将对面");
			return false;
		case CGoRule::RETURNFALSE://非法走棋
			return false;
		}

		break;
	case BlackReadly:
		return BQi == m_GoRule.GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//本方的棋,重新选取
		if (m_GoRule.GetQiZiSide(m_ChessBoard[i][j]) == BQi)
		{
			m_iBuShu--;//重定义棋时存在上一位置
			m_WalkState = BlackReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://将军
			onPromptSound(JiangJun);
			return true;
			break;
		case CGoRule::RETURNTRUE://可以走棋
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case CGoRule::BEIJIANGJUN://被将
			onPromptMessage("这步棋不能走，否则你要输了。", "被将军");
			return false;
		case CGoRule::JIANGDUIMIAN://将对面
			onPromptMessage("这步棋不能走，否则你要输了。", "将对面");
			return false;
		case CGoRule::RETURNFALSE://非法走棋
			return false;
			break;
		}

		break;
	}

	return true;
}
