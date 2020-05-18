// CDChineseChessControl.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDChineseChessControl

class CDChineseChessControl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDChineseChessControl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x23AC49D1, 0xF4FE, 0x4AB0, { 0xB5, 0xA3, 0xBB, 0x3C, 0xB2, 0x2D, 0xFE, 0xD0 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:

// 操作
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL GoChess(short i, short j)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, i, j);
		return result;
	}
	BOOL SaveChessGame(LPCTSTR szFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, szFile);
		return result;
	}
	BOOL LoadChessGame(LPCTSTR szFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, szFile);
		return result;
	}
	BOOL NextStep()
	{
		BOOL result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL PreviouStep()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}


};
