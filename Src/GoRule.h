/*******************************************************************************************************
文件名：GoRule.h
功  能：走棋规则
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-18
时  间：9:55:40
*******************************************************************************************************/

#if !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
#define AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Piece.h"

class CHINESECHESS_EXPORT CGoRule
{
public:
	CGoRule();
	virtual ~CGoRule();
    
	typedef enum _ENUM_ReturnValue {
		RETURNFALSE,    //错误，不能走
		BEIJIANGJUN,    //被将军
		JIANGDUIMIAN,   //将对面
		JIANGJUN,       //将军
		JIANGBEICHI,    //将已被吃
		RETURNTRUE      //可以走棋
	} ENUM_ReturnValue;
	ENUM_ReturnValue GoChess(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);

private:
	ENUM_ReturnValue ChessRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]); 

	// 兵规则
	ENUM_ReturnValue BingRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 炮规则
	ENUM_ReturnValue PaoRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 帅规则
	ENUM_ReturnValue ShuaiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 仕规则
	ENUM_ReturnValue ShiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 相规则
	ENUM_ReturnValue XiangRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 马规则
	ENUM_ReturnValue MaRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);
	// 车规则
	ENUM_ReturnValue CheRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10]);

	// 将军
	ENUM_ReturnValue JiangJun(int ito, int jto, CPiece::ENUM_QiZi ChessBoard[][10]);

	// 马将军
	bool MaJiangJun(int iShuai, int jShuai, int iMa, int jMa, CPiece::ENUM_QiZi ChessBoard[][10]);
};

#endif // !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
