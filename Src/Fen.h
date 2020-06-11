/**
  Forsyth-Edwards Notation
  
  */

#ifndef CFEN_H
#define CFEN_H

#pragma once

#include <string>
#include "Piece.h"

class CFen
{
public:
    CFen();
    
    int FenFromBoard(std::string &szFen, CPiece::ENUM_QiZi board[][10],
                     char side = 'r', int nStep = 1);
    int FenToBoard(const std::string &szFen, CPiece::ENUM_QiZi board[][10],
                   char &side, int &nStep);
};

#endif // CFEN_H
