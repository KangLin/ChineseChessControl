// ChineseChessControl.cpp: CChineseChessControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "ChineseChessControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChineseChessControlApp theApp;

const GUID CDECL _tlid = {0x80e92be0,0xa67b,0x421b,{0x8e,0xf7,0x8f,0x42,0x41,0x48,0x80,0xc0}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

extern bool NewDynLinkLibrary();

// CChineseChessControlApp::InitInstance - DLL 初始化

BOOL CChineseChessControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
		NewDynLinkLibrary();
	}

	return bInit;
}



// CChineseChessControlApp::ExitInstance - DLL 终止

int CChineseChessControlApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
