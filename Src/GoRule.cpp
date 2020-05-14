/*******************************************************************************************************
文件名：GoRule.cpp
功  能：走棋规则
思  路：红棋放在棋盘上方，黑棋放在棋盘下方。
编译器：Visual C++ 6.0
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：21:38:52
*******************************************************************************************************/

#include "stdafx.h"
#include "GoRule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoRule::CGoRule()
{}

CGoRule::~CGoRule()
{}

/*******************************************************************************************************
函数名：GetQiZiSide
功  能：得到棋子是红棋,还是黑棋
参  数：
		 ENUM_QiZi qz：要专断的棋子
返回值：返回红棋还是黑棋或无棋
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：12:10:36
*******************************************************************************************************/
ENUM_QiZi CGoRule::GetQiZiSide(ENUM_QiZi qz)
{
	if (qz > NoQiZi)
		return RQi;
	if (qz < NoQiZi)
		return BQi;
	return NoQiZi;
}

/*******************************************************************************************************
函数名：GoChess
功  能：判断能否从点（ifrom, jfrom）到点（ito, jto）走棋
参  数：
         int ito：目标点横坐标[0-8]
         int jto：目标点纵坐标[0-9]
         int ifrom：源点横坐标[0-8]
         int jfrom：源点纵坐标[0-9]
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：将对面、JIANGDUIMIAN,叫将、BEIJIANGJUN,将军、JIANGJUN,
        可以走棋、RETURNTRUE，不能走棋、RETURNFALSE,    
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:34:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::GoChess(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	ENUM_ReturnValue m_RV;
	ENUM_QiZi goneChessBoard[9][10];

	m_RV = ChessRule(ito, jto, ifrom, jfrom, ChessBoard);
	if(m_RV == RETURNTRUE)
	{
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 10; j++)
				goneChessBoard[i][j] = ChessBoard[i][j];
		//假设走棋
		goneChessBoard[ito][jto] = goneChessBoard[ifrom][jfrom];
		goneChessBoard[ifrom][jfrom] = NoQiZi;
		//判断将对面、叫将、将军
		m_RV = JiangJun(ito, jto, ifrom, jfrom, goneChessBoard);
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:53:57
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ChessRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	switch(ChessBoard[ifrom][jfrom])
	{
	case BChe:
	case RChe:
		return CheRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BMa:
	case RMa:
		return MaRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BXiang:
	case RXiang:
		return XiangRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BShi:
	case RShi:
		return ShiRule(ito, jto, ifrom, jfrom, ChessBoard);
		break;
	case BShuai:
	case RShuai:
		return ShuaiRule(ito, jto, ifrom, jfrom, ChessBoard);
	case BPao:
	case RPao:
		return PaoRule(ito, jto, ifrom, jfrom, ChessBoard);
	case BBing:
	case RBing:
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:30:51
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::CheRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		while(jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (jfrom != jto))
				return RETURNFALSE;			
		}
		return RETURNTRUE;
	}
	if(jto == jfrom)
	{
		while(ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (ifrom != ito))
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:36:05
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::MaRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 1 && abs(jto - jfrom) == 2)
	{
		if(ChessBoard[ifrom][jfrom + sig(jto - jfrom)] == NoQiZi)
			return RETURNTRUE;
		else
			return RETURNFALSE;	
	}
	if(abs(ito - ifrom) == 2 && abs(jto - jfrom) == 1)
	{
		if(ChessBoard[ifrom + sig(ito - ifrom)][jfrom] == NoQiZi)
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：22:49:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::XiangRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(abs(ito - ifrom) == 2 
		&& abs(jfrom - jto) == 2 
		&& ChessBoard[ifrom + sig(ito - ifrom)][jfrom + sig(jto - jfrom)] == NoQiZi)
	{
		if(jfrom <= 4 && jto <=4)
			return RETURNTRUE;
		if(jfrom >=5 && jto >=5)
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:07:29
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:15:40
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::ShuaiRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if (ito >= 3 && ito <= 5
		&& ((abs(ito - ifrom) == 1 && jto == jfrom)
			|| (abs(jto - jfrom) == 1 && ito == ifrom)))
	{
		if (/*jfrom >= 0 &&*/ jfrom <= 2 && /*jto >= 0 &&*/ jto <= 2)
			return RETURNTRUE;
		if (jfrom >= 7 /*&& jfrom <= 9 */&& jto >= 7/* && jto <= 9*/)
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:24:18
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::PaoRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	if(ito == ifrom)
	{
		int iNum = 0;
		while(jfrom != jto)
		{
			jfrom += sig(jto - jfrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (jfrom != jto))
				iNum++;
		}
		switch(iNum)
		{
		case 0:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNFALSE;
		    else
				return RETURNTRUE;
			break;
		default:
			return RETURNFALSE;
		}
	}
	if(jto == jfrom)
	{
		int iNum = 0;
		while(ifrom != ito)
		{
			ifrom += sig(ito - ifrom);
			if(ChessBoard[ifrom][jfrom] != NoQiZi && (ifrom != ito))
				iNum++;
			
		}
		switch(iNum)
		{
		case 0:
			if(ChessBoard[ito][jto] == NoQiZi)
				return RETURNTRUE;
		    else
				return RETURNFALSE;
			break;
		case 1:
			if(ChessBoard[ito][jto] == NoQiZi)
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：如果可走返回 RETURNTRUE，否则返回 RETURNFALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：23:38:32
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::BingRule(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	bool bTopSide = false;
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (ChessBoard[i][j])
			{
			case RShuai:
			case RShi:
			case BShuai:
			case BShi:
				bTopSide = GetQiZiSide(ChessBoard[i][j]) == GetQiZiSide(ChessBoard[ifrom][jfrom]);
				break;
			default:
				break;
			}
		}
	}
	if (bTopSide)
	{
		if (jto - jfrom == 1 && ito == ifrom)
			return RETURNTRUE;
		if (jfrom > 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
			return RETURNTRUE;
	} else {
		if(jto - jfrom == -1 && ito == ifrom)		
			return RETURNTRUE;
		if(jfrom <= 4 && abs(ito - ifrom) <= 1 && jto == jfrom)
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
         ENUM_QiZi ChessBoard[9][10]：棋盘数组
返回值：返回 JIANGDUIMIAN、BEIJIANGJUN、JIANGJUN, RETURNTRUE
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-2
时  间：9:02:54
*******************************************************************************************************/
CGoRule::ENUM_ReturnValue CGoRule::JiangJun(int ito, int jto, int ifrom, int jfrom, ENUM_QiZi ChessBoard[][10])
{
	int iRShuai, jRShuai, iBShuai, jBShuai;
	//找黑帅
	for(iBShuai = 3; iBShuai < 6; iBShuai++)
	{
		for(jBShuai = 7; jBShuai < 10; jBShuai++)
		{
			if(ChessBoard[iBShuai][jBShuai] == BShuai)
				break;
		}
		if(ChessBoard[iBShuai][jBShuai] == BShuai)
			break;		
	}
	//找红帅
	for(iRShuai = 3; iRShuai < 6; iRShuai++)
	{
		for(jRShuai = 0; jRShuai < 3; jRShuai++)
		{
			if(ChessBoard[iRShuai][jRShuai] == RShuai)
				break;
		}
		if(ChessBoard[iRShuai][jRShuai] == RShuai)
			break;		
	}

	//判断将对面
	int i = 0, j;
	if(iBShuai == iRShuai)
	{
		j = jRShuai;
		while(j != jBShuai)
		{
			j++;
			//判断中间是否有子
			if(ChessBoard[iRShuai][j] != NoQiZi && j != jBShuai)
			{
				i++;
				break;
			}
		}
		if(i == 0)
			return JIANGDUIMIAN;
	}

	//判断被将军、判断将军
	switch(GetQiZiSide(ChessBoard[ito][jto]))
	{	
	case RQi:
		//被将
		i = iRShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jRShuai;
        for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;		
		//马
		i = iRShuai - 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

        //将军
		i = iBShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		j = jBShuai;
		for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  JIANGJUN;
		//马
		i = iBShuai - 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		
		
	case BQi:
		//被将
		i = iBShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		j = jBShuai;
		for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == RQi)
				if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
					return  BEIJIANGJUN;
		//马
		i = iBShuai - 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai - 2;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 1;
		j = jBShuai + 2;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai - 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai - 1;
		if(ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		

		i = iBShuai + 2;
		j = jBShuai + 1;
		if(j < 10 && ChessBoard[i][j] == RMa)
			if(ChessRule(iBShuai, jBShuai, i, j, ChessBoard) == RETURNTRUE)
				return  BEIJIANGJUN;		
		
		//将军
		i = iRShuai;
		for(j = 0; j < 10; j++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;
		j = jRShuai;
        for(i = 0; i < 10; i++)
			if(GetQiZiSide(ChessBoard[i][j]) == BQi)
				if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
					return JIANGJUN;		
        
		//马
		i = iRShuai - 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai - 2;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 1;
		j = jRShuai + 2;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai - 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai - 1;
		if(j >= 0 && ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		

		i = iRShuai + 2;
		j = jRShuai + 1;
		if(ChessBoard[i][j] == BMa)
			if(ChessRule(iRShuai, jRShuai, i, j, ChessBoard) == RETURNTRUE)
				return  JIANGJUN;		
		break;
	}

	return RETURNTRUE;
}
