#include "ChessSteps.h"

CChessSteps::CChessSteps()
{
    m_nSteps = 0;
}

CChessSteps::~CChessSteps()
{}

std::string CChessSteps::toString()
{
    return m_szSteps;
}

int CChessSteps::AddStep(strStep step)
{
    m_Steps.push_back(step);
    return 0;
}

int CChessSteps::AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript)
{
    strStep step = {i, j, qz, szDescript};
    m_Steps.push_back(step);
    return 0;
}

CChessStepsIccs::CChessStepsIccs() : CChessSteps()
{}

CChessStepsIccs::~CChessStepsIccs()
{}

int CChessStepsIccs::AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript)
{
    char col = 'A' + i;
    std::string row = std::to_string(9 - j);
    switch (m_nSteps % 4) {
    case 0:
        m_szSteps += std::to_string(m_nSteps / 4 + 1) + ". ";
        m_szSteps += col + row;
        break;
    case 1:
        m_szSteps += "-";
        m_szSteps += col + row;
        if(!szDescript.empty())
        {
            m_szSteps += " {";
            m_szSteps += szDescript;
            m_szSteps += "}";
        }
        break;
    case 2:
        m_szSteps += " ";
        m_szSteps += col + row;
        break;
    case 3:
        m_szSteps += "-";
        m_szSteps += col + row;
        if(!szDescript.empty())
        {
            m_szSteps += " {";
            m_szSteps += szDescript;
            m_szSteps += "}";
        }
        m_szSteps += "\n";
        break;
    }
    m_nSteps++;
    return 0;
}

int CChessStepsIccs::GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript)
{
    return 0;
}
