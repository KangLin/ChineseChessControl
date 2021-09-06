// 作者：康林 <kl222@126.com>

#include "Piece.h"

CPiece::CPiece()
{}

CPiece::~CPiece()
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
/*CPiece::ENUM_QiZi CPiece::GetQiZiSide(ENUM_QiZi qz)
{
	if (qz > NoQiZi)
		return RQi;
	if (qz < NoQiZi)
		return BQi;
	return NoQiZi;
}*/

bool CPiece::IsRedQiZi(ENUM_QiZi qz)
{
	if (NoQiZi == qz) return false;
	return !(0x8 & qz);
}

bool CPiece::IsBlackQiZi(ENUM_QiZi qz)
{
	if (NoQiZi == qz) return false;
	return 0x8 & qz;
}

bool CPiece::IsExistQiZi(ENUM_QiZi qz)
{
	return NoQiZi != qz;
}

bool CPiece::IsNoQiZi(ENUM_QiZi qz)
{
	return NoQiZi == qz;
}

bool CPiece::IsSameSide(ENUM_QiZi me, ENUM_QiZi other)
{
	if (NoQiZi == me || NoQiZi == other)
		return false;
	return (0x08 & me) == (0x08 & other);
}

bool CPiece::IsOtherSide(ENUM_QiZi me, ENUM_QiZi other)
{
	if (NoQiZi == me || NoQiZi == other)
		return false;
	return (0x08 & me) != (0x08 & other);
}

bool CPiece::IsOtherSideMa(ENUM_QiZi me, ENUM_QiZi otherMa)
{
	if (IsOtherSide(me, otherMa))
		return otherMa == RMa || otherMa == BMa;
	return false;
}

bool CPiece::IsShuai(ENUM_QiZi qz)
{
	if (RShuai == qz || BShuai == qz)
		return true;
	return false;
}

bool CPiece::IsShi(ENUM_QiZi qz)
{
	if (RShi == qz || BShi == qz)
		return true;
	return false;
}
