#ifndef CCHESSSTEPSCHINESE_H
#define CCHESSSTEPSCHINESE_H

#include "ChessSteps.h"

class CChessStepsChinese : public CChessSteps
{
public:
    CChessStepsChinese();
    virtual ~CChessStepsChinese();
    
    virtual std::string toString();
    virtual int GetStep(int &i, int &j, CPiece::ENUM_QiZi &qz, std::string &szDescript);

private:
    std::string GetQiZi(CPiece::ENUM_QiZi qz);
    std::string StepToString(strStep to, strStep from);
    /**
     * @brief 查找同列是否有相同的棋子
     * @param qz
     * @return： 0，没有；>0,前面有；<0后面有
     */
    int FindSameQiZi(strStep step);
    std::string FindSameColumBing(strStep step);
    
    const std::string ChineseNumber[10] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
    std::string m_Ping; //平
    std::string m_Jin;  //进
    std::string m_Tui;  //退
    std::string m_Qian; //前
    std::string m_Zhong;//中
    std::string m_Hou;  //后
};

#endif // CCHESSSTEPSCHINESE_H
