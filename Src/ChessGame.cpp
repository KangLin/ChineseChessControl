#include "stdafx.h"
#include "ChessGame.h"

CChessGame::CChessGame()
{
	m_nIndex = -1;
	m_bFuPang = false;
}

CChessGame::~CChessGame()
{}

/*******************************************************************************************************
函数名：QiZiBianMa
功  能：棋子编解码
参  数：
		 int *i：棋盘横坐标[0-8]
		 int *j：棋盘纵坐标[0-9]
		 CPiece::ENUM_QiZi *QZ：棋子
		 int *Code：棋子编码
		 ENUM_BianMa：枚举常量（BianMa:编码(默认值)，JieMa：解码）
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-2
时  间：7:36:32
*******************************************************************************************************/
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, INT32 *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		*Code = *i | (*j << 4) | (*QZ << 8);
		TRACE(_T("i:%d;j:%d:qz:%X:code:%X"), *i, *j, *QZ, *Code);
		return *Code;

	case JieMa:
		*QZ = (CPiece::ENUM_QiZi) ((*Code & 0x0F00) >> 8);
		TRACE(_T("i:%d;j:%d:qz:%X:code:%X"), *i, *j, *QZ, *Code);
		*i = *Code & 0x000F;
		*j = (*Code & 0x00F0) >> 4;
		return 0;
	}
	
	return 0;
}

/**
 * 保存一步
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param  int i：当前下棋的位置,横坐标[0-8]
 * @param  int j：当前下棋的位置,纵坐标[0-9]
 * @param  qz 棋子
 *
 * @returns 成功返回 0 ，否则返回非零
 */
int CChessGame::SaveStep(int i, int j, CPiece::ENUM_QiZi qz)
{
	int code;
	QiZiBianMa(&i, &j, &qz, &code);

	// 调整容器大小
	if (m_nIndex + 1 < m_ChessGame.size())
	{
		m_ChessGame.resize(m_nIndex + 1);
	}

	m_ChessGame.push_back(code);//保存到棋局中
	m_nIndex++;

	return 0;
}

/**
 * 撤回一步
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @returns 成功返回 0 ，否则返回非零
 */
int CChessGame::RevokeStep()
{
	if (m_nIndex < 0)
		return -1;
	m_nIndex--;
	m_ChessGame.erase(--m_ChessGame.end());
	return 0;
}

/*******************************************************************************************************
函数名：GetPreviouStep
功  能：上步棋
参  数：无
返回值：走棋步数
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:19:51
*******************************************************************************************************/
int CChessGame::GetPreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_nIndex < 0)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[m_nIndex], JieMa);
	m_nIndex--;
	return 0;
}

/**
 * Gets the next step
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 *
 * @param [in,out] i 
 * @param [in,out] j 
 * @param [in,out] qz 
 * @returns The next step.
 */
int CChessGame::GetNextStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_ChessGame.size() <= m_nIndex + 1)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[++m_nIndex], JieMa);

	return 0;
	
}