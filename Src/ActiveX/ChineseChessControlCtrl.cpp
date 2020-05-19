// ChineseChessControlCtrl.cpp : CChineseChessControlCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "ChineseChessControl.h"
#include "ChineseChessControlCtrl.h"
#include "ChineseChessControlPropPage.h"
#include "afxdialogex.h"

#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessControlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
//	ON_WM_KEYUP()
//	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CChineseChessControlCtrl, COleControl)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessControlCtrl, "QiPangColor", dispidQiPangColor, m_QiPangColor, OnQiPangColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessControlCtrl, "TiShiBoxColor", dispidTiShiBoxColor, m_TiShiBoxColor, OnTiShiBoxColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessControlCtrl, "BoardLayout", dispidBoardLayout, m_BoardLayout, OnBoardLayoutChanged, VT_I2)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "NextStep", dispidNextStep, NextStep, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "PreviouStep", dispidPreviouStep, PreviouStep, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "GoChess", dispidGoChess, GoChess, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "SaveChessGame", dispidSaveChessGame, SaveChessGame, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "LoadChessGame", dispidLoadChessGame, LoadChessGame, VT_BOOL, VTS_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessControlCtrl, "EnablePromptSound", dispidEnablePromptSound, m_EnablePromptSound, OnEnablePromptSoundChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY_ID(CChineseChessControlCtrl, "EnablePromptMessage", dispidEnablePromptMessage, m_EnablePromptMessage, OnEnablePromptMessageChanged, VT_BOOL)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CChineseChessControlCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CChineseChessControlCtrl, 1)
	PROPPAGEID(CChineseChessControlPropPage::guid)
END_PROPPAGEIDS(CChineseChessControlCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CChineseChessControlCtrl, "ChineseChessControlCtrl.1.0.0",
	0xe4e060cb,0xa3aa,0x4278,0xb1,0xed,0xce,0x50,0x20,0xc4,0x2e,0xc7)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CChineseChessControlCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DChineseChessControl = {0x7192fb6d,0x7455,0x4da8,{0xb3,0xac,0x64,0x5d,0xd6,0x05,0x57,0xf3}};
const IID IID_DChineseChessControlEvents = {0x0850de98,0xfc76,0x4b94,{0x9b,0xbe,0xe2,0xe5,0x9e,0x0f,0xe0,0xea}};

// 控件类型信息

static const DWORD _dwChineseChessControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CChineseChessControlCtrl, IDS_CHINESECHESSCONTROL, _dwChineseChessControlOleMisc)

// CChineseChessControlCtrl::CChineseChessControlCtrlFactory::UpdateRegistry -
// 添加或移除 CChineseChessControlCtrl 的系统注册表项

BOOL CChineseChessControlCtrl::CChineseChessControlCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_CHINESECHESSCONTROL,
			IDB_CHINESECHESSCONTROL,
			afxRegApartmentThreading,
			_dwChineseChessControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CChineseChessControlCtrl::CChineseChessControlCtrl - 构造函数

CChineseChessControlCtrl::CChineseChessControlCtrl()
{
	InitializeIIDs(&IID_DChineseChessControl, &IID_DChineseChessControlEvents);

	m_pChess = NULL;
}

// CChineseChessControlCtrl::~CChineseChessControlCtrl - 析构函数

CChineseChessControlCtrl::~CChineseChessControlCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CChineseChessControlCtrl::DoPropExchange - 持久性支持

void CChineseChessControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	PX_Color(pPX, _T("QiPangColor"), m_QiPangColor, RGB(0, 0, 0));
	PX_Color(pPX, _T("TiShiBoxColor"), m_TiShiBoxColor, RGB(0, 255, 0));
	PX_UShort(pPX, _T("BoardLayout"), (USHORT&)m_BoardLayout, (USHORT)CChineseChess::TopBlackAndBottomRed);
}


// CChineseChessControlCtrl::OnResetState - 将控件重置为默认状态

void CChineseChessControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 调度映射 === 的函数块
//

void CChineseChessControlCtrl::OnQiPangColorChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加属性处理程序代码
	TRACE(_T("CChineseChessControlCtrl::OnQiPangColorChanged()"));
	SetModifiedFlag();
}

void CChineseChessControlCtrl::OnTiShiBoxColorChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
}

void CChineseChessControlCtrl::OnBoardLayoutChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(m_pChess)
		m_pChess->SetBoardLayout(m_BoardLayout);
	SetModifiedFlag();
}

void CChineseChessControlCtrl::OnEnablePromptSoundChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pChess)
		m_pChess->EnablePromptSound(m_EnablePromptSound);
	SetModifiedFlag();
}

void CChineseChessControlCtrl::OnEnablePromptMessageChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pChess)
		m_pChess->EnablePromptMessage(m_EnablePromptMessage);

	SetModifiedFlag();
}

// CChineseChessControlCtrl::AboutBox - 向用户显示“关于”框

void CChineseChessControlCtrl::AboutBox()
{
	//CDialogEx dlgAbout(IDD_ABOUTBOX_CHINESECHESSCONTROL);
	//dlgAbout.DoModal();
}

VARIANT_BOOL CChineseChessControlCtrl::NextStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess)
		m_pChess->NextStep();
	if (nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::PreviouStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess)
		nRet = m_pChess->PreviouStep();
	if(nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::GoChess(SHORT i, SHORT j)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = 0;
	if (m_pChess)
		nRet = GoChess(i, j);
	if(nRet)
		return VARIANT_TRUE;
	return VARIANT_FALSE;
}

VARIANT_BOOL CChineseChessControlCtrl::SaveChessGame(LPCTSTR szFile)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	const char* pszFile = T2CA(szFile);
	int nRet = 0;
	if (m_pChess)
		m_pChess->SaveChessGame(pszFile);
	if(nRet)
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::LoadChessGame(LPCTSTR szFile)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TRACE(_T("file:%s"), szFile);
	const char *pszFile = T2CA(szFile);
	int nRet = 0;
	if (m_pChess)
	{
		nRet = m_pChess->LoadChessGame(pszFile);
		m_pChess->Invalidate();
	}
	if(nRet)
		return VARIANT_FALSE;
	InvalidateControl();
	return VARIANT_TRUE;
}

//
//以上是完成 === 调度映射 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 消息处理程序 === 的函数块
//

int CChineseChessControlCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pChess = new CChineseChessView();
	CRect rect;
	GetClientRect(rect);
	m_pChess->Create(NULL, _T("Chinese chess"), WS_CHILD, rect, this, IDV_CHINESE_CHESS);
	m_pChess->ShowWindow(SW_SHOW);
	return 0;
}

void CChineseChessControlCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (m_pChess && m_pChess->GetSafeHwnd())
		m_pChess->MoveWindow(0, 0, cx, cy);
		
}

//
//以上是完成 === 消息处理程序 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
