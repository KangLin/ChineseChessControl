// 作者：康林 <kl222@126.com>

#ifndef CCHESSSTEPS_H_KL_2020_06_12_
#define CCHESSSTEPS_H_KL_2020_06_12_

#pragma once

#include <string>
#include <vector>
#include "Piece.h"

/**
 * @brief 着法
 * - 棋子的名称
 *   为方便表示，中国象棋的棋子名称除了用汉字以外，还可以用字母，字母可从国际象棋中稍加改动得到，而数字是为了方便棋谱的输入(以便用在数字小键盘上)：
 *   |红方|黑方|字母|相当于国际象棋中的棋子   |数字|
 *   |帅  |将  |K  |King(王)              |1  |
 *   |仕  |士  |A  |Advisor(没有可比较的棋子)|2 |
 *   |相	  |象  |B/E|	Bishop(象)/Elephant   |3 |
 *   |马  |马  |N/H|	Knight(马)/Horse      |4 |
 *   |车  |车  | R |Rook(车)               |5 |
 *   |炮  |炮  | C |Cannon(没有可比较的棋子) |6 |
 *   |兵  |卒  |P  |Pawn(兵)               |7 |
 * @see http://www.xqbase.com/protocol/cchess_move.htm
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

/**
 * @brief ICCS是中国象棋互联网服务器(Internet Chinese Chess Server)的缩写。
 */
class CChessStepsIccs : public CChessSteps
{
public:
    CChessStepsIccs();
    virtual ~CChessStepsIccs();

    virtual int AddStep(int i, int j, CPiece::ENUM_QiZi qz, const std::string &szDescript);
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript);
};

#endif // CCHESSSTEPS_H_KL_2020_06_12_
