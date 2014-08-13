/*******************************************************************************************************
文件名：GoRule.h
功  能：走棋规则
思  路：红棋放在棋盘上方，黑棋放在棋盘下方。
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-18
时  间：9:55:40
*******************************************************************************************************/

#if !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
#define AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_

#include "EnumAndStructAndConst.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGoRule  
{
public:
	CGoRule();
	virtual ~CGoRule();
    
	ENUM_ReturnValue GoChess(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[9][10]);

private:
	ENUM_ReturnValue JiangJun(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[9][10]);
	ENUM_ReturnValue ChessRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue BingRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue PaoRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue ShuaiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue ShiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10]);
	ENUM_ReturnValue XiangRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[9][10]);
	ENUM_ReturnValue MaRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[9][10]);
	ENUM_ReturnValue CheRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[9][10]);

};

#endif // !defined(AFX_GORULE_H__D75E7189_0187_471C_8E8D_237321CC4D18__INCLUDED_)
