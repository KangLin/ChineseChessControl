// ChineseChessControlCtrl.cpp : CChineseChessControlCtrl ActiveX 控件类的实现。

#include "pch.h"
#include "framework.h"
#include "ChineseChessControl.h"
#include "ChineseChessControlCtrl.h"
#include "ChineseChessControlPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessControlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CChineseChessControlCtrl, COleControl)
	DISP_FUNCTION_ID(CChineseChessControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
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

IMPLEMENT_OLECREATE_EX(CChineseChessControlCtrl, "ChineseChessControlCtrl.1.1.1",
	0x23ac49d1,0xf4fe,0x4ab0,0xb5,0xa3,0xbb,0x3c,0xb2,0x2d,0xfe,0xd0)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CChineseChessControlCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DChineseChessControl = {0xc66fbdae,0xfb51,0x4fb8,{0xb6,0xbc,0xcd,0x2c,0xbe,0x46,0x1b,0xb7}};
const IID IID_DChineseChessControlEvents = {0x6757238f,0x9836,0x4b8a,{0x9c,0x13,0x0a,0xcc,0x7d,0x66,0x07,0xb5}};

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
	// TODO:  在此初始化控件的实例数据。
}

// CChineseChessControlCtrl::~CChineseChessControlCtrl - 析构函数

CChineseChessControlCtrl::~CChineseChessControlCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CChineseChessControlCtrl::OnDraw - 绘图函数

void CChineseChessControlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CChineseChessControlCtrl::DoPropExchange - 持久性支持

void CChineseChessControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CChineseChessControlCtrl::OnResetState - 将控件重置为默认状态

void CChineseChessControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CChineseChessControlCtrl::AboutBox - 向用户显示“关于”框

void CChineseChessControlCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_CHINESECHESSCONTROL);
	dlgAbout.DoModal();
}


// CChineseChessControlCtrl 消息处理程序
