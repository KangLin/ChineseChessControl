// ChineseChessActiveXCtrl.cpp : CChineseChessActiveXCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "ChineseChessActiveX.h"
#include "ChineseChessActiveXCtrl.h"
#include "ChineseChessActiveXPropPage.h"
#include "afxdialogex.h"

#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessActiveXCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
//	ON_WM_KEYUP()
//	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CChineseChessActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "QiPangColor", dispidQiPangColor, GetQiPangColor, SetQiPangColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "TiShiBoxColor", dispidTiShiBoxColor, GetTiShiBoxColor, SetTiShiBoxColor, VT_COLOR)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "BoardLayout", dispidBoardLayout, GetBoardLayout, SetBoardLayout, VT_I2)

	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "RedName", dispidRedName, GetRedName, SetRedName, VT_BSTR)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "BlackName", dispidBlackName, GetBlackName, SetBlackName, VT_BSTR)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "StartTime", dispidStartTime, GetStartTime, SetStartTime, VT_I4)
	DISP_PROPERTY_EX_ID(CChineseChessActiveXCtrl, "EndTime", dispidEndTime, GetEndTime, SetEndTime, VT_I4)

	DISP_PROPERTY_NOTIFY_ID(CChineseChessActiveXCtrl, "EnablePromptSound", dispidEnablePromptSound, m_EnablePromptSound, OnEnablePromptSoundChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessActiveXCtrl, "EnablePromptMessage", dispidEnablePromptMessage, m_EnablePromptMessage, OnEnablePromptMessageChanged, VT_BOOL)

	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "NextStep", dispidNextStep, NextStep, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "PreviouStep", dispidPreviouStep, PreviouStep, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "GoChess", dispidGoChess, GoChess, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "SaveChessGame", dispidSaveChessGame, SaveChessGame, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "LoadChessGame", dispidLoadChessGame, LoadChessGame, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "AddGameTag", dispidAddGameTag, AddGameTag, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CChineseChessActiveXCtrl, "GetgameTag", dispidGetgameTag, GetgameTag, VT_BSTR, VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CChineseChessActiveXCtrl, COleControl)
	EVENT_CUSTOM_ID("EventGoChess", eventidEventGoChess, EventGoChess, VTS_I2 VTS_I2 VTS_I4)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CChineseChessActiveXCtrl, 1)
	PROPPAGEID(CChineseChessActiveXPropPage::guid)
END_PROPPAGEIDS(CChineseChessActiveXCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CChineseChessActiveXCtrl, "ChineseChessActiveX.2.0.4",
	0xe4e060cb,0xa3aa,0x4278,0xb1,0xed,0xce,0x50,0x20,0xc4,0x2e,0xc7)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CChineseChessActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DChineseChessActiveX = {0x7192fb6d,0x7455,0x4da8,{0xb3,0xac,0x64,0x5d,0xd6,0x05,0x57,0xf3}};
const IID IID_DChineseChessActiveXEvents = {0x0850de98,0xfc76,0x4b94,{0x9b,0xbe,0xe2,0xe5,0x9e,0x0f,0xe0,0xea}};

// 控件类型信息

static const DWORD _dwChineseChessActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CChineseChessActiveXCtrl, IDS_CHINESECHESSACTIVEX, _dwChineseChessActiveXOleMisc)

// CChineseChessActiveXCtrl::CChineseChessActiveXCtrlFactory::UpdateRegistry -
// 添加或移除 CChineseChessActiveXCtrl 的系统注册表项

BOOL CChineseChessActiveXCtrl::CChineseChessActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CHINESECHESSACTIVEX,
			IDB_CHINESECHESSACTIVEX,
			afxRegApartmentThreading,
			_dwChineseChessActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// CChineseChessActiveXCtrl::CChineseChessActiveXCtrl - 构造函数
CChineseChessActiveXCtrl::CChineseChessActiveXCtrl()
{
	InitializeIIDs(&IID_DChineseChessActiveX, &IID_DChineseChessActiveXEvents);

	m_pChess = NULL;
	m_pHandler = new CChineseChessActiveXHandler(this);
}

// CChineseChessActiveXCtrl::~CChineseChessActiveXCtrl - 析构函数

CChineseChessActiveXCtrl::~CChineseChessActiveXCtrl()
{
	if (m_pHandler)
		delete m_pHandler;

}

// CChineseChessActiveXCtrl::DoPropExchange - 持久性支持

void CChineseChessActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CChineseChessActiveXCtrl::OnResetState - 将控件重置为默认状态

void CChineseChessActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 调度映射 === 的函数块
//

void CChineseChessActiveXCtrl::SetQiPangColor(OLE_COLOR val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
	{
		m_pChess->SetQiPangColor(val);
	}
	SetModifiedFlag();
}

OLE_COLOR CChineseChessActiveXCtrl::GetQiPangColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		return m_pChess->GetQiPangColor();
	return 0;
}

void CChineseChessActiveXCtrl::SetTiShiBoxColor(OLE_COLOR val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SetTiShiBoxColor(val);
	SetModifiedFlag();
}

OLE_COLOR CChineseChessActiveXCtrl::GetTiShiBoxColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		return m_pChess->GetTiShiBoxColor();
	return 0;
}

SHORT CChineseChessActiveXCtrl::GetBoardLayout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		return m_pChess->GetBoardLayout();
	return 0;
}
void CChineseChessActiveXCtrl::SetBoardLayout(SHORT val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
	{
		m_pChess->SetBoardLayout((CChineseChess::ENUM_BoardLayout) val);
		m_pChess->Invalidate();
	}
	SetModifiedFlag();
	InvalidateControl();
}

void CChineseChessActiveXCtrl::OnEnablePromptSoundChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->EnablePromptSound(m_EnablePromptSound);
	SetModifiedFlag();
}

void CChineseChessActiveXCtrl::OnEnablePromptMessageChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess)
		m_pChess->EnablePromptMessage(m_EnablePromptMessage);

	SetModifiedFlag();
}

BSTR CChineseChessActiveXCtrl::GetRedName()
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	if (m_pChess && m_pChess->GetSafeHwnd())
		strResult = A2CT(m_pChess->GetRedName().c_str());

	return strResult.AllocSysString();
}

void CChineseChessActiveXCtrl::SetRedName(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SetRedName(newVal);
	SetModifiedFlag();
}

BSTR CChineseChessActiveXCtrl::GetBlackName()
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	if (m_pChess && m_pChess->GetSafeHwnd())
		strResult = A2CT(m_pChess->GetBlackName().c_str());

	return strResult.AllocSysString();
}

void CChineseChessActiveXCtrl::SetBlackName(LPCTSTR val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SetBlackName(val);
	SetModifiedFlag();
}

LONG CChineseChessActiveXCtrl::GetStartTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess && m_pChess->GetSafeHwnd())
		return m_pChess->GetStartTime();

	return 0;
}

void CChineseChessActiveXCtrl::SetStartTime(LONG val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SetStartTime(val);

	SetModifiedFlag();
}

LONG CChineseChessActiveXCtrl::GetEndTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess && m_pChess->GetSafeHwnd())
		return m_pChess->GetEndTime();

	return 0;	
}

void CChineseChessActiveXCtrl::SetEndTime(LONG val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SetEndTime(val);

	SetModifiedFlag();
}

// CChineseChessActiveXCtrl::AboutBox - 向用户显示“关于”框

void CChineseChessActiveXCtrl::AboutBox()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->AboutBox();
}

VARIANT_BOOL CChineseChessActiveXCtrl::NextStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->NextStep();
	if (nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessActiveXCtrl::PreviouStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
		nRet = m_pChess->PreviouStep();
	if(nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessActiveXCtrl::GoChess(SHORT i, SHORT j)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
		nRet = m_pChess->GoChess(i, j);
	if(nRet)
		return VARIANT_TRUE;
	return VARIANT_FALSE;
}

VARIANT_BOOL CChineseChessActiveXCtrl::SaveChessGame(LPCTSTR szFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->SaveChessGame(szFile);
	if(nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessActiveXCtrl::LoadChessGame(LPCTSTR szFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
	{
		nRet = m_pChess->LoadChessGame(szFile);
	}
	if(nRet)
		return VARIANT_FALSE;

	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessActiveXCtrl::AddGameTag(LPCTSTR szTag, LPCTSTR szVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess && m_pChess->GetSafeHwnd())
	{
		nRet = m_pChess->AddGameTag(szTag, szVal);
	}
	if (nRet)
		return VARIANT_FALSE;

	return VARIANT_TRUE;
}

BSTR CChineseChessActiveXCtrl::GetgameTag(LPCTSTR szTag)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	if (m_pChess && m_pChess->GetSafeHwnd())
		strResult = m_pChess->GetGameTag(szTag);

	return strResult.AllocSysString();
}

//
//以上是完成 === 调度映射 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 消息处理程序 === 的函数块
//

int CChineseChessActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pChess = new CChineseChessView();
	CRect rect;
	GetClientRect(rect);
	m_pChess->Create(NULL, _T("Chinese chess"), WS_CHILD, rect, this, IDV_CHINESE_CHESS);
	m_pChess->ShowWindow(SW_SHOW);

	m_pChess->SetChineseChessHandler(m_pHandler);
	return 0;
}

void CChineseChessActiveXCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->MoveWindow(0, 0, cx, cy);
		
}

//
//以上是完成 === 消息处理程序 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int CChineseChessActiveXHandler::OnGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
	if(m_pActiveX)
		m_pActiveX->EventGoChess(i, j, chess);
	return 0;
}