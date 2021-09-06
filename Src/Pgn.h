// 作者：康林 <kl222@126.com>

#ifndef CPGN_H_KL_2020_06_11_
#define CPGN_H_KL_2020_06_11_

#pragma once

#include <string>
#include <map>
#include <time.h>
#include <memory>

#include "ChessStepsChinese.h"

/**
 * @brief Class to hold all information for the Portable Game Notation (PGN) of a
 *        single game. 
 * 
 * @see   http://www.xqbase.com/protocol/cchess_pgn.htm
 *        https://www.xqbase.com/protocol/pgnfen1.htm
 */
class CPGN
{
public:
    CPGN();
    
    std::string GetTag(const std::string &szTag);
    int SetTag(const std::string &szTag, const std::string& szValue);
    
    /** \brief Gets the game as PGN string.
     *
     * \return Returns the complete PNG notation for the game.
     */
    std::string toString() const;
    /**
     * @brief 解析 PGN
     * @param szPgn
     * @return 
     */
    int ParseString(const std::string szPgn);

    /** \brief Gets the name of the tournament or match event.
     *
     * \return name of the tournament or match event
     */
    const std::string& GetEvent() const;
    int SetEvent(const char* pEvent);

    /** \brief Gets the location of the event.
     *
     * \return location of the event
     */
    const std::string& GetSite() const;
    int SetSite(const char* pSite);

    /** \brief Gets the date of the event.
     *
     * \return date of the event
     */
    const time_t& GetDate() const;
    int SetDate(const time_t &t);

    int parseDate(const std::string& dateText);
    std::string dateToString(const time_t &t) const;
    
    /** \brief Get the playing round ordinal of the game.
     *
     * \return playing round ordinal of the game
     */
    const std::string& GetRound() const;
    int SetRound(const char* pRound);

    /** \brief Get the player(s) of the white pieces.
     *
     * \return player(s) of the white pieces
     */
    const std::string& GetRed() const;
    int SetRed(const char* pRed);

    /** \brief Get the player(s) of the black pieces.
     *
     * \return player(s) of the black pieces
     */
    const std::string& GetBlack() const;
    int SetBlack(const char* pBlack);

    /** \brief Gets the result of the game, if any.
     *
     * \return result of the game
     */
    const std::string& GetResult() const;
    int SetResult(const char* pResult);
    
    const std::string& GetFen() const;
    int SetFen(const char* pFen);
    
    const std::string& GetFormat() const;
    int SetFormat(const char* pFormat);
    
    int SetSteps(std::shared_ptr<CChessSteps> steps);
    
private:
    std::string m_Game;						   //游戏类型，国际象棋没有这个标签，中国象棋的PGN文件中这个标签必须放在第一位，其值必须为“Chinese Chess”
    std::string m_Event;					   //比赛名
    std::string m_Site;						   //比赛地点
    time_t m_Date;							   //比赛日期，格式统一为“yyyy.mm.dd”
    std::string m_Round;					   //比赛轮次
    std::string m_Red;						   //红方棋手，不同与国际象棋的White
    std::string m_Black;					   //黑方棋手
    std::string m_Result;					   //比赛结果，“红先胜”用“1-0”表示，“黑先胜”用“0-1”表示，和棋用“1/2-1/2”表示，未知用“*”表示。
    std::string m_szFEN;					   //开始局面，中局、残局和排局等摆出来的局面，作棋谱记录时通常要规定这个选项
    std::string m_Format;					   //表示记谱方法，可以是Chinese(中文纵线格式)、WXF(WXF纵线格式)和ICCS(ICCS坐标格式)，默认为Chinese。
    std::map<std::string, std::string> m_Tags; 
    
    std::shared_ptr<CChessSteps> m_pSteps;
};

#endif // CPGN_H_KL_2020_06_11_
