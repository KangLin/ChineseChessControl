#include "ChineseChess.h"

CChineseChess::CChineseChess()
{}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;

	//------------------------------------------------------------------------
    //以下是完成 ===初始化开始棋局=== 功能的语句块
    //

    //初始化空棋局
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			m_ChessBoard[i][j] = NoQiZi;

	//设置棋盘布局,红上黑下
	if (m_BoardLayout & OnlyTopBlack)
	{
		m_ChessBoard[0][0] = m_ChessBoard[8][0] = BChe;
		m_ChessBoard[1][0] = m_ChessBoard[7][0] = BMa;
		m_ChessBoard[2][0] = m_ChessBoard[6][0] = BXiang;
		m_ChessBoard[3][0] = m_ChessBoard[5][0] = BShi;
		m_ChessBoard[4][0] = BShuai;
		m_ChessBoard[1][2] = m_ChessBoard[7][2] = BPao;
		m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = BBing;
	}

	if (m_BoardLayout & OnlyBottomRed)
	{
		m_ChessBoard[0][9] = m_ChessBoard[8][9] = RChe;
		m_ChessBoard[1][9] = m_ChessBoard[7][9] = RMa;
		m_ChessBoard[2][9] = m_ChessBoard[6][9] = RXiang;
		m_ChessBoard[3][9] = m_ChessBoard[5][9] = RShi;
		m_ChessBoard[4][9] = RShuai;
		m_ChessBoard[1][7] = m_ChessBoard[7][7] = RPao;
		m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = RBing;
	}

	//
	//以上是完成 ===初始化开始棋局=== 功能的语句块
	//------------------------------------------------------------------------

}

int CChineseChess::GetBoardRown()
{
	return m_BoardRow;
}

int CChineseChess::GetBoardColumn()
{
	return m_BoardColumn;
}

/*******************************************************************************************************
函数名：GetQiZiSide
功  能：得到棋子是红棋,还是黑棋
参  数：
		 ENUM_QiZi qz：要专断的棋子
返回值：返回红棋还是黑棋或无棋
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：12:10:36
*******************************************************************************************************/
ENUM_QiZi GetQiZiSide(ENUM_QiZi qz)
{
	if (qz > NoQiZi)
		return RQi;
	if (qz < NoQiZi)
		return BQi;
	return NoQiZi;
}

/*******************************************************************************************************
函数名：GoChess
功  能：走棋
参  数：
		 int i：棋盘格横坐标[0-8]
		 int j：棋盘格纵坐标[0-9]
		 bool bEnvet：是否激活事件。默认为TRUE。
返回值：成功返回true，否则返回false。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j, bool bEnvet)
{
	return false;
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
	if (i < 0 || i > m_BoardRow - 1 || j < 0 || j > m_BoardColumn - 1)
	{   //出界
		return false;
	}

	switch (m_WalkState)
	{
	case RedReadly:
		return RQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
		break;
	case RedWalked:
		//本方的棋,重新选取
		if (GetQiZiSide(m_ChessBoard[i][j]) == RQi)
		{
			m_iBuShu--;//重定义棋时存在上一位置
			m_WalkState = RedReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case JIANGJUN://将军
			onPromptSound(JiangJun);
			return true;
		case RETURNTRUE://可以走棋
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case BEIJIANGJUN://被将
			onPromptMessage("这步棋不能走，否则你要输了。", "被将军");
			return false;
		case JIANGDUIMIAN://将对面
			onPromptMessage("这步棋不能走，否则你要输了。", "将对面");
			return false;
		case RETURNFALSE://非法走棋
			return false;
		}

		break;
	case BlackReadly:
		return BQi == GetQiZiSide(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//本方的棋,重新选取
		if (GetQiZiSide(m_ChessBoard[i][j]) == BQi)
		{
			m_iBuShu--;//重定义棋时存在上一位置
			m_WalkState = BlackReadly;
			return true;
		}
		//判断能否走棋
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case JIANGJUN://将军
			onPromptSound(JiangJun);
			return true;
			break;
		case RETURNTRUE://可以走棋
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case BEIJIANGJUN://被将
			onPromptMessage("这步棋不能走，否则你要输了。", "被将军");
			return false;
		case JIANGDUIMIAN://将对面
			onPromptMessage("这步棋不能走，否则你要输了。", "将对面");
			return false;
		case RETURNFALSE://非法走棋
			return false;
			break;
		}

		break;
	}

	return true;
}
