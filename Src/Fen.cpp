/**
  
红方    黑方     字母    相当于国际象棋中的棋子
帅       将       K        King(王) 	
仕       士       A        Advisor(没有可比较的棋子) 	
相       象      B/E       Bishop(象) 	
马       马      N/H       Knight(马) 	
车       车       R        Rook(车) 	
炮       炮       C        Cannon(没有可比较的棋子) 	
兵       卒       P        Pawn(兵)

红方用大写字母，黑方用小写字母

@see http://www.xqbase.com/protocol/pgnfen2.htm

注意：棋盘布局:详见《象棋竞赛规则(2011)》第一章 第1条
     红棋在下，黑棋在上，左上角为[0][0]，右下角为[9][10]
 
*/

#include "Fen.h"

/**
 * @brief CFen::CFen
 */
CFen::CFen()
{}

int CFen::FenFromBoard(std::string &szFen, CPiece::ENUM_QiZi (*board)[10],
                       char side, int nStep)
{
    for(int j = 0; j < 10; j++)
    {
        if(j > 0)
            szFen += "/";
        
        int nEmpty = 0;
        for(int i = 0; i < 9; i++)
        {
            CPiece::ENUM_QiZi qz = board[i][j];
            if(CPiece::IsNoQiZi(qz))
                nEmpty++;
            else
            {
                if(nEmpty > 0)
                {
                    szFen += std::to_string(nEmpty);
                    nEmpty = 0;
                }
                switch (qz) {
                case CPiece::RChe:
                    szFen += "R";
                    break;
                case CPiece::RMa:
                    szFen += "N";
                    break;
                case CPiece::RXiang:
                    szFen += "B";
                    break;
                case CPiece::RShi:
                    szFen += "A";
                    break;
                case CPiece::RShuai:
                    szFen += "K";
                    break;
                case CPiece::RPao:
                    szFen += "C";
                    break;
                case CPiece::RBing:
                    szFen += "P";
                    break;
                case CPiece::BChe:
                    szFen += "r";
                    break;
                case CPiece::BMa:
                    szFen += "n";
                    break;
                case CPiece::BXiang:
                    szFen += "b";
                    break;
                case CPiece::BShi:
                    szFen += "a";
                    break;
                case CPiece::BShuai:
                    szFen += "k";
                    break;
                case CPiece::BPao:
                    szFen += "c";
                    break;
                case CPiece::BBing:
                    szFen += "p";
                    break;
                }
            }
        }
        if(nEmpty > 0)
        {
            szFen += std::to_string(nEmpty);
            nEmpty = 0;
        }
    }
    
    szFen += " ";
    szFen += side;
    szFen += " - - - ";
    szFen += std::to_string(nStep);
    return 0;
}

int CFen::FenToBoard(const std::string &szFen, CPiece::ENUM_QiZi (*board)[10],
                     char &side, int &nStep)
{
    int i = 0;
    int j = 0;
    int nPos = 0;
    bool bExit = false;
    while(nPos < szFen.size())
    {
        char c = szFen.at(nPos++);
        switch (c) {
        case 'R':
            board[i][j] = CPiece::RChe;
            i++;
            break;
        case 'N':
        case 'H':
            board[i][j] = CPiece::RMa;
            i++;
            break;
        case 'B':
        case 'E':
            board[i][j] = CPiece::RXiang;
            i++;
            break;
        case 'A':
            board[i][j] = CPiece::RShi;
            i++;
            break;
        case 'K':
            board[i][j] = CPiece::RShuai;
            i++;
            break;
        case 'C':
            board[i][j] = CPiece::RPao;
            i++;
            break;
        case 'P':
            board[i][j] = CPiece::RBing;
            i++;
            break;
        case 'r':
            board[i][j] = CPiece::BChe;
            i++;
            break;
        case 'n':
        case 'h':
            board[i][j] = CPiece::BMa;
            i++;
            break;
        case 'b':
        case 'e':
            board[i][j] = CPiece::BXiang;
            i++;
            break;
        case 'a':
            board[i][j] = CPiece::BShi;
            i++;
            break;
        case 'k':
            board[i][j] = CPiece::BShuai;
            i++;
            break;
        case 'c':
            board[i][j] = CPiece::BPao;
            i++;
            break;
        case 'p':
            board[i][j] = CPiece::BBing;
            i++;
            break;
        case '/':
            j++;
            i = 0;
            if(j > 10) bExit = true;
            break;
        case ' ':
            bExit = true;
            break;
        default:
            std::string n;
            n += c;
            i += atoi(n.c_str());
        }
        
        if(bExit) break;
    }
    
    char c = szFen.at(nPos);
    if('b' == c || 'B' == c)
        side = 'b';
    else
        side = 'r';
    nPos += 8;
    std::string n;
    n += szFen.substr(nPos, szFen.size() - nPos);
    nStep = atoi(n.c_str());
    return 0;
}

int CFen::FenFromStartGame(std::string &szFen,
                           std::vector<CChessGame::strStartGame> startGame,
                           char side,
                           int nStep)
{
    CPiece::ENUM_QiZi board[9][10];
    int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
        {
            board[i][j] = CPiece::NoQiZi;
        }
    
    for(auto &it: startGame)
    {
        board[it.i][it.j] = it.qz;
    }

    int nRet = CChessGame::CheckGame(board);
    if(nRet) return nRet;
    return FenToBoard(szFen, board, side, nStep);
}
