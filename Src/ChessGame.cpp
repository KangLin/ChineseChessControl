#include "stdafx.h"
#include "ChessGame.h"

CChessGame::CChessGame()
{
	m_iBuShu = -1;
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
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		*Code = (*i + *j * 10 + *QZ * 100);
		return *Code;
		break;
	case JieMa:
		*QZ = (CPiece::ENUM_QiZi) (*Code / 100);
		TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
		int v;
		v = *Code % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
	}
	return 0;
}

int CChessGame::NextStep(int i, int j, CPiece::ENUM_QiZi qz)
{
	int code;
	QiZiBianMa(&i, &j, &qz, &code);
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
	return 0;
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
int CChessGame::PreviouStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
	if (m_iBuShu < 0)
		return -1;

	QiZiBianMa(&i, &j, &qz, &m_QiJu[m_iBuShu], JieMa);
	
	return 0;
}