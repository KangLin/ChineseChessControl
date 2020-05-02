#if !defined(AFX_CHINESECHESSCTR_H__89039692_0185_487A_B9F9_8BDCC3CB20D1__INCLUDED_)
#define AFX_CHINESECHESSCTR_H__89039692_0185_487A_B9F9_8BDCC3CB20D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ChineseChessCtr.h : main header file for CHINESECHESSCTR.DLL

#if !defined( __AFXCTL_H__ )
#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChineseChessCtrApp : See ChineseChessCtr.cpp for implementation.

class CChineseChessCtrApp : public COleControlModule
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

#endif // !defined(AFX_CHINESECHESSCTR_H__89039692_0185_487A_B9F9_8BDCC3CB20D1__INCLUDED)
