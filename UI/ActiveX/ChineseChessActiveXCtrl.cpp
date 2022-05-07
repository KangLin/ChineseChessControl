// ChineseChessActiveXCtrl.cpp : CChineseChessActiveXCtrl ActiveX �ؼ����ʵ�֡�

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

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CChineseChessActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
//	ON_WM_KEYUP()
//	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// ����ӳ��

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

// �¼�ӳ��

BEGIN_EVENT_MAP(CChineseChessActiveXCtrl, COleControl)
	EVENT_CUSTOM_ID("EventGoChess", eventidEventGoChess, EventGoChess, VTS_I2 VTS_I2 VTS_I4)
END_EVENT_MAP()

// ����ҳ

// TODO: ������Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CChineseChessActiveXCtrl, 1)
	PROPPAGEID(CChineseChessActiveXPropPage::guid)
END_PROPPAGEIDS(CChineseChessActiveXCtrl)

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CChineseChessActiveXCtrl, "ChineseChessActiveX.2.0.4",
	0xe4e060cb,0xa3aa,0x4278,0xb1,0xed,0xce,0x50,0x20,0xc4,0x2e,0xc7)

// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CChineseChessActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)

// �ӿ� ID

const IID IID_DChineseChessActiveX = {0x7192fb6d,0x7455,0x4da8,{0xb3,0xac,0x64,0x5d,0xd6,0x05,0x57,0xf3}};
const IID IID_DChineseChessActiveXEvents = {0x0850de98,0xfc76,0x4b94,{0x9b,0xbe,0xe2,0xe5,0x9e,0x0f,0xe0,0xea}};

// �ؼ�������Ϣ

static const DWORD _dwChineseChessActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CChineseChessActiveXCtrl, IDS_CHINESECHESSACTIVEX, _dwChineseChessActiveXOleMisc)

// CChineseChessActiveXCtrl::CChineseChessActiveXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CChineseChessActiveXCtrl ��ϵͳע�����

BOOL CChineseChessActiveXCtrl::CChineseChessActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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

// CChineseChessActiveXCtrl::CChineseChessActiveXCtrl - ���캯��
CChineseChessActiveXCtrl::CChineseChessActiveXCtrl()
{
	InitializeIIDs(&IID_DChineseChessActiveX, &IID_DChineseChessActiveXEvents);

	m_pChess = NULL;
	m_pHandler = new CChineseChessActiveXHandler(this);
}

// CChineseChessActiveXCtrl::~CChineseChessActiveXCtrl - ��������

CChineseChessActiveXCtrl::~CChineseChessActiveXCtrl()
{
	if (m_pHandler)
		delete m_pHandler;

}

// CChineseChessActiveXCtrl::DoPropExchange - �־���֧��

void CChineseChessActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}


// CChineseChessActiveXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CChineseChessActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO:  �ڴ��������������ؼ�״̬��
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� === ����ӳ�� === �ĺ�����
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

// CChineseChessActiveXCtrl::AboutBox - ���û���ʾ�����ڡ���

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
//��������� === ����ӳ�� === �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� === ��Ϣ������� === �ĺ�����
//

int CChineseChessActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
//��������� === ��Ϣ������� === �ĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int CChineseChessActiveXHandler::OnGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
	if(m_pActiveX)
		m_pActiveX->EventGoChess(i, j, chess);
	return 0;
}