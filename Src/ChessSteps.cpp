#include "ChessSteps.h"

CChessSteps::CChessSteps()
{
    m_nStep = 0;
}

CChessSteps::~CChessSteps()
{}

std::string CChessSteps::toString()
{
    return m_Steps;
}

CChessStepsChinese::CChessStepsChinese() : CChessSteps()
{}

CChessStepsChinese::~CChessStepsChinese()
{}

int CChessStepsChinese::AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript)
{
    char col = 'A' + i;
    std::string row = std::to_string(9 - j);
    switch (m_nStep % 4) {
    case 0:
        m_Steps += std::to_string(m_nStep / 4 + 1) + ". ";
        m_Steps += col + row;
        break;
    case 1:
        m_Steps += "-";
        m_Steps += col + row;
        if(!szDescript.empty())
        {
            m_Steps += " {";
            m_Steps += szDescript;
            m_Steps += "}";
        }
        break;
    case 2:
        m_Steps += " ";
        m_Steps += col + row;
        break;
    case 3:
        m_Steps += "-";
        m_Steps += col + row;
        if(!szDescript.empty())
        {
            m_Steps += " {";
            m_Steps += szDescript;
            m_Steps += "}";
        }
        m_Steps += "\n";
        break;
    }
    m_nStep++;
    return 0;
}

int CChessStepsChinese::GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript)
{
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
    switch (m_nStep % 4) {
    case 0:
        m_Steps += std::to_string(m_nStep / 4 + 1) + ". ";
        m_Steps += col + row;
        break;
    case 1:
        m_Steps += "-";
        m_Steps += col + row;
        if(!szDescript.empty())
        {
            m_Steps += " {";
            m_Steps += szDescript;
            m_Steps += "}";
        }
        break;
    case 2:
        m_Steps += " ";
        m_Steps += col + row;
        break;
    case 3:
        m_Steps += "-";
        m_Steps += col + row;
        if(!szDescript.empty())
        {
            m_Steps += " {";
            m_Steps += szDescript;
            m_Steps += "}";
        }
        m_Steps += "\n";
        break;
    }
    m_nStep++;
    return 0;
}

int CChessStepsIccs::GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript)
{
    return 0;
}
