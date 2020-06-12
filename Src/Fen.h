/**
  Forsyth-Edwards Notation
  
  */

#ifndef CFEN_H_KL_2020_06_11_
#define CFEN_H_KL_2020_06_11_

#pragma once

#include <vector>
#include <string>
#include "Piece.h"
#include "ChessGame.h"

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
