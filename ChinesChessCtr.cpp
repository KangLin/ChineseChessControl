// 中国象棋控件.cpp : Implementation of CMyApp and DLL registration.

#include "stdafx.h"
#include "ChinesChessCtr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMyApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xf21f4040, 0x9ee2, 0x42ec, { 0x91, 0, 0x9d, 0x2f, 0x79, 0x23, 0xfc, 0x38 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - DLL initialization

BOOL CMyApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
		TRACE(_T("CXQApp::InitInstance.\n"));
		if (!AfxSocketInit())//初始化WinSocket
		{
			AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
			return FALSE;
		}
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CMyApp::ExitInstance - DLL termination

int CMyApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
