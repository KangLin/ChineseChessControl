#ifndef CCHESSSTEPS_H_KL_2020_06_12_
#define CCHESSSTEPS_H_KL_2020_06_12_

#pragma once

#include <string>
#include <vector>
#include "Piece.h"

/**
 @brief 着法 
 @see http://www.xqbase.com/protocol/cchess_move.htm
 */
class CChessSteps
{
public:
    CChessSteps();
    virtual ~CChessSteps();

    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript);
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript) = 0;

    virtual std::string toString();

    struct strStep {
		int i;
        int j;
        CPiece::ENUM_QiZi qz;
		std::string szDescript; //这一步的描述信息
	};
    virtual int AddStep(strStep step);
    
    CPiece::ENUM_QiZi m_Board[9][10];
    
protected:
    std::string m_szSteps;
    int m_nSteps;
    std::vector<strStep> m_Steps;
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
