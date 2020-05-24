#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CChess 包装器类

class CChess : public CWnd
{
protected:
	DECLARE_DYNCREATE(CChess)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE4E060CB, 0xA3AA, 0x4278, { 0xB1, 0xED, 0xCE, 0x50, 0x20, 0xC4, 0x2E, 0xC7 } };
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
enum
{
    NoQi = 0,
    OnlyTopBlack = 1,
    OnlyBottomRed = 2,
    SwapRedBetweenBlack = 4,
    OnlyTopRed = 5,
    OnlyBottomBlack = 6,
    TopBlackAndBottomRed = 3,
    TopRedAndBottomBlack = 7
}_ENUM_BoardLayout;
enum
{
    RShuai = 1,
    RShi = 2,
    RXiang = 3,
    RMa = 4,
    RChe = 5,
    RPao = 6,
    RBing = 7,
    NoQiZi = 0,
    BShuai = 9,
    BShi = 10,
    BXiang = 11,
    BMa = 12,
    BChe = 13,
    BPao = 14,
    BBing = 15
}_ENUM_QiZi;


// 操作
public:

// _DChineseChessActiveX

// Functions
//

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

// Properties
//

unsigned long GetQiPangColor()
{
	unsigned long result;
	GetProperty(0x1, VT_UI4, (void*)&result);
	return result;
}
void SetQiPangColor(unsigned long propVal)
{
	SetProperty(0x1, VT_UI4, propVal);
}
unsigned long GetTiShiBoxColor()
{
	unsigned long result;
	GetProperty(0x2, VT_UI4, (void*)&result);
	return result;
}
void SetTiShiBoxColor(unsigned long propVal)
{
	SetProperty(0x2, VT_UI4, propVal);
}
long GetBoardLayout()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}
void SetBoardLayout(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}
BOOL GetEnablePromptSound()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}
void SetEnablePromptSound(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}
BOOL GetEnablePromptMessage()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}
void SetEnablePromptMessage(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}
CString GetRedName()
{
	CString result;
	GetProperty(0xb, VT_BSTR, (void*)&result);
	return result;
}
void SetRedName(CString propVal)
{
	SetProperty(0xb, VT_BSTR, propVal);
}
CString GetBlackName()
{
	CString result;
	GetProperty(0xc, VT_BSTR, (void*)&result);
	return result;
}
void SetBlackName(CString propVal)
{
	SetProperty(0xc, VT_BSTR, propVal);
}
unsigned long GetStartTime()
{
	unsigned long result;
	GetProperty(0xd, VT_UI4, (void*)&result);
	return result;
}
void SetStartTime(unsigned long propVal)
{
	SetProperty(0xd, VT_UI4, propVal);
}
unsigned long GetEndTime()
{
	unsigned long result;
	GetProperty(0xe, VT_UI4, (void*)&result);
	return result;
}
void SetEndTime(unsigned long propVal)
{
	SetProperty(0xe, VT_UI4, propVal);
}


};
