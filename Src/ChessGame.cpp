
#include "ChessGame.h"
#include <fstream>
#include <time.h>
#include <string.h>

#ifdef WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
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
		 char *i：棋盘横坐标[0-8]
		 char *j：棋盘纵坐标[0-9]
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
 * @param char i：当前下棋的位置,横坐标[0-8]
 * @param char j：当前下棋的位置,纵坐标[0-9]
 * @param qz 棋子
 * @param const char* pDescript： 这一步的描述
 *
 * @returns 成功返回 0 ，否则返回非零
 */
int CChessGame::SaveStep(int i, int j, CPiece::ENUM_QiZi qz,
                         const char* pDescript, time_t tm)
{
	strStep step;
	QiZiBianMa(&i, &j, &qz, &step.code);
	if (pDescript)
		step.szDescript = pDescript;
    
    step.tm = tm;
    
	// 调整容器大小
	if (m_nIndex + 1 < m_ChessGame.size())
	{
		m_ChessGame.resize(m_nIndex + 1);
	}

	m_ChessGame.push_back(step);//保存到棋局中
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

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[m_nIndex].code, JieMa);
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

	QiZiBianMa(&i, &j, &qz, &m_ChessGame[++m_nIndex].code, JieMa);

	return 0;
}

int CChessGame::SaveChessGame(const char* szFile)
{
	if (!szFile) return -1;
	strFile head;
#ifdef WIN32
#ifdef MINGW
	strncpy_s(head.head.szAppName, MAX_STRING_BUFFER, APPNAME, MAX_STRING_BUFFER);
	strncpy_s(head.head.szAuthor, MAX_STRING_BUFFER, AUTHOR, MAX_STRING_BUFFER);
#else
	strncpy_s(head.head.szAppName, APPNAME, MAX_STRING_BUFFER);
	strncpy_s(head.head.szAuthor, AUTHOR, MAX_STRING_BUFFER);
#endif
#else
	strncpy(head.head.szAppName, APPNAME, MAX_STRING_BUFFER);
	strncpy(head.head.szAuthor, AUTHOR, MAX_STRING_BUFFER);
#endif

	head.head.dwVersion = 2;
	head.iBuShu = htons(m_ChessGame.size());

	head.timeStart = htonl(m_tmStart);
	head.timeEnd = htonl(m_tmEnd);
#ifdef WIN32
#ifdef MINGW
	strncpy_s(head.szRedName, MAX_STRING_BUFFER, m_szRedName.c_str(), MAX_STRING_BUFFER);
	strncpy_s(head.szBlackName, MAX_STRING_BUFFER, m_szBlackName.c_str(), MAX_STRING_BUFFER);
#else
	strncpy_s(head.szRedName, m_szRedName.c_str(), MAX_STRING_BUFFER);
	strncpy_s(head.szBlackName, m_szBlackName.c_str(), MAX_STRING_BUFFER);
#endif
#else
	strncpy(head.szRedName, m_szRedName.c_str(), MAX_STRING_BUFFER);
	strncpy(head.szBlackName, m_szBlackName.c_str(), MAX_STRING_BUFFER);
#endif

	std::ofstream out(szFile);
	if (!out.is_open())
		return -2;
	out.write((char*)&head, sizeof(strFile));
	WriteStringToFile(out, m_szTags);
	std::vector<strStep>::iterator it;
	for (it = m_ChessGame.begin(); it != m_ChessGame.end(); it++)
	{
		out.write(it->code.code, sizeof(strCODE));
        long t = htonl(it->tm);
        out.write((char*)&t, sizeof(long));
		WriteStringToFile(out, it->szDescript);
	}
	out.close();
	return 0;
}

int CChessGame::LoadChessGame(const char* szFile)
{
	int nRet = 0;
	if (!szFile) return -1;

	strFile head;
	memset(&head, 0, sizeof(strFile));

	std::ifstream in(szFile);
	if (!in.is_open())
		return -2;

	in.read((char*)&head, sizeof(strFile));
	m_szRedName = head.szRedName;
	m_szBlackName = head.szBlackName;
	m_tmStart = ntohl(head.timeStart);
	m_tmEnd = ntohl(head.timeEnd);

	do {
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
		if (head.head.dwVersion > 2)
		{
			nRet = -5;
			break;
		}

		ReadStringFromFile(in, m_szTags);

		m_ChessGame.clear();
		m_nIndex = ntohs(head.iBuShu);

		while (m_nIndex--)
		{
			strStep step;
			in.read((char*)&step.code, sizeof(strCODE));
            long tm;
            in.read((char*)&tm, sizeof(long));
            step.tm = ntohl(tm);
			ReadStringFromFile(in, step.szDescript);
			m_ChessGame.push_back(step);
		}
		m_nIndex = -1;
	} while (0);

	in.close();
	return nRet;;
}

int CChessGame::WriteStringToFile(std::ofstream &o, std::string &s)
{
	short nLen = s.size();
	short n = htons(nLen);
	o.write((char*)&n, sizeof(short));
	if (nLen > 0)
	{
		o.write(s.c_str(), nLen);
	}
	return 0;
}

int CChessGame::ReadStringFromFile(std::ifstream &i, std::string &s)
{
	short nLen = 0;
	i.read((char*)&nLen, sizeof(short));
	nLen = ntohs(nLen);
	if (nLen > 0)
	{
		char* pBuf = new char[nLen + 1];
		memset(pBuf, 0, nLen + 1);
		i.read(pBuf, nLen);
		s = pBuf;
		delete[]pBuf;
	}
	return 0;
}

time_t CChessGame::GetStartTime()
{
	return m_tmStart;
}

int CChessGame::SetStartTime(const time_t& t)
{
	m_tmStart = t;
	return 0;
}

time_t CChessGame::GetEndTime()
{
	return m_tmEnd;
}

int CChessGame::SetEndTime(const time_t& t)
{
	m_tmEnd = t;
	return 0;
}

std::string CChessGame::GetRedName()
{
	return m_szRedName;
}

int CChessGame::SetRedName(const char* pszName)
{
	m_szRedName = pszName;
	return 0;
}

std::string CChessGame::GetBlackName()
{
	return m_szBlackName;
}

int CChessGame::SetBlackName(const char* pszName)
{
	m_szBlackName = pszName;
	return 0;
}

std::string CChessGame::GetTags()
{
	return m_szTags;
}

int CChessGame::SetTags(const char* pTags)
{
	m_szTags = pTags;
	return 0;
}
