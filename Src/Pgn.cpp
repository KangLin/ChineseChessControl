#include "Pgn.h"
#include <memory.h>

CPGN::CPGN()
    : m_Game("Chinese Chess"),
      m_Event("?"),
      m_Site("?"),
      m_Date(time(nullptr)),
      m_Round("?"),
      m_Red("?"),
      m_Black("?"),
      m_Result("*"),
      m_Format("Chinese"),
      m_pSteps(nullptr)
{}

std::string CPGN::GetTag(const std::string &szTag)
{
    const auto iter = m_Tags.find(szTag);
     if (iter != m_Tags.end())
       return iter->second;
     // Is it a tag from the standard tag roster?
     if (szTag == "Event")
       return GetEvent();
     if (szTag == "Site")
       return GetSite();
     if (szTag == "Date")
     {
         return dateToString(GetDate());
     }
     if (szTag == "Round")
       return GetRound();
     if (szTag == "Red")
       return GetRed();
     if (szTag == "Black")
       return GetBlack();
     if (szTag == "Result")
       return GetResult();
     if(szTag == "Fen")
         return GetFen();
     if(szTag == "Format")
         return GetFormat();

     // Tag was not found.
     return std::string();
}

int CPGN::SetTag(const std::string &szTag, const std::string &szValue)
{
    if (szTag == "Event")
        SetEvent(szValue.c_str());
    else if (szTag == "Site")
        SetSite(szValue.c_str());
    else if (szTag == "Date")
        parseDate(szValue);
    else if (szTag == "Round")
        SetRound(szValue.c_str());
    else if (szTag == "Red")
        SetRed(szValue.c_str());
    else if (szTag == "Black")
        SetBlack(szValue.c_str());
    else if (szTag == "Result")
        SetResult(szValue.c_str());
    else if(szTag == "Fen")
        SetFen(szValue.c_str());
    else if(szTag == "Format")
        SetFormat(szValue.c_str());
    else
        m_Tags[szTag] = szValue;
    return 0;
}

std::string CPGN::toString() const
{
    std::string pgn;
    
    pgn = "[Game \"" + m_Game + "\"]\n"
            + "[Event \"" + GetEvent() + "\"]\n"
            + "[Site \"" + GetSite() + "\"]\n";
    
    pgn += "[Date \"";
    pgn += dateToString(GetDate());
    pgn += "\"]\n";
    
    pgn += "[Round \"" + GetRound() + "\"]\n"
            + "[Red \"" + GetRed() + "\"]\n"
            + "[Black \"" + GetBlack() + "\"]\n"
            + "[Result \"" + GetResult() + "\"]\n";
    + "[Fen \"" + GetFen() + "\"]\n";
    + "[Format \"" + GetFormat() + "\"]\n";
    for(const auto& item : m_Tags)
    {
        pgn += "[" + item.first + " \"" + item.second + "\"]\n";
    } // for
    pgn += "\n";
    pgn += m_pSteps->toString();
    pgn += " " + GetResult();
    return pgn;
}

const std::string &CPGN::GetEvent() const
{
    return m_Event;
}

int CPGN::SetEvent(const char *pEvent)
{
    m_Event = pEvent;
    return 0;
}

const std::string& CPGN::GetSite() const
{
    return m_Site;
}

int CPGN::SetSite(const char *pSite)
{
    m_Site = pSite;
    return 0;
}

const time_t& CPGN::GetDate() const
{
    return m_Date;
}

int CPGN::parseDate(const std::string &dateText)
{
    struct tm tm;
    
    memset(&tm, 0, sizeof (struct tm));
    sscanf(dateText.c_str(), "%d.%d.%d" ,    
           &(tm.tm_year),
           &(tm.tm_mon),
           &(tm.tm_mday));
    tm.tm_year -= 1900;
    tm.tm_mon --;
    m_Date = mktime(&tm);
    return 0;
}

std::string CPGN::dateToString(const time_t &t) const
{
    struct tm* t1 = localtime(&t);
    char buf[30];
    strftime(buf, 30, "%Y.%m.%d", t1);
    return buf;
}

int CPGN::SetDate(const time_t &t)
{
    m_Date = t;
    return 0;
}

const std::string& CPGN::GetRound() const
{
    return m_Round;
}

int CPGN::SetRound(const char *pRound)
{
    m_Round = pRound;
    return 0;
}

const std::string& CPGN::GetRed() const
{
    return m_Red;
}

int CPGN::SetRed(const char *pRed)
{
    m_Red = pRed;
    return 0;
}

const std::string& CPGN::GetBlack() const
{
    return m_Black;
}

int CPGN::SetBlack(const char *pBlack)
{
    m_Black = pBlack;
    return 0;
}

const std::string& CPGN::GetResult() const
{
    return m_Result;
}

int CPGN::SetResult(const char *pResult)
{
    m_Result = pResult;
    return 0;
}

const std::string& CPGN::GetFen() const
{
    return m_szFEN;
}

int CPGN::SetFen(const char *pFen)
{
    m_szFEN = pFen;
    return 0;
}

const std::string& CPGN::GetFormat() const
{
    return m_Format;
}

int CPGN::SetFormat(const char *pFormat)
{
    m_Format = pFormat;
    return 0;
}

int CPGN::SetSteps(CChessSteps *steps)
{
    m_pSteps = steps;
    return 0;
}
