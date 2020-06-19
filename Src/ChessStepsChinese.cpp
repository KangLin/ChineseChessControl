#include "ChessStepsChinese.h"

CChessStepsChinese::CChessStepsChinese() : CChessSteps()
{
    m_Ping = "平";
    m_Jin = "进";
    m_Tui = "退";
    m_Qian = "前";
    m_Zhong = "中";
    m_Hou = "后";
}

CChessStepsChinese::~CChessStepsChinese()
{}

//详见《象棋竞赛规则(2011)》第二章 第7条
std::string CChessStepsChinese::toString()
{
    std::string szRet;
    m_nSteps = 0;
    
    while (m_nSteps < m_Steps.size()) {
        strStep curStep = m_Steps[m_nSteps];
        switch (m_nSteps % 4) {
        case 0:
            szRet += std::to_string(m_nSteps / 4 + 1) + ". ";
            break;
        case 1:
        {
            strStep fromStep = m_Steps[m_nSteps - 1];
            szRet += StepToString(curStep, fromStep);
            if(!curStep.szDescript.empty())
            {
                szRet += " {";
                szRet += curStep.szDescript;
                szRet += "}";
            }
            
            m_Board[fromStep.i][fromStep.j] = CPiece::NoQiZi;
            m_Board[curStep.i][curStep.j] = fromStep.qz;
        }
            break;
        case 2:
            szRet += " ";
            break;
        case 3:
        {
            strStep fromStep = m_Steps[m_nSteps - 1];
            szRet += StepToString(curStep, fromStep);
            if(!curStep.szDescript.empty())
            {
                szRet += " {";
                szRet += curStep.szDescript;
                szRet += "}";
            }
            szRet += "\n";
            
            m_Board[fromStep.i][fromStep.j] = CPiece::NoQiZi;
            m_Board[curStep.i][curStep.j] = fromStep.qz;
        }
            break;
        
        }
        m_nSteps++;
    }
    
    return szRet;
}

int CChessStepsChinese::GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript)
{
    return 0;
}

std::string CChessStepsChinese::GetQiZi(CPiece::ENUM_QiZi qz)
{
    switch (qz) {
    case CPiece::RShuai:
        return "帅";
    case CPiece::RShi:
        return "仕";
    case CPiece::RXiang:
        return "相";
    case CPiece::RMa:
    case CPiece::BMa:
        return "马";
    case CPiece::RChe:
    case CPiece::BChe:
        return "车";
    case CPiece::RPao:
    case CPiece::BPao:
        return "炮";
    case CPiece::RBing:
        return "兵";
    case CPiece::BShuai:
        return "将";
    case CPiece::BShi:
        return "士";
    case CPiece::BXiang:
        return "象";
    case CPiece::BBing:
        return "卒";
    }
    return "";
}

std::string CChessStepsChinese::StepToString(strStep to, strStep from)
{
    std::string szRet;

    CPiece::ENUM_QiZi qz = from.qz;
    switch (qz) {
    case CPiece::RShuai:
        szRet = GetQiZi(qz) + ChineseNumber[9 - from.i];
        if(from.j == to.j)
            szRet += m_Ping + ChineseNumber[9 - to.i];
        else
        {
            if(from.j < to.j)
                szRet += m_Tui;
            else 
                szRet += m_Jin;
            szRet += ChineseNumber[1];
        }
        break;
    case CPiece::BShuai:
        szRet = GetQiZi(qz) + std::to_string(from.i + 1);
        if(from.j == to.j)
            szRet += m_Ping + std::to_string(to.i + 1);
        else 
        {
            if(from.j > to.j)
                szRet += m_Tui;
            else 
                szRet += m_Jin;
            szRet += "1";
        }
        break;
    case CPiece::RShi:
    case CPiece::RXiang:
        szRet = GetQiZi(qz) + ChineseNumber[9 - from.i];
        if(from.j < to.j)
            szRet += m_Tui;
        else 
            szRet += m_Jin;
        szRet += ChineseNumber[9 - to.i];
        break;
    case CPiece::BShi:
    case CPiece::BXiang:
        szRet = GetQiZi(qz) + std::to_string(from.i + 1);
        if(from.j > to.j)
            szRet += m_Tui;
        else 
            szRet += m_Jin;
        szRet += std::to_string(to.i + 1);
        break;
    
    case CPiece::RMa:
    {
        int nRet = FindSameQiZi(from);
        if(0 == nRet)
        {
            szRet = GetQiZi(qz) + ChineseNumber[9 - from.i];
        } else if(nRet > 0)
        {
            szRet = m_Qian + GetQiZi(qz);
        } else if(nRet < 0)
        {
            szRet = m_Hou + GetQiZi(qz);
        }
        if(from.j < to.j)
            szRet += m_Tui;
        else 
            szRet += m_Jin;
        szRet += ChineseNumber[9 - to.i];
        break;
    }
    case CPiece::BMa:
    {
        int nRet = FindSameQiZi(from);
        if(0 == nRet)
        {
            szRet = GetQiZi(qz) + std::to_string(from.i + 1);
        } else if(nRet > 0)
        {
            szRet = m_Qian + GetQiZi(qz);
        } else if(nRet < 0)
        {
            szRet = m_Hou + GetQiZi(qz);
        }
        if(from.j > to.j)
            szRet += m_Tui;
        else 
            szRet += m_Jin;
        szRet += std::to_string(to.i + 1);
        break;
    }
    case CPiece::RChe:
    case CPiece::RPao:
    {
        int nRet = FindSameQiZi(from);
        if(0 == nRet)
        {
            szRet = GetQiZi(qz) + ChineseNumber[9 - from.i];
        } else if(nRet > 0)
        {
            szRet = m_Qian + GetQiZi(qz);           
        } else if(nRet < 0)
        {
            szRet = m_Hou + GetQiZi(qz);
        }
        if(from.j == to.j)
            szRet += m_Ping + ChineseNumber[9 - to.i];
        else
        {
            if(from.j < to.j)
                szRet += m_Tui;
            else 
                szRet += m_Jin;
            szRet += ChineseNumber[std::abs(to.j - from.j)];
        }
        break;
    }
    case CPiece::BChe:
    case CPiece::BPao:
    {
        int nRet = FindSameQiZi(from);
        if(0 == nRet)
        {
            szRet = GetQiZi(qz) + std::to_string(from.i + 1);
        } else if(nRet > 0)
        {
            szRet = m_Qian + GetQiZi(qz);
        } else if(nRet < 0)
        {
            szRet = m_Hou + GetQiZi(qz);
        }
        if(from.j == to.j)
            szRet += m_Ping + std::to_string(to.i + 1);
        else
        {
            if(from.j < to.j)
                szRet += m_Jin;
            else 
                szRet += m_Tui;
            szRet += std::to_string(std::abs(to.j - from.j));
        }
        break;
    }
    case CPiece::RBing:
    {
        szRet = FindSameColumBing(from);
        if(szRet.empty())
        {
            szRet = GetQiZi(qz) + ChineseNumber[9 - from.i];
            
        } else {
            szRet += GetQiZi(qz);
        }
        
        if(from.j == to.j)
            szRet += m_Ping + ChineseNumber[9 - to.i];
        else
            szRet += m_Jin + ChineseNumber[std::abs(to.j - from.j)];
    }
        break;
    case CPiece::BBing:
    {
        szRet = FindSameColumBing(from);
        if(szRet.empty())
            szRet = GetQiZi(qz) + std::to_string(from.i + 1);
        else 
            szRet += GetQiZi(qz);
        
        if(from.j == to.j)
            szRet += m_Ping + std::to_string(to.i + 1);
        else
            szRet += m_Jin + std::to_string(std::abs(to.j - from.j));
    }
        break;
    }
    return  szRet;
}

/**
 * @brief 查找同列是否有相同的棋子
 * @param qz
 * @return： 0，没有；>0,前面有；<0后面有
 */
int CChessStepsChinese::FindSameQiZi(strStep step)
{
    int nRet = 0;
    for(int j = 0; j < 10; j++)
    {
        if(j == step.j) continue;
        
        if(step.qz == m_Board[step.i][j])
        {
            if(CPiece::IsRedQiZi(step.qz))
            {
                if(j < step.j)
                    nRet--;
                else
                    nRet++;
                break;
            }
            else
            {
                if(j > step.j)
                    nRet--;
                else
                    nRet++;
                break;
            }
        }
    }
    return nRet;
}

/*
 * 兵要按情况讨论：
 * (1) 三个兵在一条纵线上：用“前”、“中”和“后”来区别；
 * (2) 三个以上兵在一条纵线上：最前面的兵用“一”代替“前”，以后依次是“二”、“三”、“四”和“五”；
 * (3) 在有两条纵线，每条纵线上都有一个以上的兵：按照“先从左到右，再从前到后”(即先看最左边一列，
 *     从前到后依次标记为“一”和“二”，可能还有“三”，再看右边一列)的顺序，
 *     把这些兵的位置标依次标记为“一”、“二”、“三”、“四”和“五”，不在这两条纵线上的兵不参与标记。
 */
std::string CChessStepsChinese::FindSameColumBing(strStep step)
{
    std::string szRet;
    int nRet = FindSameQiZi(step);
    if(0 == nRet)
        return szRet;
    
    if(CPiece::IsRedQiZi(step.qz))
    {
        //判断第（3）种情况
        int nTotal = 0;
        int nFirstCol = -1;
        int nTowCol = -1;
        for(int i = 0; i < 9; i++)
        {
            int nNum = 0;
            for(int j = 0; j < 10; j++)
            {
                if(m_Board[i][j] == step.qz)
                    nNum++;
            }
            
            if(nNum > 1)
            {
                if(-1 == nFirstCol)
                {
                    nTotal = nNum;
                    nFirstCol = i;
                }
                else
                    nTowCol = i;
            }
        }

        //第(1)，(2)种情况
        if(-1 == nTowCol)
        {
            int nNum = 0;
            for(int j = 0; j < 10; j++)
            {
                if(m_Board[step.i][j] == step.qz)
                    nNum++;
            }
            
            int curNum = 0;
            for(int j = 0; j < 10; j++)
            {
                if(m_Board[step.i][j] == step.qz)
                    curNum++;
                if(j == step.j)
                    break;
            }
            
            switch (nNum) {
            case 2:
                if(1 == curNum)
                    return m_Qian;
                else
                    return m_Hou;
            case 3:
                switch(curNum){
                case 1:
                    return m_Qian;
                case 2:
                    return m_Zhong;
                case 3:
                    return m_Hou;
                }
                break;
            case 4:
            case 5:
                return ChineseNumber[curNum];
            }
        } 
        //第（3）种情况
        int curNum = 0;
        for(int j = 0; j < 10; j++)
        {
            if(m_Board[step.i][j] == step.qz)
                curNum++;
            if(j == step.j)
                break;
        }
        if(nFirstCol == step.i)
            return ChineseNumber[curNum];
        return ChineseNumber[curNum + nTotal];
    
    } else {
        //判断第（3）种情况
        int nTotal = 0;
        int nFirstCol = -1;
        int nTowCol = -1;
        for(int i = 8; i >=0 ; i--)
        {
            int nNum = 0;
            for(int j = 9; j >= 0; j--)
            {
                if(m_Board[i][j] == step.qz)
                    nNum++;
            }
            
            if(nNum >= 2)
            {
                if(-1 == nFirstCol)
                {
                    nFirstCol = i;
                    nTotal = nNum;
                }
                else
                    nTowCol += i;
            }
            
        }
        //第(1)，(2)种情况
        if(-1 == nTowCol)
        {
            int nNum = 0;
            for(int j = 9; j >= 0; j--)
            {
                if(m_Board[step.i][j] == step.qz)
                    nNum++;
            }
            
            int curNum = 0;
            for(int j = 9; j >= 0; j--)
            {
                if(m_Board[step.i][j] == step.qz)
                    curNum++;
                if(j == step.j)
                    break;
            }
            
            switch (nNum) {
            case 2:
                if(1 == curNum)
                    return m_Qian;
                else
                    return m_Hou;
            case 3:
                switch(curNum){
                case 1:
                    return m_Qian;
                case 2:
                    return m_Zhong;
                case 3:
                    return m_Hou;
                }
                break;
            case 4:
            case 5:
                return ChineseNumber[curNum];
            }
        } 
        //第（3）种情况
        int curNum = 0;
        for(int j = 9; j >= 0; j--)
        {
            if(m_Board[step.i][j] == step.qz)
                curNum++;
            if(j == step.j)
                break;
        }
        if(nFirstCol == step.i)
            return ChineseNumber[curNum];
        return ChineseNumber[curNum + nTotal];
    }
}
