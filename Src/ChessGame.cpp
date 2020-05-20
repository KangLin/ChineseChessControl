
#include "ChessGame.h"
#include <fstream>

#if defined( _DEBUG) && defined(_MSC_VER)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

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
		 CPiece::ENUM_QiZi *qz：棋子
		 strCODE *pCode：棋子编码
		 ENUM_BianMa：枚举常量（BianMa:编码(默认值)，JieMa：解码）
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-2
时  间：7:36:32
*******************************************************************************************************/
int CChessGame::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *qz, strCODE *pCode, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		pCode->code[0] = *i;
		pCode->code[1] = *j;
		pCode->code[2] = *qz;
		break;
	case JieMa:
		*i = pCode->code[0];
		*j = pCode->code[1];
		*qz = static_cast<CPiece::ENUM_QiZi>(pCode->code[2]);
		break;
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
	strCODE code;
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
 * 撤销一步
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
 * @param  int i：当前下棋的位置,横坐标[0-8]
 * @param  int j：当前下棋的位置,纵坐标[0-9]
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

int CChessGame::SaveChessGame(const char* szFile, char layout)
{
	if (!szFile) return -1;
	strFile head;
	strcpy_s(head.head.szAppName, APPNAME);
	strcpy_s(head.head.szAuthor, AUTHOR);
	head.head.dwVersion = 1;
	head.iBuShu = m_ChessGame.size();
	head.boardLayout = layout;

	std::ofstream out(szFile);
	if (!out.is_open())
		return -2;
	out.write((char*)&head, sizeof(strFile));
	std::vector<strCODE>::iterator it;
	for (it = m_ChessGame.begin(); it != m_ChessGame.end(); it++)
	{
		out.write(it->code, sizeof(strCODE));
	}
	out.close();
	return 0;
}

int CChessGame::LoadChessGame(const char* szFile, char &layout)
{
	int nRet = 0;
	if (!szFile) return -1;

	strFile head;
	std::ifstream in(szFile);
	if (!in.is_open())
		return -2;

	in.read((char*)&head, sizeof(strFile));
	layout = head.boardLayout;
	do{
		if (strcmp(head.head.szAppName, APPNAME))
		{
			nRet = -3;
			break;
		}
		if (strcmp(head.head.szAuthor, AUTHOR))
		{
			nRet = -4;
			break;
		}

		m_ChessGame.clear();
		m_nIndex = head.iBuShu;

		while (m_nIndex--)
		{
			strCODE code;
			in.read((char*)&code, sizeof(strCODE));
			m_ChessGame.push_back(code);
		}
		m_nIndex = -1;
	} while (0);

	in.close();
	return nRet;;
}