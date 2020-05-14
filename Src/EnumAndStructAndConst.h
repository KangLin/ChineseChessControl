/*******************************************************************************************************
文件名：EnumAndStructAndConst.h
功  能：象棋控件的枚举常、结构、常数的定义
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：13:39:08
*******************************************************************************************************/
#if !defined(ENUMANDSTRUCTANDCONST_H)
#define ENUMANDSTRUCTANDCONST_H

#pragma once

#include "common.h"

typedef enum _ENUM_QiZi{
	RShuai = 1, //红帅
	RShi = 2,   //红仕
	RXiang = 3, //红相
	RMa = 4,    //红马
	RChe = 5,   //红车
	RPao = 6,   //红炮
	RBing = 7,  //红兵
    NoQiZi = 0, //无子
	RQi = 1,    //红棋
	BQi = -1,   //黑棋
	BShuai = -1,//黑帅
	BShi = -2,  //黑仕
	BXiang = -3,//黑相
	BMa = -4,   //黑马
	BChe = -5,  //黑车
	BPao = -6,  //黑炮
	BBing = -7  //黑兵
} ENUM_QiZi;

typedef enum _ENUM_BianMa{BianMa, JieMa} ENUM_BianMa;

#define MAX_STRING_BUFFER 128

#endif //!defined(ENUMANDSTRUCTANDCONST_H)