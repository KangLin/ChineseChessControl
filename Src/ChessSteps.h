#ifndef CCHESSSTEPS_H_KL_2020_06_12_
#define CCHESSSTEPS_H_KL_2020_06_12_

#pragma once

#include <string>
#include <vector>
#include "Piece.h"

class CChessSteps
{
public:
    CChessSteps();
    virtual ~CChessSteps();

    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz) = 0;
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz) = 0;

    virtual std::string toString();

private:
    std::string m_Steps;
};

#endif // CCHESSSTEPS_H_KL_2020_06_12_
