// ChineseChessActiveX.cpp: CChineseChessActiveXApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "ChineseChessActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChineseChessActiveXApp theApp;

const GUID CDECL _tlid = {0x80e92be0,0xa67b,0x421b,{0x8e,0xf7,0x8f,0x42,0x41,0x48,0x80,0xc0}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

extern bool ChineseChessViewNewDynLinkLibrary();

// CChineseChessActiveXApp::InitInstance - DLL ��ʼ��

BOOL CChineseChessActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		ChineseChessViewNewDynLinkLibrary();
	}

	return bInit;
}



// CChineseChessActiveXApp::ExitInstance - DLL ��ֹ

int CChineseChessActiveXApp::ExitInstance()
{
	// TODO:  �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
