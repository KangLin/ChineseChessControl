// Chess.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CChess

class CChess : public CWnd
{
protected:
	DECLARE_DYNCREATE(CChess)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x71AD322, 0x22BA, 0x45BF, { 0x9E, 0x1F, 0x15, 0x4E, 0xFA, 0xF4, 0xE4, 0x2B } };
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

	long NextStep()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long PreviouStep()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void ReStart()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	signed char SaveChess(LPCTSTR lpcszFileName)
	{
		signed char result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I1, (void*)&result, parms, lpcszFileName);
		return result;
	}
	signed char LoadChess(LPCTSTR lpcszFileName)
	{
		signed char result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I1, (void*)&result, parms, lpcszFileName);
		return result;
	}
	signed char LoadChessStart(LPCTSTR lpcszFileName)
	{
		signed char result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I1, (void*)&result, parms, lpcszFileName);
		return result;
	}
	void QiPangInterconvert()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	signed char Walk(short i, short j)
	{
		signed char result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I1, (void*)&result, parms, i, j);
		return result;
	}
	void InterConvertCoordinate(short x, short y, short * pi, short * pj)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_PI2 VTS_PI2 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, pi, pj);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}


};
