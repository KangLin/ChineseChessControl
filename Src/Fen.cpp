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

    FEN就是“福斯夫-爱德华兹记号法”(Forsyth-Edwards Notation)，
这是一种使用ASCII码字符描述国际象棋局面的标准。
FEN是建立在19世纪由报社记者S·D·福斯夫设计的记录局面的标准基础上的。
后来为了适合象棋软件的需要，由爱德华兹对此做了少许修改。

1-1 结构描述
　　一个FEN记录使用长度可不同的一行来表示，由六个区域组成。
单纯的FEN记录文件后缀应该是“.fen”，比如：kk-1.fen。
　　FEN描述了：棋子位置、轮走棋方、易位可行性、吃过路兵目标格、半步计数、以及总回合数。
所有这一切用一行文字符号表示就行了而且非常容易读。
　　看看一个FEN的六个区域及其含义，先举一个谁都太熟悉了的局面的FEN文件：
    rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1
　　这就是每盘常规对局的最初局面，一个子都没有动。
　　译文以不同颜色表示了这个FEN中的六个不同区域，它们是：
　
1) 棋子位置数值区域(Piece placement data) 
　　就是表示双方棋子各在棋盘哪个格子上的。
规则是从第8横线开始顺次数到第1横线(白方在下，从上数到下)，从a线开始顺次数到h线；
白方棋子以大写字母“PNBRQK”表示，黑方棋子以小写“pnbrqk”表示，这是英文表示法，
每个字母代表的意义与常规规定相同。数字代表一个横线上的连续空格，反斜杠“/” 表示结束一个横线的描述。
　　上面的那pppppppp，就是表示黑方在第7横线上排有8只兵；后面那4个数字8，
就是表示从第6到第3横线，双方一个棋子都不在，是空格；7个反斜杠“/”将第一区域分成8段，
因为棋盘有8条横线；其它的照着图完全可以类推。
　
2) 轮走棋方(Active color) 
　　表示目前局面该谁走棋。小写“r”表示红方走棋；小写“b”表示黑方走棋；
显然起初局面肯定是红先，所以上面就是“r” 。

3) 易位可行性(Castling availability) 
　　这表示在当前局面下每一方有没有潜在的各种王车易位的可行性(目前不一定行，但以后有可能行)。
如果谁都没有，就用“-”表示；大写“K”表示白方有短易位的可行性，
大写“Q”表示白方有长易位的可行性；对应的小写“k”和“q”代表黑方短和长易位的可行性。
书写顺序必须是先大写后小写、先短易位后长易位，并且之间不能有空格。
中国象棋中没有这个，用 “-” 表示
　
4) 吃过路兵目标格(En passant target square) 
　　如果没有，就用“-”表示。如果有，就用具体完成吃过路兵的那个格子坐标来表示，
显然对于白兵被吃只可能在第3横线，对于黑兵被吃只可能在第6横线。
而且，这个标记是且只是在该局面紧接的上一步棋是某方刚走兵推进两格的情况下出现。
中国象棋中没有这个，用 “-” 表示

5) 半回合计数(Halfmove clock) 
　　用一个非负数表示自从上一次动兵或吃子之后目前走了的半回合数。这个是为了适应50步和棋规则而定。
【译注：但是在winboard的FEN输出中，这个值好象总是0】

6) 回合数(Fullmove number) 
　　当前要进行到的回合数。不管白还是黑，第一步时总是以1表示，以后黑方每走一步数字就加1。

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
    if(startGame.empty()) return -1;
    
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
    return FenFromBoard(szFen, board, side, nStep);
}
