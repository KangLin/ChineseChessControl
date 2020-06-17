/**
 @brief 着法 
 @see http://www.xqbase.com/protocol/cchess_move.htm
 */

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

    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript) = 0;
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript) = 0;

    virtual std::string toString();

protected:
    std::string m_Steps;
    int m_nStep;
};

class CChessStepsChinese : public CChessSteps
{
public:
    CChessStepsChinese();
    virtual ~CChessStepsChinese();
    
    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript);
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript);
};

class CChessStepsIccs : public CChessSteps
{
public:
    CChessStepsIccs();
    virtual ~CChessStepsIccs();

    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript);
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript);
};

#endif // CCHESSSTEPS_H_KL_2020_06_12_
