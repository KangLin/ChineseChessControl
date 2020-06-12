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

class CChessStepsChinese : public CChessSteps
{
public:
    CChessStepsChinese();
    virtual ~CChessStepsChinese();
    
    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz);
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz);
};

#endif // CCHESSSTEPS_H_KL_2020_06_12_
