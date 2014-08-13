/*******************************************************************************************************
文件名：中国象棋控件.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2005-3-23
时  间：12:04:41

FileName：中国象棋控件.h
Compiler：Visual C++ 6.0
Author  ：KangLin
          Copyright 2005 KangLin
Date    ：2005-3-23
Time    ：12:04:41
*******************************************************************************************************/
#if !defined(AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED_)
#define AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 中国象棋控件.h : main header file for 中国象棋控件.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyApp : See 中国象棋控件.cpp for implementation.

class CMyApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED)
