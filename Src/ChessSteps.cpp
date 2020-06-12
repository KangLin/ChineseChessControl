#include "ChessSteps.h"

CChessSteps::CChessSteps()
{}

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

int CChessStepsChinese::AddStep(int i, int j, CPiece::ENUM_QiZi qz)
{
    return 0;
}

int CChessStepsChinese::GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz)
{
    return 0;
}
