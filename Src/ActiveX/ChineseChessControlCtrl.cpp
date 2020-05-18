// ChineseChessControlCtrl.cpp : CChineseChessControlCtrl ActiveX 控件类的实现。

#include "pch.h"
#include "framework.h"
#include "ChineseChessControl.h"
#include "ChineseChessControlCtrl.h"
#include "ChineseChessControlPropPage.h"
#include "afxdialogex.h"

#include <atlconv.h>

//播放音频
#include <mmsystem.h>
#pragma comment(lib, "winmm")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessControlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
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

IMPLEMENT_OLECREATE_EX(CChineseChessControlCtrl, "ChineseChessControl.1.1.2",
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

	m_QiPangColor = RGB(0, 0, 0);
	m_TiShiBoxColor = RGB(0, 255, 0);

	m_QiPangStartX = m_QiPangStartY = 0;
	m_QiPangDistance = 0;

	if (m_QiPangPicture.GetSafeHandle() == NULL)
	{
		m_QiPangPicture.LoadBitmap(IDB_QIPANG);
	}

	if (m_RedShuai.GetSafeHandle() == NULL)
	{
		m_RedShuai.LoadBitmap(IDB_RSHUAI);
	}

	if (m_RedShi.GetSafeHandle() == NULL)
	{
		m_RedShi.LoadBitmap(IDB_RSHI);
	}

	if (m_RedXiang.GetSafeHandle() == NULL)
	{
		m_RedXiang.LoadBitmap(IDB_RXIANG);
	}

	if (m_RedMa.GetSafeHandle() == NULL)
	{
		m_RedMa.LoadBitmap(IDB_RMA);
	}

	if (m_RedChe.GetSafeHandle() == NULL)
	{
		m_RedChe.LoadBitmap(IDB_RCHE);
	}

	if (m_RedPao.GetSafeHandle() == NULL)
	{
		m_RedPao.LoadBitmap(IDB_RPAO);
	}

	if (m_RedBing.GetSafeHandle() == NULL)
	{
		m_RedBing.LoadBitmap(IDB_RBING);
	}


	if (m_BlackShuai.GetSafeHandle() == NULL)
	{
		m_BlackShuai.LoadBitmap(IDB_BSHUAI);
	}

	if (m_BlackShi.GetSafeHandle() == NULL)
	{
		m_BlackShi.LoadBitmap(IDB_BSHI);
	}

	if (m_BlackXiang.GetSafeHandle() == NULL)
	{
		m_BlackXiang.LoadBitmap(IDB_BXIANG);
	}

	if (m_BlackMa.GetSafeHandle() == NULL)
	{
		m_BlackMa.LoadBitmap(IDB_BMA);
	}

	if (m_BlackChe.GetSafeHandle() == NULL)
	{
		m_BlackChe.LoadBitmap(IDB_BCHE);
	}

	if (m_BlackPao.GetSafeHandle() == NULL)
	{
		m_BlackPao.LoadBitmap(IDB_BPAO);
	}

	if (m_BlackBing.GetSafeHandle() == NULL)
	{
		m_BlackBing.LoadBitmap(IDB_BBING);
	}
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

	DrawQiPang(pdc, rcBounds);   //画棋盘
}

// CChineseChessControlCtrl::DoPropExchange - 持久性支持

void CChineseChessControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	PX_Color(pPX, _T("QiPangColor"), m_QiPangColor, RGB(0, 0, 0));
	PX_Color(pPX, _T("TiShiBoxColor"), m_TiShiBoxColor, RGB(0, 255, 0));
	PX_UShort(pPX, _T("BoardLayout"), (USHORT&)m_BoardLayout, (USHORT)TopBlackAndBottomRed);
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
	InvalidateControl();
}

void CChineseChessControlCtrl::OnTiShiBoxColorChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CChineseChessControlCtrl::OnBoardLayoutChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Initial();
	SetBoardLayout(m_BoardLayout);
	SetModifiedFlag();
	InvalidateControl();
}

void CChineseChessControlCtrl::OnEnablePromptSoundChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	__super::EnablePromptSound(m_EnablePromptSound);
	SetModifiedFlag();
}

void CChineseChessControlCtrl::OnEnablePromptMessageChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	__super::EnablePromptMessage(m_EnablePromptMessage);

	SetModifiedFlag();
}

// CChineseChessControlCtrl::AboutBox - 向用户显示“关于”框

void CChineseChessControlCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_CHINESECHESSCONTROL);
	dlgAbout.DoModal();
}

VARIANT_BOOL CChineseChessControlCtrl::NextStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加调度处理程序代码
	if (__super::NextStep())
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::PreviouStep()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (__super::PreviouStep())
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::GoChess(SHORT i, SHORT j)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (__super::GoChess(i, j))
		return VARIANT_TRUE;
	return VARIANT_FALSE;
}

VARIANT_BOOL CChineseChessControlCtrl::SaveChessGame(LPCTSTR szFile)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	const char* pszFile = T2CA(szFile);
	if (__super::SaveChessGame(pszFile))
		return VARIANT_FALSE;
	return VARIANT_TRUE;
}

VARIANT_BOOL CChineseChessControlCtrl::LoadChessGame(LPCTSTR szFile)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TRACE(_T("file:%s"), szFile);
	const char *pszFile = T2CA(szFile);
	if (__super::LoadChessGame(pszFile))
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

void CChineseChessControlCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CChineseChessControlCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int i = 0, j = 0;
	ConvertCoordinate(&point.x, &point.y, &i, &j);
	TRACE(_T("point: i = %d j = %d\n"), i, j);
	TRACE(_T("CXQCtrl::OnLButtonUp的当前线程:%x\n"), ::GetCurrentThreadId());
	if (GoChess(i, j))
	{

	}
	__super::OnLButtonUp(nFlags, point);
}

void CChineseChessControlCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	SetQiPang(cx, cy);
}

//
//以上是完成 === 消息处理程序 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 虚拟函数实现 === 的函数块
//

int CChineseChessControlCtrl::onPromptSound(PROMPT_SOUND sound)
{
	LPCTSTR pId = NULL;
	switch (sound)
	{
	case JiangJun:
		pId = _T("IDW_CHECK");
		break;
	case Eat:
		pId = _T("IDW_EAT");
		break;
	case Go:
		pId = _T("IDW_GO");
		break;
	case NoGo:
		pId = _T("IDW_DEAD");
		break;
	case Select:
		pId = _T("IDW_SELECT");
		break;
	default:
		break;
	}

	PromptSound(pId);
	return 0;
}

int CChineseChessControlCtrl::onPromptMessage(CGoRule::ENUM_ReturnValue val)
{
	switch (val)
	{
	case CGoRule::BEIJIANGJUN:
		::MessageBox(GetSafeHwnd(), _T("这步不能走，否则会输棋！"), _T("被将军"), MB_OK);
		break;
	case CGoRule::JIANGDUIMIAN:
		::MessageBox(GetSafeHwnd(), _T("这步不能走，否则会输棋！"), _T("将对面"), MB_OK);
		break;
	}
	return 0;
}

int CChineseChessControlCtrl::onCleanPrompt(int i, int j)
{
	InvalidateRectage(i, j);
	return 0;
}

int CChineseChessControlCtrl::onDrawPrompt(int i, int j)
{
	InvalidateRectage(i, j);
	return 0;
}

int CChineseChessControlCtrl::onGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
	return 0;
}

//
//以上是完成 === 虚拟函数实现 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*******************************************************************************************************
函数名：InitalQiPangPosition
功  能：设置棋盘位置
参  数：
		 int width：控件窗口宽度
		 int height：控件窗口高度
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2020-5-12
时  间：11:27:12
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::SetQiPang(int width, int height)
{
	if (width > height)
	{
		m_QiPangDistance = height / 11;
		m_QiPangStartX = (width - m_QiPangDistance * 10) / 2 + m_QiPangDistance;
		m_QiPangStartY = m_QiPangDistance;
	}
	else
	{
		m_QiPangDistance = width / 10;
		m_QiPangStartX = m_QiPangDistance;
		m_QiPangStartY = (height - m_QiPangDistance * 11) / 2 + m_QiPangDistance;
	}
	return TRUE;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 辅助 === 功能的函数块
//

/*******************************************************************************************************
函数名：TransparentBlt2
功  能：画透明图
参  数：
		 HDC hdcDest：       目标DC
		 int nXOriginDest：目标X偏移
		 int nYOriginDest：目标Y偏移
		 int nWidthDest：目标宽度
		 int nHeightDest：目标高度
		 HDC hdcSrc：源DC
		 int nXOriginSrc：源X起点
		 int nYOriginSrc：源Y起点
		 int nWidthSrc：源宽度
		 int nHeightSrc：源高度
		 UINT crTransparent：透明色,COLORREF类型
返回值：无
备  注：此函数可用于 WINDOWS 98 及以上的 WINDOWS 系统。
		如果能确定是 WINDOWS2000 及以上的 WINDOWS 系统，可以使用 TransparentBlt 函数
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：19:50:00
*******************************************************************************************************/
void TransparentBlt2(HDC hdcDest,      // 目标DC
	int nXOriginDest,   // 目标X偏移
	int nYOriginDest,   // 目标Y偏移
	int nWidthDest,     // 目标宽度
	int nHeightDest,    // 目标高度
	HDC hdcSrc,         // 源DC
	int nXOriginSrc,    // 源X起点
	int nYOriginSrc,    // 源Y起点
	int nWidthSrc,      // 源宽度
	int nHeightSrc,     // 源高度
	UINT crTransparent  // 透明色,COLORREF类型
)
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest,
			hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0, 0, 0));
	SetTextColor(hImageDC, RGB(255, 255, 255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest, RGB(0xff, 0xff, 0xff));
	SetTextColor(hdcDest, RGB(0, 0, 0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);

}

/*******************************************************************************************************
函数名：PromptSound
功  能：播放声音
说  明：1、在“工程->设置->link->对象/库”中加入winmm.lib
		2、加入头文件 #include <mmsystem.h>
参  数：
		 LPCTSTR ID：声音的字符标志
返回值：如果成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：20:47:29
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::PromptSound(LPCTSTR ID)
{
	if (NULL != ID)
	{
		HINSTANCE hInstance = AfxGetInstanceHandle();
		HRSRC hr = FindResource(hInstance, ID, _T("WAVE"));
		HGLOBAL hg = LoadResource(hInstance, hr);
		LPCTSTR lp = (LPCTSTR)LockResource(hg);
		::sndPlaySound(lp, SND_MEMORY | SND_ASYNC);
		FreeResource(hg);
	}
	else
	{
		Beep(1000, 20);
	}
	return true;
}

/*******************************************************************************************************
函数名：ConvertCoordinate
功  能：坐标转换
参  数：
		 long *x：设备横坐标
		 long *y：设备纵坐标
		 int *i：棋盘横坐标[0,8]
		 int *j：棋盘纵坐标[0,9]
		 ENUM_ConvertCoordinate eCC：转换方式
		 XYToIJ:从设备坐标转换到棋盘坐标(默认值)
		 IJToXY:从棋盘坐标转换到设备坐标
返回值：返回真值。
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-24
时  间：15:01:37
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC)
{
	switch (eCC)
	{
	case XYToIJ:
		*i = (*x - m_QiPangStartX + m_QiPangDistance / 2) / m_QiPangDistance;
		*j = (*y - m_QiPangStartY + m_QiPangDistance / 2) / m_QiPangDistance;
		break;
	case IJToXY:
		*x = m_QiPangStartX + *i * m_QiPangDistance;
		*y = m_QiPangStartY + *j * m_QiPangDistance;
		break;
	}
	return true;
}

//
//以上是完成 === 辅助 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 中国象棋界面处理 === 的函数块
//

/*******************************************************************************************************
函数名：DrawQiPang
功  能：画棋盘
参  数：
		 CDC *pdc：设备上下文
		 CRect rcBounds：控件区域(包括边界)
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：17:10:23
*******************************************************************************************************/
void CChineseChessControlCtrl::DrawQiPang(CDC *pdc, CRect rcBounds)
{
	ASSERT(pdc != NULL);

	//棋盘图片
	BITMAP bitmap;
	m_QiPangPicture.GetBitmap(&bitmap);

	CDC psdc;
	psdc.CreateCompatibleDC(pdc);
	psdc.SelectObject(&m_QiPangPicture);

	pdc->StretchBlt(0, 0, rcBounds.Width(), rcBounds.Height(),
		&psdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	psdc.DeleteDC();

	int i, j;
	for (i = 0; i < 9; i++) //纵格
	{
		if (i == 0 || i == 8)
		{
			CPen Pen, *oldPen;
			Pen.CreatePen(PS_SOLID, 2, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);

			pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY);
			pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY + 9 * m_QiPangDistance);

			pdc->SelectObject(&oldPen);
		}
		else
		{
			CPen Pen, *oldPen;
			Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);

			pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY);
			pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY + 4 * m_QiPangDistance);

			pdc->MoveTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY + 5 * m_QiPangDistance);
			pdc->LineTo(m_QiPangStartX + i * m_QiPangDistance,
				m_QiPangStartY + 9 * m_QiPangDistance);

			pdc->SelectObject(&oldPen);
		}
	}

	for (i = 0; i < 10; i++)  //横格
	{
		CPen Pen, *oldPen;
		if (i == 0 || i == 9)
		{
			Pen.CreatePen(PS_SOLID, 2, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);
		}
		else
		{
			Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
			oldPen = (CPen*)pdc->SelectObject(&Pen);
		}


		pdc->MoveTo(m_QiPangStartX,
			m_QiPangStartY + i * m_QiPangDistance);
		pdc->LineTo(m_QiPangStartX + 8 * m_QiPangDistance,
			m_QiPangStartY + i * m_QiPangDistance);

		pdc->SelectObject(&oldPen);
	}

	//九宫
	CPen Pen, *oldPen;
	Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
	oldPen = (CPen*)pdc->SelectObject(&Pen);

	pdc->MoveTo(m_QiPangStartX + 3 * m_QiPangDistance,
		m_QiPangStartY);
	pdc->LineTo(m_QiPangStartX + 5 * m_QiPangDistance,
		m_QiPangStartY + 2 * m_QiPangDistance);

	pdc->MoveTo(m_QiPangStartX + 5 * m_QiPangDistance,
		m_QiPangStartY);
	pdc->LineTo(m_QiPangStartX + 3 * m_QiPangDistance,
		m_QiPangStartY + 2 * m_QiPangDistance);

	pdc->MoveTo(m_QiPangStartX + 3 * m_QiPangDistance,
		m_QiPangStartY + 7 * m_QiPangDistance);
	pdc->LineTo(m_QiPangStartX + 5 * m_QiPangDistance,
		m_QiPangStartY + 9 * m_QiPangDistance);

	pdc->MoveTo(m_QiPangStartX + 5 * m_QiPangDistance,
		m_QiPangStartY + 7 * m_QiPangDistance);
	pdc->LineTo(m_QiPangStartX + 3 * m_QiPangDistance,
		m_QiPangStartY + 9 * m_QiPangDistance);

	pdc->SelectObject(&oldPen);

	//星位
	DrawXinWei(pdc, 1, 2);
	DrawXinWei(pdc, 7, 2);
	DrawXinWei(pdc, 1, 7);
	DrawXinWei(pdc, 7, 7);
	DrawXinWei(pdc, 0, 3, Right_XinWei);
	DrawXinWei(pdc, 2, 3);
	DrawXinWei(pdc, 4, 3);
	DrawXinWei(pdc, 6, 3);
	DrawXinWei(pdc, 8, 3, Left_XinWei);
	DrawXinWei(pdc, 0, 6, Right_XinWei);
	DrawXinWei(pdc, 2, 6);
	DrawXinWei(pdc, 4, 6);
	DrawXinWei(pdc, 6, 6);
	DrawXinWei(pdc, 8, 6, Left_XinWei);

	//楚河汉界
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHU);  //楚
	DrawPicture(pdc, 7, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_HE);   //河
	DrawPicture(pdc, 6, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_HAN);  //汉
	DrawPicture(pdc, 1, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_JIE);  //界
	DrawPicture(pdc, 2, 4, &bmp, true);
	bmp.Detach();
	bmp.LoadBitmap(IDB_KL);   //KL
	DrawPicture(pdc, 4, 4, &bmp, true);

	//画棋子
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
		{
			DrawQiZi(pdc, i, j, m_ChessBoard[i][j]);
		}

	//显示提示框
    if(IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
		DrawTiShiBox(pdc, m_PreviouPositionX, m_PreviouPositionY);
	if (IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
		DrawTiShiBox(pdc, m_CurrentPositionX, m_CurrentPositionY);

}

/*******************************************************************************************************
函数名：DrawXinWei
功  能：画星位
参  数：
		 CDC *pdc：设备上下文
		 int i：星位的横坐标[0-8]
		 int j：星位的纵坐标[0-9]
		 ENUM_XINWEI xinwei：画的位置取下列值勤之一:
         XinWei:全画(默认值),
         Left_XinWei:画左边的星位
         Right_XinWei:画右边的星位
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：17:56:58
*******************************************************************************************************/
void CChineseChessControlCtrl::DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei)
{
	int d, ds;
	long x, y;

	d = m_QiPangDistance * 4 / 10;
	ds = m_QiPangDistance * 2 / 10;

	/*x = m_QiPangStartX + i * m_QiPangDistance;
	y = m_QiPangStartY + j * m_QiPangDistance;
	*/
	ConvertCoordinate(&x, &y, &i, &j, IJToXY);

	CPen Pen, *oldPen;
	Pen.CreatePen(PS_SOLID, 1, m_QiPangColor);
	oldPen = (CPen*)pdc->SelectObject(&Pen);

	if (xinwei != Left_XinWei)
	{
		pdc->MoveTo(x + ds,
			y + ds);
		pdc->LineTo(x + d,
			y + ds);

		pdc->MoveTo(x + ds,
			y - ds);
		pdc->LineTo(x + d,
			y - ds);

		pdc->MoveTo(x + ds,
			y + ds);
		pdc->LineTo(x + ds,
			y + d);

		pdc->MoveTo(x + ds,
			y - ds);
		pdc->LineTo(x + ds,
			y - d);
	}

	if (xinwei != Right_XinWei)
	{
		pdc->MoveTo(x - ds,
			y - ds);
		pdc->LineTo(x - ds,
			y - d);

		pdc->MoveTo(x - ds,
			y + ds);
		pdc->LineTo(x - ds,
			y + d);

		pdc->MoveTo(x - ds,
			y + ds);
		pdc->LineTo(x - d,
			y + ds);

		pdc->MoveTo(x - ds,
			y - ds);
		pdc->LineTo(x - d,
			y - ds);
	}
	pdc->SelectObject(&oldPen);
}

/*******************************************************************************************************
函数名：DrawTiShiBox
功  能：画提示框
参  数：
		 int i：棋盘横坐标[0-8]
		 int j：棋盘纵坐标[0-9]
返回值：成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：04-9-2
时  间：21:01:23
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::DrawTiShiBox(CDC *pdc, int i, int j)
{
	//	CClientDC dc(this);
	ASSERT(pdc != NULL);
	long m_X, m_Y, m_L = m_QiPangDistance / 2;
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 2, m_TiShiBoxColor);
	oldpen = (CPen*)pdc->SelectObject(&pen);

	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	pdc->MoveTo(m_X - m_L, m_Y - m_L);
	pdc->LineTo(m_X - m_L, m_Y - m_L / 2);

	pdc->MoveTo(m_X - m_L, m_Y - m_L);
	pdc->LineTo(m_X - m_L / 2, m_Y - m_L);

	pdc->MoveTo(m_X + m_L, m_Y + m_L);
	pdc->LineTo(m_X + m_L, m_Y + m_L / 2);

	pdc->MoveTo(m_X + m_L, m_Y + m_L);
	pdc->LineTo(m_X + m_L / 2, m_Y + m_L);

	pdc->MoveTo(m_X - m_L, m_Y + m_L);
	pdc->LineTo(m_X - m_L, m_Y + m_L / 2);

	pdc->MoveTo(m_X - m_L, m_Y + m_L);
	pdc->LineTo(m_X - m_L / 2, m_Y + m_L);

	pdc->MoveTo(m_X + m_L, m_Y - m_L);
	pdc->LineTo(m_X + m_L, m_Y - m_L / 2);

	pdc->MoveTo(m_X + m_L, m_Y - m_L);
	pdc->LineTo(m_X + m_L / 2, m_Y - m_L);


	pdc->SelectObject(oldpen);
	return true;
}

/*******************************************************************************************************
函数名：DrawQiZi
功  能：画棋子
参  数：
		 int i：棋子横坐标[0-8]
		 int j：棋子纵坐标[0-9]
		 CPiece::ENUM_QiZi eQiZi：棋子
返回值：如果成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：19:47:24
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi)
{
	ASSERT(pdc != NULL);

	CBitmap *m_QiZi = NULL;

#pragma warning( disable : 4806 )

	switch (eQiZi)
	{
	case CPiece::NoQiZi:
		return false;
	case CPiece::RShuai:
		m_QiZi = &m_RedShuai;
		break;
	case CPiece::RShi:
		m_QiZi = &m_RedShi;
		break;
	case CPiece::RXiang:
		m_QiZi = &m_RedXiang;
		break;
	case CPiece::RMa:
		m_QiZi = &m_RedMa;
		break;
	case CPiece::RChe:
		m_QiZi = &m_RedChe;
		break;
	case CPiece::RPao:
		m_QiZi = &m_RedPao;
		break;
	case CPiece::RBing:
		m_QiZi = &m_RedBing;
		break;
	case CPiece::BShuai:
		m_QiZi = &m_BlackShuai;
		break;
	case CPiece::BShi:
		m_QiZi = &m_BlackShi;
		break;
	case CPiece::BXiang:
		m_QiZi = &m_BlackXiang;
		break;
	case CPiece::BMa:
		m_QiZi = &m_BlackMa;
		break;
	case CPiece::BChe:
		m_QiZi = &m_BlackChe;
		break;
	case CPiece::BPao:
		m_QiZi = &m_BlackPao;
		break;
	case CPiece::BBing:
		m_QiZi = &m_BlackBing;
		break;
	}

#pragma warning( default : 4806 )

	if (NULL != m_QiZi)
	{
		return DrawPicture(pdc, i, j, m_QiZi);
	}
	else
	{
		return false;
	}
}


/*******************************************************************************************************
函数名：DrawPicture
功  能：画图片
参  数：
		 CDC *pdc：设备上下文
		 int i：图片位置横坐标[0-8]
		 int j：图片位置纵坐标[0-9]
		 CBitmap *pbmp：图片指针
		 BOOL CHHJKL：画楚河汉界（默认值为 false）
返回值：成功返回 true
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：18:59:53
*******************************************************************************************************/
BOOL CChineseChessControlCtrl::DrawPicture(CDC *pdc, int i, int j, CBitmap *pbmp, BOOL CHHJKL)
{
	ASSERT(pdc != NULL && pbmp != NULL);

	long m_X, m_Y;

	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	if (CHHJKL)//画楚河汉界
	{
		m_X -= m_QiPangDistance / 2;
	}
	else
	{
		m_X -= m_QiPangDistance / 2;
		m_Y -= m_QiPangDistance / 2;
	}

	//棋盘图片
	BITMAP bitmap;
	pbmp->GetBitmap(&bitmap);

	CDC psdc;
	psdc.CreateCompatibleDC(pdc);
	psdc.SelectObject(pbmp);

	TransparentBlt2(pdc->GetSafeHdc(), m_X, m_Y, m_QiPangDistance, m_QiPangDistance,
		psdc.GetSafeHdc(), 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 255, 255));


	/*------------------------------------------------------------------------
	//以下是由 ---康  林--- 删除于 2004-12-17 : 21:39:09
	//

	//用于Windows 2000 以上版本
	TransparentBlt(pdc->GetSafeHdc(), m_X, m_Y, m_QiPangDistance, m_QiPangDistance,
		   psdc.GetSafeHdc(), 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(255, 255, 255));

	//
	//以上是由 ---康  林--- 删除于 2004-12-17 : 21:39:09
	//------------------------------------------------------------------------*/

	psdc.DeleteDC();
	return true;
}

/*******************************************************************************************************
函数名：InvalidateRectage
功  能：产生无效矩形,用于删除棋子
参  数：
		 int i：棋盘横坐标[0-8]
		 int j：棋盘横坐标[0-9]
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：10:49:56
*******************************************************************************************************/
void CChineseChessControlCtrl::InvalidateRectage(int i, int j)
{
	long x, y;
	if (i >= 0 && i <= 8 && j >= 0 && j <= 9)
	{
		ConvertCoordinate(&x, &y, &i, &j, IJToXY);
		RECT rect;
		rect.top = y - m_QiPangDistance / 2 - 1;
		rect.left = x - m_QiPangDistance / 2 - 1;
		rect.bottom = y + m_QiPangDistance / 2 + 1;
		rect.right = x + m_QiPangDistance / 2 + 1;
		InvalidateControl(&rect);
	}
}

//
//以上是完成 === 中国象棋界面处理 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
