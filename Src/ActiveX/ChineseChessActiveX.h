#pragma once

// ChineseChessActiveX.h: ChineseChessActiveX.DLL 的主标头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CChineseChessActiveXApp: 请参阅 ChineseChessActiveX.cpp 了解实现。

class CChineseChessActiveXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

