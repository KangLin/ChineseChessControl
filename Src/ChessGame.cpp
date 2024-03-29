﻿// 作者：康林 <kl222@126.com>

#include "ChessGame.h"
#include <fstream>
#include <time.h>
#include <string.h>
#include <memory>
#include "Pgn.h"
#include "Fen.h"

#ifdef WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

#include "Pgn.h"

CChessGame::CChessGame()
{
	m_nIndex = -1;
	m_bFuPang = false;
    /*
    m_StartGame.push_back({0, 0, CPiece::BChe});
    m_StartGame.push_back({1, 0, CPiece::BMa});
    m_StartGame.push_back({2, 0, CPiece::BXiang});
    m_StartGame.push_back({3, 0, CPiece::BShi});
    m_StartGame.push_back({4, 0, CPiece::BShuai});
    m_StartGame.push_back({5, 0, CPiece::BShi});
    m_StartGame.push_back({6, 0, CPiece::BXiang});
    m_StartGame.push_back({7, 0, CPiece::BMa});
    m_StartGame.push_back({8, 0, CPiece::BChe});

    m_StartGame.push_back({1, 2, CPiece::BPao});
    m_StartGame.push_back({7, 2, CPiece::BPao});

    m_StartGame.push_back({0, 3, CPiece::BBing});
    m_StartGame.push_back({2, 3, CPiece::BBing});
    m_StartGame.push_back({4, 3, CPiece::BBing});
    m_StartGame.push_back({6, 3, CPiece::BBing});
    m_StartGame.push_back({8, 3, CPiece::BBing});

    m_StartGame.push_back({0, 9, CPiece::RChe});
    m_StartGame.push_back({1, 9, CPiece::RMa});
    m_StartGame.push_back({2, 9, CPiece::RXiang});
    m_StartGame.push_back({3, 9, CPiece::RShi});
    m_StartGame.push_back({4, 9, CPiece::RShuai});
    m_StartGame.push_back({5, 9, CPiece::RShi});
    m_StartGame.push_back({6, 9, CPiece::RXiang});
    m_StartGame.push_back({7, 9, CPiece::RMa});
    m_StartGame.push_back({8, 9, CPiece::RChe});

    m_StartGame.push_back({1, 7, CPiece::RPao});
    m_StartGame.push_back({7, 7, CPiece::RPao});

    m_StartGame.push_back({0, 6, CPiece::RBing});
    m_StartGame.push_back({2, 6, CPiece::RBing});
    m_StartGame.push_back({4, 6, CPiece::RBing});
    m_StartGame.push_back({6, 6, CPiece::RBing});
    m_StartGame.push_back({8, 6, CPiece::RBing});
    //*/
    
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
		pCode->step[0] = *i;
		pCode->step[1] = *j;
		pCode->step[2] = *qz;
		break;
	case JieMa:
		*i = pCode->step[0];
		*j = pCode->step[1];
		*qz = static_cast<CPiece::ENUM_QiZi>(pCode->step[2]);
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
 * @param qz: 棋子
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
	
    // 保存标签
    short nTag = htons(m_Tags.size());
    out.write((char*)&nTag, sizeof (short));
    for(const auto& item: m_Tags)
    {
        std::string key = item.first;
        std::string val = item.second;
        WriteStringToFile(out, key);
        WriteStringToFile(out, val);
    }    
    
    //保存开局
    char nLen = 0; //开局最多30子
    nLen = m_StartGame.size();
    out.write(&nLen, sizeof (char));
    if(nLen > 0)
    {
        std::vector<strStartGame>::iterator it;
        for(it = m_StartGame.begin(); it != m_StartGame.end(); it++)
        {
            strCODE code;
            QiZiBianMa(&it->i, &it->j, &it->qz, &code);
            out.write(code.step, sizeof(strCODE));
        }
    }

    //保存着法
    std::vector<strStep>::iterator it;
	for (it = m_ChessGame.begin(); it != m_ChessGame.end(); it++)
	{
		out.write(it->code.step, sizeof(strCODE));
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
		if (head.head.dwVersion != 2)
		{
			nRet = -5;
			break;
		}

        //加载标签
        short nTags = 0;
        in.read((char*)&nTags, sizeof (short));
        nTags = ntohs(nTags);
        if(nTags) m_Tags.clear();
        while(nTags-- > 0)
        {
            std::string key, val;
            ReadStringFromFile(in, key);
            ReadStringFromFile(in, val);
            m_Tags[key] = val;
        }
        
        //加载开局
        m_StartGame.clear();
        char nLen = 0;
        in.read(&nLen, sizeof (char));
        if(nLen > 0)
        {
            while (nLen--) {
                strCODE code;
                in.read(code.step, sizeof(strCODE));
                strStartGame g;
                QiZiBianMa(&g.i, &g.j, &g.qz, &code, JieMa);
                m_StartGame.push_back(g);
            }
        }

        //加载着法
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
	return nRet;
}

int CChessGame::SaveChessGamePgn(const char *pFileName, _SavePgnFormat f)
{
    int nRet = 0;
	if (!pFileName) return -1;
    
    CPGN pgn;
    std::shared_ptr<CChessSteps> Steps;
    
    //设置 Tag
    if(!m_szRedName.empty())
        pgn.SetRed(m_szRedName.c_str());
    if(!m_szBlackName.empty())
        pgn.SetBlack(m_szBlackName.c_str());

    CPiece::ENUM_QiZi board[9][10];
    if(m_StartGame.empty())
    {
        GetStartGameBoard(board);
    }
    
    std::string szFen;
    CFen fen;
    nRet = fen.FenFromBoard(szFen, board);
    if(0 == nRet)
        pgn.SetFen(szFen.c_str());

    for(const auto& item: m_Tags)
    {
        std::string key = item.first;
        std::string val = item.second;
        pgn.SetTag(key, val);
    }

    switch (f) {
    case ICCS:
        pgn.SetFormat("ICCS");
        Steps = std::shared_ptr<CChessStepsIccs>(new CChessStepsIccs());
        break;
    case WXF:
        pgn.SetFormat("WXF");
        break;
    case Chinese:
        pgn.SetFormat("Chinese");
        Steps = std::shared_ptr<CChessStepsChinese>(new CChessStepsChinese());
        break;
    }

    GetStartGameBoard(Steps->m_Board);
    for(auto& item: m_ChessGame)
    {
        int i = 0, j = 0;
        CPiece::ENUM_QiZi qz = CPiece::NoQiZi;
        QiZiBianMa(&i, &j, &qz, &item.code, JieMa);
        Steps->AddStep(i, j, qz, item.szDescript);
    }
    
    std::ofstream out(pFileName);
	if (!out.is_open())
		return -2;
    pgn.SetSteps(Steps);
    out << pgn.toString();
    out.close();
    
    return nRet;
}

int CChessGame::LoadChessGamePgn(const char *pFileName, _SavePgnFormat f)
{
    int nRet = 0;
	if (!pFileName) return -1;
    
    //TODO:
    std::ifstream in(pFileName);
	if (!in.is_open())
		return -2;
    
    
    in.close();
    return nRet;
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

std::string CChessGame::GetTag(const std::string &szpTag)
{
    std::map<std::string, std::string>::iterator it;
    it = m_Tags.find(szpTag);
    if(m_Tags.end() != it)
        return it->second;
    return std::string();
}

int CChessGame::AddTag(const std::string &szTag, const std::string &szVal)
{
    m_Tags[szTag] = szVal;
    return 0;
}

//检测布局是否合法, 使用标准棋盘布局，红下黑上
int CChessGame::CheckGame(const CPiece::ENUM_QiZi board[][10])
{
    int nRet = 0;
    
    int nRChe = 0;
    int nRMa = 0;
    int nRXiang = 0;
    int nRShi = 0;
    int nRShuai = 0;
    int nRPao = 0;
    int nRBing = 0;
    
    int nBChe = 0;
    int nBMa = 0;
    int nBXiang = 0;
    int nBShi = 0;
    int nBShuai = 0;
    int nBPao = 0;
    int nBBing = 0;
    
    //检查各种棋子个数
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 10; j++)
        {
            switch(board[i][j])
            {
            case CPiece::RChe:
                nRChe++;
                break;
            case CPiece::RMa:
                nRMa++;
                break;
            case CPiece::RXiang:
                nRXiang++;
                if(!((2 == i && 9 == j) || (6 == i && 9 == j)
                     || (0 == i && 7 == j) || (8 == i && 7 == j)
                     || (2 == i && 5 == j) || (6 == i && 5 == j)
                     ))
                    return -1;
                break;
            case CPiece::RShi:
                nRShi++;
                if(i < 3 || i > 5 || j < 7)
                    return -2;
                if((i == 3 ||  5 == i) && j == 8)
                    return -3;
                if(i == 4 && (j == 9 || j == 7))
                    return -4;
                break;
            case CPiece::RShuai:
                nRShuai++;
                if(i < 3 || i > 5 || j < 7)
                    return -5;
                break;
            case CPiece::RPao:
                nRPao++;
                break;
            case CPiece::RBing:
                nRBing++;
                if(j > 6) return -6;
                break;
            case CPiece::BBing:
                nBBing++;
                if(j < 3) return -7;                
                break;
            case CPiece::BPao:
                nBPao++;
                break;
            case CPiece::BChe:
                nBChe++;
                break;
            case CPiece::BMa:
                nBMa++;
                break;
            case CPiece::BXiang:
                nBXiang++;
                if(!((2 == i && 0 == j) || (6 == i && 0 == j)
                     || (0 == i && 2 == j) || (8 == i && 2 == j)
                     || (2 == i && 4 == j) || (6 == i && 4 == j)
                     ))
                    return -8;
                break;
            case CPiece::BShi:
                nBShi++;
                if(i < 3 || i > 5 || j > 2)
                    return -9;
                if((i == 3 ||  5 == i) && j == 1)
                    return -10;
                if(i == 4 && (j == 0 || j == 2))
                    return -11;
                break;
            case CPiece::BShuai:
                nBShuai++;
                if(i < 3 || i > 5 || j > 2)
                    return -12;
                break;
            default:
                break;
            }
        }
    if(nBChe > 2 || nRChe > 2
            || nBMa > 2 || nRMa > 2
            || nBXiang > 2 || nRXiang > 2
            || nBShi > 2 || nBShi > 2
            || nBShuai > 1 || nRShuai > 1
            || nBPao > 2 || nRPao > 2
            || nBBing > 5 || nRBing > 5)
        return -13;
    
    return nRet;
}

int CChessGame::GetStartGameBoard(/*[out]*/CPiece::ENUM_QiZi board[][10])
{
	//初始化空棋局
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
        {
            board[i][j] = CPiece::NoQiZi;
        }

    if(m_StartGame.size())
    {
        std::vector<CChessGame::strStartGame>::iterator it;
        for(it = m_StartGame.begin(); it != m_StartGame.end(); it++)
        {
            board[it->i][it->j] = it->qz;
        }
        return CheckGame(board);
    }
    else
    {
        board[0][0] = board[8][0] = CPiece::BChe;
        board[1][0] = board[7][0] = CPiece::BMa;
        board[2][0] = board[6][0] = CPiece::BXiang;
        board[3][0] = board[5][0] = CPiece::BShi;
        board[4][0] = CPiece::BShuai;
        board[1][2] = board[7][2] = CPiece::BPao;
        board[0][3] = board[2][3] = board[4][3] = board[6][3] = board[8][3] = CPiece::BBing;
        
        board[0][9] = board[8][9] = CPiece::RChe;
        board[1][9] = board[7][9] = CPiece::RMa;
        board[2][9] = board[6][9] = CPiece::RXiang;
        board[3][9] = board[5][9] = CPiece::RShi;
        board[4][9] = CPiece::RShuai;
        board[1][7] = board[7][7] = CPiece::RPao;
        board[0][6] = board[2][6] = board[4][6] = board[6][6] = board[8][6] = CPiece::RBing;
    }
    return 0;
}
