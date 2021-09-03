/*******************************************************************************************************
文件名：GoRule.cpp
功  能：走棋规则
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：21:38:52
*******************************************************************************************************/

#include "GoRule.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoRule::CGoRule()
{}

CGoRule::~CGoRule()
{}

/*******************************************************************************************************
函数名：GoChess
功  能：判断能否从点（ifrom, jfrom）到点（ito, jto）走棋
参  数：
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：将对面、JIANGDUIMIAN,叫将、BEIJIANGJUN,将军、JIANGJUN,
		可以走棋、RETURNTRUE，不能走棋、RETURNFALSE,
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:34:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::GoChess(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	ENUM_ReturnValue m_RV;
	CPiece::ENUM_QiZi goneChessBoard[9][10];

	m_RV = ChessRule(ito, jto, ifrom, jfrom, ChessBoard);
	if (m_RV == RETURNTRUE)
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				goneChessBoard[i][j] = ChessBoard[i][j];
		//假设走棋
		goneChessBoard[ito][jto] = goneChessBoard[ifrom][jfrom];
		goneChessBoard[ifrom][jfrom] = CPiece::NoQiZi;
		//判断将对面、叫将、将军
		m_RV = JiangJun(ito, jto, goneChessBoard);
	}

	return m_RV;
}

/*******************************************************************************************************
函数名：ChessRule
功  能：分别判断各棋子走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:53:57
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ChessRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	switch (ChessBoard[ifrom][jfrom])
	{
	case CPiece::BChe:
	case CPiece::RChe:
		return CheRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BMa:
	case CPiece::RMa:
		return MaRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BXiang:
	case CPiece::RXiang:
		return XiangRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BShi:
	case CPiece::RShi:
		return ShiRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case CPiece::BShuai:
	case CPiece::RShuai:
		return ShuaiRule(ito, jto, ifrom, jfrom, ChessBoard);
	case CPiece::BPao:
	case CPiece::RPao:
		return PaoRule(ito, jto, ifrom, jfrom, ChessBoard);
	case CPiece::BBing:
	case CPiece::RBing:
		return BingRule(ito, jto, ifrom, jfrom, ChessBoard);
	default:
		return RETURNFALSE;
	}
	return RETURNTRUE;
}

/*******************************************************************************************************
函数名：CheRule
功  能：车的走法
参  数：
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:30:51
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::CheRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (ito == ifrom)
	{
		while (jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if (CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (jfrom != jto))
				return RETURNFALSE;
		}
		return RETURNTRUE;
	}
	if (jto == jfrom)
	{
		while (ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if (CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (ifrom != ito))
				return RETURNFALSE;
		}
		return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：MaRule
功  能：马的走法
参  数：
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:36:05
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::MaRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (abs(ito - ifrom) == 1 && abs(jto - jfrom) == 2)
	{
		if (CPiece::IsNoQiZi(ChessBoard[ifrom][jfrom + sig(jto - jfrom)]))
			return RETURNTRUE;
		else
			return RETURNFALSE;
	}
	if (abs(ito - ifrom) == 2 && abs(jto - jfrom) == 1)
	{
		if (CPiece::IsNoQiZi(ChessBoard[ifrom + sig(ito - ifrom)][jfrom]))
			return RETURNTRUE;
		else
			return RETURNFALSE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：XiangRule
功  能：象的走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:49:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::XiangRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (abs(ito - ifrom) == 2
		&& abs(jfrom - jto) == 2
		&& CPiece::IsNoQiZi(ChessBoard[ifrom + sig(ito - ifrom)][jfrom + sig(jto - jfrom)]))
	{
		if (jfrom <= 4 && jto <= 4)
			return RETURNTRUE;
		if (jfrom >= 5 && jto >= 5)
			return RETURNTRUE;
	}

	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：ShiRule
功  能：士的走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:07:29
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (abs(ifrom - ito) == 1
		&& abs(jfrom - jto) == 1
		&& ito >= 3 && ito <= 5)
	{
		if (jfrom >= 0 && jfrom <= 2 && jto >= 0 && jto <= 2)
			return RETURNTRUE;
		if (jfrom >= 7 && jfrom <= 9 && jto >= 7 && jto <= 9)
			return RETURNTRUE;
	}

	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：ShuaiRule
功  能：将的走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:15:40
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShuaiRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (ito >= 3 && ito <= 5
		&& ((abs(ito - ifrom) == 1 && jto == jfrom)
			|| (abs(jto - jfrom) == 1 && ito == ifrom)))
	{
		if (/*jfrom >= 0 &&*/ jfrom <= 2 && /*jto >= 0 &&*/ jto <= 2)
			return RETURNTRUE;
		if (jfrom >= 7 /*&& jfrom <= 9 */ && jto >= 7/* && jto <= 9*/)
			return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：PaoRule
功  能：炮的走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:24:18
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::PaoRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (ito == ifrom)
	{
		int iNum = 0;
		while (jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if (CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (jfrom != jto))
				iNum++;
		}
		switch (iNum)
		{
		case 0:
			if (CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNTRUE;
			else
				return RETURNFALSE;
			break;
		case 1:
			if (CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNFALSE;
			else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	if (jto == jfrom)
	{
		int iNum = 0;
		while (ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if (CPiece::IsExistQiZi(ChessBoard[ifrom][jfrom]) && (ifrom != ito))
				iNum++;

		}
		switch (iNum)
		{
		case 0:
			if (CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNTRUE;
			else
				return RETURNFALSE;
			break;
		case 1:
			if (CPiece::IsNoQiZi(ChessBoard[ito][jto]))
				return RETURNFALSE;
			else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：BingRule
功  能：兵的走法
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:38:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::BingRule(int ito, int jto, int ifrom, int jfrom, CPiece::ENUM_QiZi ChessBoard[][10])
{
	bool bTopSide = false;
	bool bExit = false;
    // 判断是否与上面的士、帅是同一边的
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (ChessBoard[i][j])
			{
			case CPiece::RShuai:
			case CPiece::RShi:
			case CPiece::BShuai:
			case CPiece::BShi:
				bTopSide = CPiece::IsSameSide(ChessBoard[i][j], ChessBoard[ifrom][jfrom]);
				bExit = true;
				break;
			default:
				break;
			}
		}
		if (bExit)
			break;
	}
	if (bTopSide)
	{
		if (jto - jfrom == 1 && ito == ifrom)
			return RETURNTRUE;
		if (jfrom > 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
	}
	else {
		if (jto - jfrom == -1 && ito == ifrom)
			return RETURNTRUE;
		if (jfrom <= 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
	}
	return RETURNFALSE;
}

/*******************************************************************************************************
函数名：JiangJun
功  能：判断将对面、叫将、将军
参  数：
		 int ito：目标点横坐标[0-8]
		 int jto：目标点纵坐标[0-9]
		 int ifrom：源点横坐标[0-8]
		 int jfrom：源点纵坐标[0-9]
		 CPiece::ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：返回 JIANGDUIMIAN、BEIJIANGJUN、JIANGJUN, RETURNTRUE
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-2
时  间：9:02:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::JiangJun(int ito, int jto, CPiece::ENUM_QiZi ChessBoard[][10])
{
	int iTopShuai = 0, jTopShuai = 0;
	int iBottomShuai = 0, jBottomShuai = 0;
	bool bExit = false;
	//找底下的帅的位置
	for (iBottomShuai = 3; iBottomShuai < 6; iBottomShuai++)
	{
		for (jBottomShuai = 7; jBottomShuai < 10; jBottomShuai++)
		{
			if (CPiece::IsShuai(ChessBoard[iBottomShuai][jBottomShuai]))
			{
				bExit = true;
				break;
			}
		}
		if (bExit) break;
	}
	bExit = false;
	//找上面的帅的位置
	for (iTopShuai = 3; iTopShuai < 6; iTopShuai++)
	{
		for (jTopShuai = 0; jTopShuai < 3; jTopShuai++)
		{
			if (CPiece::IsShuai(ChessBoard[iTopShuai][jTopShuai]))
			{
				bExit = true;
				break;
			}
		}
		if (bExit) break;
	}
	if (!CPiece::IsShuai(ChessBoard[iTopShuai][jTopShuai])
		|| !CPiece::IsShuai(ChessBoard[iBottomShuai][jBottomShuai]))
		return JIANGBEICHI;  //没找到帅，被吃了

	//判断将对面
	int i = 0, j = 0;
	if (iBottomShuai == iTopShuai)
	{
		j = jTopShuai;
		while (j != jBottomShuai)
		{
			j++;
			//判断中间是否有子
			if (CPiece::IsExistQiZi(ChessBoard[iTopShuai][j]) && j != jBottomShuai)
			{
				i++;
				break;
			}
		}
		if (i == 0)
			return JIANGDUIMIAN;
	}

	// 必须是先判断被将军，再判断将军
	// 当前棋子是上面这一边的
	if (CPiece::IsSameSide(ChessBoard[ito][jto], ChessBoard[iTopShuai][jTopShuai]))
	{
		//被（车，炮，兵)将
		i = iTopShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;

		j = jTopShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;

		//被马将
		if (MaJiangJun(iTopShuai, jTopShuai, ChessBoard))
			return BEIJIANGJUN;

		//车、炮、兵将军
		i = iBottomShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		j = jBottomShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		//马将军
		if (MaJiangJun(iBottomShuai, jBottomShuai, ChessBoard))
			return JIANGJUN;
	}

	//当前棋子是下面这一边的
	if (CPiece::IsSameSide(ChessBoard[ito][jto], ChessBoard[iBottomShuai][jBottomShuai]))
	{
		//被（车、炮、兵)将军
		i = iBottomShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jBottomShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iBottomShuai][jBottomShuai], ChessBoard[i][j]))
				if (ChessRule(iBottomShuai, jBottomShuai, i, j, ChessBoard) == RETURNTRUE)
					return BEIJIANGJUN;
		//被马将
		if (MaJiangJun(iBottomShuai, jBottomShuai, ChessBoard))
			return BEIJIANGJUN;

		//（车，炮，兵)将
		i = iTopShuai;
		for (j = 0; j < 10; j++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;

		j = jTopShuai;
		for (i = 0; i < 9; i++)
			if (CPiece::IsOtherSide(ChessBoard[iTopShuai][jTopShuai], ChessBoard[i][j]))
				if (ChessRule(iTopShuai, jTopShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;

		//马将
		if (MaJiangJun(iTopShuai, jTopShuai, ChessBoard))
			return JIANGJUN;
	}

	return RETURNTRUE;
}

// 马将军
bool CGoRule::MaJiangJun(int iShuai, int jShuai, int iMa, int jMa, CPiece::ENUM_QiZi ChessBoard[][10])
{
	if (CPiece::IsOtherSideMa(ChessBoard[iShuai][jShuai], ChessBoard[iMa][jMa]))
		if (ChessRule(iShuai, jShuai, iMa, jMa, ChessBoard) == RETURNTRUE)
			return true;
	return false;
}

// 判断被马将军
bool CGoRule::MaJiangJun(int iShuai, int jShuai, CPiece::ENUM_QiZi ChessBoard[][10])
{
	int i = 0;
	int j = 0;

	i = iShuai - 1;
	j = jShuai - 2;
	if (j >= 0 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai - 1;
	j = jShuai + 2;
	if (j < 10 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai + 1;
	j = jShuai - 2;
	if (j >= 0 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai + 1;
	j = jShuai + 2;
	if (j < 10 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai - 2;
	j = jShuai - 1;
	if (j >= 0 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai - 2;
	j = jShuai + 1;
	if (j < 10 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai + 2;
	j = jShuai - 1;
	if (j >= 0 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	i = iShuai + 2;
	j = jShuai + 1;
	if (j < 10 && MaJiangJun(iShuai, jShuai, i, j, ChessBoard))
		return true;

	return false;
}
