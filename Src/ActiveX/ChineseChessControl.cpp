// ChineseChessControl.cpp: CChineseChessControlApp 和 DLL 注册的实现。

#include "pch.h"
#include "../MFC/framework.h"
#include "ChineseChessControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChineseChessControlApp theApp;

const GUID CDECL _tlid = {0x340162b7,0x44f0,0x440b,{0x9a,0xd9,0x94,0x84,0x3a,0x28,0x65,0xd0}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CChineseChessControlApp::InitInstance - DLL 初始化

BOOL CChineseChessControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
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
