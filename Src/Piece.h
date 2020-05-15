/*******************************************************************************************************
文件名：Piece.h
功  能：棋子类
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2020-05-15
时  间：15:25:10
*******************************************************************************************************/

#ifndef __PIECE_H_KL_2020_05_15__
#define __PIECE_H_KL_2020_05_15__

#pragma once
#include "Common.h"

class CPiece
{
public:
	CPiece();
	virtual ~CPiece();

	typedef enum _ENUM_QiZi {
		RShuai = 1, //红帅
		RShi = 2,   //红仕
		RXiang = 3, //红相
		RMa = 4,    //红马
		RChe = 5,   //红车
		RPao = 6,   //红炮
		RBing = 7,  //红兵
		NoQiZi = 0, //无子
		BShuai = -1,//黑帅
		BShi = -2,  //黑仕
		BXiang = -3,//黑相
		BMa = -4,   //黑马
		BChe = -5,  //黑车
		BPao = -6,  //黑炮
		BBing = -7  //黑兵
	} ENUM_QiZi;

	//static ENUM_QiZi GetQiZiSide(ENUM_QiZi qz);
	static bool IsRedQiZi(ENUM_QiZi qz);
	static bool IsBlackQiZi(ENUM_QiZi qz);

	static bool IsExistQiZi(ENUM_QiZi qz);
	static bool IsNoQiZi(ENUM_QiZi qz);

	static bool IsSameSide(ENUM_QiZi me, ENUM_QiZi other);
	static bool IsOtherSide(ENUM_QiZi me, ENUM_QiZi other);

	static bool IsOtherSideMa(ENUM_QiZi me, ENUM_QiZi otherMa);
	static bool IsShuai(ENUM_QiZi qz);
	static bool IsShi(ENUM_QiZi qz);
};

#endif //__PIECE_H_KL_2020_05_15__