
#ifndef CFEN_H_KL_2020_06_11_
#define CFEN_H_KL_2020_06_11_

#pragma once

#include <vector>
// 作者：康林 <kl222@126.com>

#include <string>
#include "Piece.h"
#include "ChessGame.h"

/**
 * 福斯夫-爱德华兹记号法 (Forsyth-Edwards Notation)
 * @see https://www.xqbase.com/protocol/cchess_fen.htm
 *      http://www.xqbase.com/protocol/pgnfen2.htm
 */
class CFen
{
public:
    CFen();
    
    int FenFromBoard(std::string &szFen, CPiece::ENUM_QiZi board[][10],
                     char side = 'r', int nStep = 1);
    int FenToBoard(const std::string &szFen, CPiece::ENUM_QiZi board[][10],
                   char &side, int &nStep);
    int FenFromStartGame(std::string &szFen,
                         std::vector<CChessGame::strStartGame> startGame,
                         char side = 'r',
                         int nStep = 1);
};

#endif // CFEN_H_KL_2020_06_11_
