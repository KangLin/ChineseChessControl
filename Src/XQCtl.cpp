// XQCtl.cpp : Implementation of the CXQCtrl ActiveX Control class.

#include "Stdafx.h"
#include "ChineseChessControl.h"
#include "XQCtl.h"
#include "XQPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXQCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXQCtrl, COleControl)
	//{{AFX_MSG_MAP(CXQCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CXQCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CXQCtrl)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "QiPangColor", m_QiPangColor, OnQiPangColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "TiShiBoxColor", m_TiShiBoxColor, OnTiShiBoxColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CXQCtrl, "QiPangLayout", m_QiPang, OnQiPangLayoutChanged, VT_I4)
	DISP_PROPERTY_EX(CXQCtrl, "QiPangPicture", GetQiPangPicture, SetQiPangPicture, VT_PICTURE)
	DISP_PROPERTY_EX(CXQCtrl, "StartSide", GetStartSide, SetStartSide, VT_I4)
	DISP_PROPERTY_EX(CXQCtrl, "CurrentSide", GetCurrentSide, SetCurrentSide, VT_I2)
	DISP_FUNCTION(CXQCtrl, "NextStep", NextStep, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "PreviouStep", PreviouStep, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "ReStart", ReStart, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "SaveChess", SaveChess, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "LoadChess", LoadChess, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "LoadChessStart", LoadChessStart, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXQCtrl, "QiPangInterconvert", QiPangInterconvert, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXQCtrl, "Walk", Walk, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXQCtrl, "InterConvertCoordinate", InterConvertCoordinate, VT_EMPTY, VTS_I2 VTS_I2 VTS_PI2 VTS_PI2)
	DISP_STOCKPROP_ENABLED()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CXQCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CXQCtrl, COleControl)
	//{{AFX_EVENT_MAP(CXQCtrl)
	EVENT_CUSTOM("MoveChess", FireMoveChess, VTS_I2  VTS_I2  VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CXQCtrl, 1)
	PROPPAGEID(CXQPropPage::guid)
END_PROPPAGEIDS(CXQCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXQCtrl, "ChineseChessControl.1.1.0",
	0x71ad322, 0x22ba, 0x45bf, 0x9e, 0x1f, 0x15, 0x4e, 0xfa, 0xf4, 0xe4, 0x2b)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CXQCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DXQ =
		{ 0xe64cbbbf, 0x1b35, 0x4334, { 0xb9, 0x7a, 0xf0, 0x42, 0x7, 0xf3, 0x83, 0xd8 } };
const IID BASED_CODE IID_DXQEvents =
		{ 0xd15120c1, 0x9b3c, 0x4e56, { 0x8f, 0x32, 0xd0, 0xac, 0xb6, 0xfc, 0x7b, 0x89 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwXQOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CXQCtrl, IDS_XQ, _dwXQOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::DoPropExchange - Persistence support

void CXQCtrl::DoPropExchange(CPropExchange* pPX)
{
	TRACE(_T("DoPropExchange-Start\n"));
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
    PX_Color(pPX, _T("QiPangColor"), m_QiPangColor, RGB(0, 0, 0));
	PX_Color(pPX, _T("TiShiBoxColor"), m_TiShiBoxColor, RGB(0, 255, 0));

	PX_Picture(pPX, _T("QiPangPicture"), m_QiPangPictureHolder);
	GetCBitmapFromCPictureHolder(&m_QiPangPictureHolder, &m_QiPangPicture);

	PX_Long(pPX, _T("StartSide"), (long&)m_WalkState, RedReadly);
    PX_Long(pPX, _T("QiPangLayout"), m_QiPang, TopRedAndBottomBlack);
	TRACE(_T("DoPropExchange-End\n"));
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::CXQCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CXQCtrl

BOOL CXQCtrl::CXQCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_XQ,
			IDB_XQ,
			afxRegApartmentThreading,
			_dwXQOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::CXQCtrl - Constructor

CXQCtrl::CXQCtrl()
{
	InitializeIIDs(&IID_DXQ, &IID_DXQEvents);
    
	m_QiPangStartX = m_QiPangStartY = 0;
	m_QiPangDistance = 0;
	m_WalkState = RedReadly;
	
	//提示框位置
	m_TiShiBoxPostion.p1.x = -1;
	m_TiShiBoxPostion.p1.y = -1;
	m_TiShiBoxPostion.p2.x = -1;
	m_TiShiBoxPostion.p2.y = -1;

	//初始化重新下棋
	m_iBuShu = -1;       //步数
	m_bFuPang = FALSE;   //复盘标志
	
	if(m_QiPangPicture.GetSafeHandle() == NULL)
	{
		m_QiPangPicture.LoadBitmap(IDB_QIPANG);
	}

	if(m_RedShuai.GetSafeHandle() == NULL)
	{
		m_RedShuai.LoadBitmap(IDB_RSHUAI);
	}

    if(m_RedShi.GetSafeHandle() == NULL)
	{
		m_RedShi.LoadBitmap(IDB_RSHI);
	}

	if(m_RedXiang.GetSafeHandle() == NULL)
	{
		m_RedXiang.LoadBitmap(IDB_RXIANG);
	}

	if(m_RedMa.GetSafeHandle() == NULL)
	{
		m_RedMa.LoadBitmap(IDB_RMA);
	}

	if(m_RedChe.GetSafeHandle() == NULL)
	{
		m_RedChe.LoadBitmap(IDB_RCHE);
	}

	if(m_RedPao.GetSafeHandle() == NULL)
	{
		m_RedPao.LoadBitmap(IDB_RPAO);
	}

	if(m_RedBing.GetSafeHandle() == NULL)
	{
		m_RedBing.LoadBitmap(IDB_RBING);
	}


	if(m_BlackShuai.GetSafeHandle() == NULL)
	{
		m_BlackShuai.LoadBitmap(IDB_BSHUAI);
	}

    if(m_BlackShi.GetSafeHandle() == NULL)
	{
		m_BlackShi.LoadBitmap(IDB_BSHI);
	}

	if(m_BlackXiang.GetSafeHandle() == NULL)
	{
		m_BlackXiang.LoadBitmap(IDB_BXIANG);
	}

	if(m_BlackMa.GetSafeHandle() == NULL)
	{
		m_BlackMa.LoadBitmap(IDB_BMA);
	}

	if(m_BlackChe.GetSafeHandle() == NULL)
	{
		m_BlackChe.LoadBitmap(IDB_BCHE);
	}

	if(m_BlackPao.GetSafeHandle() == NULL)
	{
		m_BlackPao.LoadBitmap(IDB_BPAO);
	}

	if(m_BlackBing.GetSafeHandle() == NULL)
	{
		m_BlackBing.LoadBitmap(IDB_BBING);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::~CXQCtrl - Destructor

CXQCtrl::~CXQCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

int CXQCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	TRACE(_T("CXQCtrl::OnCreate.当前的线程号:%x\n"), ::GetCurrentThreadId());

	SetInitialSize(100, 110);//设置控件初始化的大小	

	ReStart();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::OnResetState - Reset control to default state

void CXQCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::AboutBox - Display an "About" box to the user

void CXQCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_XQ);
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl::OnDraw - Drawing function

void CXQCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DrawQiPang(pdc, rcBounds);   //画棋盘
}

void CXQCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	SetQiPang(cx, cy);
	//TRACE("OnSize=%d,%d,distance=%f\n", cx,cy,m_QiPangDistance);
}

void CXQCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int i, j;
	ConvertCoordinate(&point.x, &point.y, &i, &j);
	TRACE(_T("CXQCtrl::OnLButtonUp的当前线程:%x\n"), ::GetCurrentThreadId());
	if(WalkChess(i, j))
	{
	  
	}
	
	COleControl::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CXQCtrl message handlers

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===中国象棋属性=== 的函数块
//

/*******************************************************************************************************
函数名：OnQiPangColorChanged
功  能：棋盘颜色属性通告函数
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：15:51:24
*******************************************************************************************************/
void CXQCtrl::OnQiPangColorChanged() 
{
	SetModifiedFlag();
	//重绘控件
	InvalidateControl();
}

void CXQCtrl::OnTiShiBoxColorChanged() 
{
	SetModifiedFlag();
	//重绘控件
	InvalidateControl();
}

LPPICTUREDISP CXQCtrl::GetQiPangPicture() 
{
	// TODO: Add your property handler here

	return m_QiPangPictureHolder.GetPictureDispatch();
}

void CXQCtrl::SetQiPangPicture(LPPICTUREDISP newValue) 
{
	// TODO: Add your property handler here

	m_QiPangPictureHolder.SetPictureDispatch(newValue);

	GetCBitmapFromCPictureHolder(&m_QiPangPictureHolder, &m_QiPangPicture);

	//设置修改标志
	SetModifiedFlag();
	//重绘控件
	InvalidateControl();
}

short CXQCtrl::GetCurrentSide() 
{
	return m_WalkState;
}

void CXQCtrl::SetCurrentSide(short nNewValue) 
{
	ENUM_WalkState val;
	if(nNewValue < 4 && nNewValue >= 0)
		val = (ENUM_WalkState)nNewValue;
	else
		val = BlackReadly;
	if(val == RedWalked)
		val = RedReadly;
	if(val == BlackWalked)
        val = BlackReadly;
	m_WalkState = val;
	SetModifiedFlag();
	InvalidateControl();
}

/*******************************************************************************************************
函数名：SetStartSide
功  能：谁先走棋。
参  数：
         long nNewValue：先走方
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-2
时  间：12:55:52
*******************************************************************************************************/
void CXQCtrl::SetStartSide(long nNewValue) 
{
    //if(m_WalkState == RedWalked || m_WalkState == BlackWalked)
	//	return;

	ENUM_WalkState val;
	if(nNewValue < 4 && nNewValue >= 0)
		val = (ENUM_WalkState)nNewValue;
	else
		val = BlackReadly;
	if(val == RedWalked)
		val = RedReadly;
	if(val == BlackWalked)
        val = BlackReadly;
	m_WalkState = val;
	m_FileHead.iStartSide = m_WalkState;

	SetModifiedFlag();
	//重绘控件
	InvalidateControl();
}

/*******************************************************************************************************
函数名：GetStartSide
功  能：得到开始方
参  数：无
返回值：开始方
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-2
时  间：13:05:09
*******************************************************************************************************/
long CXQCtrl::GetStartSide() 
{
	return m_FileHead.iStartSide;
}

/*******************************************************************************************************
函数名：OnQiPangLayoutChanged
功  能：棋盘布局
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-30
时  间：18:02:10
*******************************************************************************************************/
void CXQCtrl::OnQiPangLayoutChanged() 
{
	SetModifiedFlag();
	Inital();
	//重绘控件
	InvalidateControl();
}

//
//以上是完成 ===中国象棋属性=== 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===辅助=== 功能的函数块
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
void TransparentBlt2( HDC hdcDest,      // 目标DC
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
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
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
BOOL CXQCtrl::PromptSound(LPCTSTR ID)
{
	if(NULL != ID)
	{
		HINSTANCE hInstance = AfxGetInstanceHandle();
		HRSRC hr = FindResource(hInstance, ID, _T("WAVE"));
		HGLOBAL hg = LoadResource(hInstance, hr);
		LPCTSTR lp=(LPCTSTR)LockResource(hg);
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
函数名：QiZiBianMa
功  能：棋子编解码
参  数：
         int *i：棋盘横坐标[0-8]
         int *j：棋盘纵坐标[0-9]
         CPiece::ENUM_QiZi *QZ：棋子
         int *Code：棋子编码
         ENUM_BianMa：枚举常量（BianMa:编码(默认值)，JieMa：解码）
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-2
时  间：7:36:32
*******************************************************************************************************/
int CXQCtrl::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch(bianma)
	{
	case BianMa:
		*Code = (*i + *j * 10 + *QZ * 100);
		return *Code;
		break;
	case JieMa:
		*QZ =(CPiece::ENUM_QiZi) (*Code / 100);
		TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
        int v;
		v = *Code % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
	}
	return 0;
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
BOOL CXQCtrl::ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC)
{
	switch(eCC)
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

/*******************************************************************************************************
函数名：GetCBitmapFromCPictureHolder
功  能：从CPictureHolder得到CBitmap
参  数：
         CPictureHolder *ph：
         CBitmap *pb：
返回值：成功返回 true;否则,返回 false。
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：21:23:01
*******************************************************************************************************/
BOOL CXQCtrl::GetCBitmapFromCPictureHolder(CPictureHolder *ph, CBitmap *pb)
{
	ASSERT(ph != NULL && pb != NULL);

	// if picture is a bitmap
	if (PICTYPE_BITMAP == ph->GetType())
	{
		HBITMAP hBitmap = NULL;

		// get handle of the bitmap
		ph->m_pPict->get_Handle((OLE_HANDLE FAR *) &hBitmap);
		if(hBitmap != NULL) 
		{
			if(pb->GetSafeHandle() != NULL)
				pb->Detach();
			pb->Attach(hBitmap);
			return true;
		}	
	}
	return false;
}

//
//以上是完成 ===辅助=== 功能的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===中国象棋界面处理=== 的函数块
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
void CXQCtrl::DrawQiPang(CDC *pdc, CRect rcBounds)
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
	for(i = 0; i < 9; i++) //纵格
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

	for(i = 0; i < 10; i++)  //横格
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


		pdc->MoveTo(m_QiPangStartX ,
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
    for(i = 0; i < 9; i++)
		for(j = 0; j < 10; j++)
		{
			DrawQiZi(pdc, i, j, m_ChessBoard[i][j]);
		}

	//显示提示框
	CPoint point(-1, -1);
	if(m_TiShiBoxPostion.p1 != point)
		DrawTiShiBox(pdc, m_TiShiBoxPostion.p1);
	if(m_TiShiBoxPostion.p2 != point)
		DrawTiShiBox(pdc, m_TiShiBoxPostion.p2);

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
void CXQCtrl::DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei)
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
	
	if(xinwei != Left_XinWei)			
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

	if(xinwei != Right_XinWei)			
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
BOOL CXQCtrl::DrawTiShiBox(CDC *pdc, int i, int j)
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
函数名：DrawTiShiBox
功  能：画提示框
参  数：
         POINT p：提示框位置
返回值：成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：10:55:03
*******************************************************************************************************/
BOOL CXQCtrl::DrawTiShiBox(CDC *pdc, CPoint p)
{
	ASSERT(pdc != NULL);
	return DrawTiShiBox(pdc, p.x, p.y);
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
BOOL CXQCtrl::DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi)
{
	ASSERT(pdc != NULL);

    CBitmap *m_QiZi = NULL;
	
#pragma warning( disable : 4806 )

	switch(eQiZi)
	{
	case CPiece::RShuai:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedShuai : &m_BlackShuai;
		break;
	case CPiece::RShi:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedShi : &m_BlackShi;
		break;
	case CPiece::RXiang:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ?&m_RedXiang : &m_BlackXiang;
        break;
	case CPiece::RMa:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedMa : &m_BlackMa;
       	break;
	case CPiece::RChe:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedChe : &m_BlackChe;
        break;
	case CPiece::RPao:
		m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedPao : &m_BlackPao;
		break;
	case CPiece::RBing:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_RedBing : &m_BlackBing;
		break;
	case CPiece::BShuai:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackShuai : &m_RedShuai;
		break;
	case CPiece::BShi:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackShi : &m_RedShi;
		break;
	case CPiece::BXiang:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackXiang : &m_RedXiang;
	    break;
	case CPiece::BMa:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackMa : &m_RedMa;
	    break;
	case CPiece::BChe:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackChe : &m_RedChe;
		break;
	case CPiece::BPao:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackPao : &m_RedPao;
		break;
	case CPiece::BBing:
        m_QiZi = !(m_QiPang & SwapRedBetweenBlack) ? &m_BlackBing : &m_RedBing;
		break;
	}

#pragma warning( default : 4806 )

	if(NULL != m_QiZi)
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
BOOL CXQCtrl::DrawPicture(CDC *pdc, int i, int j, CBitmap *pbmp, BOOL CHHJKL)
{
	ASSERT(pdc != NULL && pbmp != NULL);

	long m_X, m_Y;

	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	if(CHHJKL)//画楚河汉界
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
void CXQCtrl::InvalidateRectage(int i, int j)
{
	long x, y;
	if(i >= 0 && i <= 8 && j >= 0 && j <= 9)
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

/*******************************************************************************************************
函数名：InvalidateRectage
功  能：产生无效矩形,用于删除棋子
参  数：
         CPoint p：棋盘坐标
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：11:20:12
*******************************************************************************************************/
void CXQCtrl::InvalidateRectage(CPoint p)
{
	InvalidateRectage(p.x, p.y);
}

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
BOOL CXQCtrl::SetQiPang(int width, int height)
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

/*******************************************************************************************************
函数名：Inital
功  能：初始化
参  数：无
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：19:49:39
*******************************************************************************************************/
BOOL CXQCtrl::Inital()
{
	//提示框位置
	m_TiShiBoxPostion.p1.x = -1;
    m_TiShiBoxPostion.p1.y = -1;
	m_TiShiBoxPostion.p2.x = -1;
    m_TiShiBoxPostion.p2.y = -1;

	CRect rect;
	if (this->GetSafeHwnd())
	{
		GetWindowRect(&rect);
		SetQiPang(rect.Width(), rect.Height());
	}

	//------------------------------------------------------------------------
	//以下是完成 ===初始化开始棋局=== 功能的语句块
	//

	//初始化空棋局
	int i, j;
	for(i = 0; i < 9; i++)
		for(j = 0; j < 10; j++)
			m_ChessBoard[i][j] = CPiece::NoQiZi;

	//设置棋盘布局,红上黑下
	if(m_QiPang & OnlyTopRed)
	{
		m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::RChe;
		m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::RMa;
		m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::RXiang;
		m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::RShi;
		m_ChessBoard[4][0] = CPiece::RShuai;
		m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::RPao;
		m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3]= m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::RBing;
	}

    if(m_QiPang & OnlyBottomBlack)
	{
		m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::BChe;
		m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::BMa;
		m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::BXiang;
		m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::BShi;
		m_ChessBoard[4][9] = CPiece::BShuai;
		m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::BPao;
		m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6]= m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::BBing;
	}

	//
	//以上是完成 ===初始化开始棋局=== 功能的语句块
	//------------------------------------------------------------------------

	return true;
}

//
//以上是完成 ===中国象棋界面处理=== 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===走棋算法=== 的函数块
//

/*******************************************************************************************************
函数名：bWalkChess
功  能：判断能否走棋
参  数：
         int i：当前下棋的位置,横坐标[0-8]
         int j：当前下棋的位置,纵坐标[0-9]
         CPiece::ENUM_QiZi qz：当前棋子
返回值：如果可以下棋返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：10:47:40
*******************************************************************************************************/
BOOL CXQCtrl::bWalkChess(int i, int j)
{
     if(i < 0 || i > 8 || j < 0 || j > 9)
	 {   //出界
		 return false;
	 }

	 switch(m_WalkState)
	 {
	 case RedReadly:
		 return CPiece::IsRedQiZi(m_ChessBoard[i][j]) ? true : false;
		 break;
	 case RedWalked:
		 //本方的棋,重新选取
		 if(CPiece::IsRedQiZi(m_ChessBoard[i][j]))
		 {
			 m_iBuShu--;//重定义棋时存在上一位置
			 m_WalkState = RedReadly;
			 return true;
		 }
		 //判断能否走棋
		 switch(m_GoRule.GoChess(i, j, m_TiShiBoxPostion.p1.x, m_TiShiBoxPostion.p1.y, m_ChessBoard))
		 {
		 case CGoRule::JIANGJUN://将军
			 PromptSound(_T("IDW_CHECK"));
			 return true;
		 case CGoRule::RETURNTRUE://可以走棋
			 m_ChessBoard[i][j] ? PromptSound(_T("IDW_EAT")) : PromptSound(_T("IDW_GO"));
			 return true;
		 case CGoRule::BEIJIANGJUN://被将
			 ::MessageBox(NULL, _T("这步棋不能走，否则你要输了。"), _T("被将军"), MB_OK );
			 return false;
		 case CGoRule::JIANGDUIMIAN://将对面
			 ::MessageBox(NULL, _T("这步棋不能走，否则你要输了。"), _T("将对面"), MB_OK );
			 return false;
		 case CGoRule::RETURNFALSE://非法走棋
		 default:
			 return false;
		 }

		 break;
	 case BlackReadly:
		 return CPiece::IsBlackQiZi(m_ChessBoard[i][j]) ? true : false;
		 break;
	 case BlackWalked:
		 //本方的棋,重新选取
		 if(CPiece::IsBlackQiZi(m_ChessBoard[i][j]))
		 {
			 m_iBuShu--;//重定义棋时存在上一位置
			 m_WalkState = BlackReadly;
			 return true;
		 }
		 //判断能否走棋
		 switch(m_GoRule.GoChess(i, j, m_TiShiBoxPostion.p1.x, m_TiShiBoxPostion.p1.y, m_ChessBoard))
		 {
		 case CGoRule::JIANGJUN://将军
			 PromptSound(_T("IDW_CHECK"));
			 return true;
		 case CGoRule::RETURNTRUE://可以走棋
			 m_ChessBoard[i][j] ? PromptSound(_T("IDW_EAT")) : PromptSound(_T("IDW_GO"));
			 return true;
		 case CGoRule::BEIJIANGJUN://被将
			 ::MessageBox(NULL, _T("这步棋不能走，否则你要输了。"), _T("被将军"), MB_OK );
			 return false;
		 case CGoRule::JIANGDUIMIAN://将对面
			 ::MessageBox(NULL, _T("这步棋不能走，否则你要输了。"), _T("将对面"), MB_OK );
			 return false;
		 case CGoRule::RETURNFALSE://非法走棋
		 default:
			 return false;
		 }

		 break;
	 }

	 return true;
}

/*******************************************************************************************************
函数名：WalkChess
功  能：走棋
参  数：
         int i：棋盘格横坐标[0-8]
         int j：棋盘格纵坐标[0-9]
         BOOL bEnvet：是否激活事件。默认为TRUE。
返回值：成功返回true，否则返回false。
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:17:56
*******************************************************************************************************/
BOOL CXQCtrl::WalkChess(int i, int j, BOOL bEnvet)
{
	int code;
	if(bWalkChess(i, j))
    { //走棋
        if(bEnvet)
        {
            FireMoveChess(i, j, m_ChessBoard[i][j]); //事件
        } //结束 if(bEnvet)
		
		QiZiBianMa(&i, &j, &m_ChessBoard[i][j], &code);
		TRACE(_T("code=%d,m_chessbord=%d\n"),code,m_ChessBoard[i][j]);
        m_iBuShu++;
        TRACE(_T("m_iBuShu=%d\n"), m_iBuShu);
		if(!m_bFuPang)
		{   //保存到棋局中
			if(m_iBuShu < m_QiJu.GetSize()) 
			{
				m_QiJu[m_iBuShu] = code;
				m_QiJu.SetSize(m_iBuShu + 1);
			}
			else//下棋
			{
				m_QiJu.Add(code);//保存到棋局中
			}
		}

		//提示框
		//DrawTiShiBox(i, j);
		switch(m_WalkState)
		{
		case RedReadly:
			PromptSound(_T("IDW_SELECT"));

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			m_TiShiBoxPostion.p2.x = -1;
			m_TiShiBoxPostion.p2.y = -1;
			InvalidateRectage(m_TiShiBoxPostion.p1);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;
				
			m_ChessBoard[i][j] = m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y];
			m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y] = CPiece::NoQiZi;

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			PromptSound(_T("IDW_SELECT"));

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			m_TiShiBoxPostion.p2.x = -1;
			m_TiShiBoxPostion.p2.y = -1;
			InvalidateRectage(m_TiShiBoxPostion.p1);
			
			m_WalkState = BlackWalked;
			break;		
		case BlackWalked:
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y];
			m_ChessBoard[m_TiShiBoxPostion.p1.x][m_TiShiBoxPostion.p1.y] = CPiece::NoQiZi;

			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			
			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else//不能走
	{
		PromptSound(NULL);
		return false;
	}
}

//
//以上是完成 ===走棋算法=== 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===中国象棋控件方法=== 的函数块
//

/*******************************************************************************************************
函数名：QiPangInterconvert
功  能：完成棋盘变换,上红的变为下红
参  数：无
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2005-6-9
时  间：13:53:44
*******************************************************************************************************/
void CXQCtrl::QiPangInterconvert() 
{
	if(m_QiPang & SwapRedBetweenBlack)
		m_QiPang = m_QiPang & ~SwapRedBetweenBlack;
	else
	    m_QiPang = m_QiPang | SwapRedBetweenBlack;
	
	//重绘控件
	InvalidateControl();
}

/*******************************************************************************************************
函数名：ReStart
功  能：重新开始下棋
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-29
时  间：19:24:07
*******************************************************************************************************/
void CXQCtrl::ReStart() 
{
	//初始化重新下棋
	m_iBuShu = -1;       //步数
	m_bFuPang = FALSE;   //复盘标志
	m_QiJu.RemoveAll();  //删除棋局
	//设置先走棋方
	if(m_WalkState == RedWalked)
		m_WalkState = RedReadly;
	if(m_WalkState == BlackWalked)
		m_WalkState = BlackReadly;

	//设置文件头
	memset(&m_FileHead, 0, sizeof(m_FileHead));	    
    m_FileHead.dwVersion = MAKEWORD(_wVerMajor, _wVerMinor); //版本
	HINSTANCE h=AfxGetInstanceHandle();
	LoadString(h, IDS_XQ, m_FileHead.szAppName, MAX_STRING_BUFFER);
	_tcscpy_s(m_FileHead.szAuthor, AUTHOR); //作者
	CTime t;
	t = CTime::GetCurrentTime();
	m_FileHead.timeStart = t.GetTime();   //开始时间
	m_FileHead.iStartSide = m_WalkState;  //先走棋方

	Inital();                             //初始化公共量

	SetModifiedFlag();
	InvalidateControl();                  //重绘控件	
}

/*******************************************************************************************************
函数名：SaveChess
功  能：保存棋局
参  数：
         LPCTSTR lpcszFileName：文件名(包含全路径)
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-30
时  间：10:16:51
*******************************************************************************************************/
BOOL CXQCtrl::SaveChess(LPCTSTR lpcszFileName) 
{
	if(m_iBuShu < 0)
		return FALSE;

    TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeWrite | CFile::modeCreate);

		m_FileHead.iBuShu = m_iBuShu;
		file.Write(&m_FileHead, sizeof(m_FileHead));
		
		for(int i = 0; i <= m_iBuShu; i++)
		{
			TCHAR buf[16];
			_stprintf_s(buf, _T("%d\n"), m_QiJu[i]);				
			file.WriteString(buf);
		}
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("保存棋局 - 打开文件错误."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	
	return TRUE;
}

/*******************************************************************************************************
函数名：LoadChess
功  能：装载棋局,为棋局结束状态
参  数：
         LPCTSTR lpcszFileName：棋局文件名(包含路径)
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-30
时  间：11:00:03
*******************************************************************************************************/
BOOL CXQCtrl::LoadChess(LPCTSTR lpcszFileName) 
{
	TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeRead);
		
		file.Read(&m_FileHead, sizeof(m_FileHead));
		if(_tcscmp(m_FileHead.szAuthor, AUTHOR))
			return FALSE;

		ReStart();//重新开始
		SetStartSide(m_FileHead.iStartSide);//谁先走棋
		CString str;
		while(file.ReadString(str))
		{
			int i, j;
			CPiece::ENUM_QiZi QZ;
			int code = _ttoi(str);
			QiZiBianMa(&i, &j, &QZ, &code, JieMa);		
			WalkChess(i, j);
		}
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("打开棋局 - 打开文件错误."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

/*******************************************************************************************************
函数名：LoadChessStart
功  能：装载棋局,并置为开始状态
说  明：如果仅复盘,则设置控件的状态为不响应:EnableWindow(FALSE);
		然后调用 NextStep() 或 PreviouStep 进行复盘.
参  数：
         LPCTSTR lpcszFileName：棋局文件名
返回值：成功返回TRUE,否则返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-30
时  间：11:03:00
*******************************************************************************************************/
BOOL CXQCtrl::LoadChessStart(LPCTSTR lpcszFileName) 
{
	TRY
	{
		CStdioFile file(lpcszFileName, CFile::modeRead);
	
		file.Read(&m_FileHead, sizeof(m_FileHead));
		if(_tcscmp(m_FileHead.szAuthor, AUTHOR))
			return FALSE;
		
		ReStart();//重新开始
		SetStartSide(m_FileHead.iStartSide);//谁先走棋
		CString str;
		while(file.ReadString(str))
		{
			m_iBuShu++;
			m_QiJu.Add(_ttoi(str));
		}
		m_iBuShu = -1;
		//m_bFuPang = TRUE; //见上面的说明
		file.Close();
	}
	CATCH(CFileException, e)
	{
		TCHAR szErr[MAX_STRING_BUFFER];
		e->GetErrorMessage(szErr, MAX_STRING_BUFFER);
		::MessageBox(NULL, szErr, _T("打开棋局 - 打开文件错误."), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	END_CATCH
	
	return TRUE;
}

/*******************************************************************************************************
函数名：NextStep
功  能：下步棋
参  数：无
返回值：走棋步数
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:19:33
*******************************************************************************************************/
long CXQCtrl::NextStep() 
{
	if(m_QiJu.GetSize() > m_iBuShu + 1)
	{
		int i, j;
		CPiece::ENUM_QiZi QZ;
		QiZiBianMa(&i, &j, &QZ, &m_QiJu[m_iBuShu + 1], JieMa);
		m_bFuPang = true;
		WalkChess(i, j);
		m_bFuPang = false;
	}
	else
	{
		PromptSound();
	}
	return m_iBuShu;//因为在WalkChess中已加一
}

/*******************************************************************************************************
函数名：PreviouStep
功  能：上步棋
参  数：无
返回值：走棋步数
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-5
时  间：10:19:51
*******************************************************************************************************/
long CXQCtrl::PreviouStep() 
{
	int i, j;
	CPiece::ENUM_QiZi QZ;
	if(m_iBuShu > 0)
	{
		switch(m_WalkState)
		{
		case RedWalked:
		case BlackWalked:
            m_iBuShu--;
            TRACE(_T("%s(%d) : m_iBuShu=%d\n"), __FILE__, __LINE__, m_iBuShu);
		case RedReadly:
		case BlackReadly:
			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
			
			QiZiBianMa(&i, &j, &QZ, &m_QiJu[m_iBuShu], JieMa);
			m_ChessBoard[i][j] = QZ;
			m_TiShiBoxPostion.p2.x = i;
			m_TiShiBoxPostion.p2.y = j;
			TRACE(_T("i=%d, j=%d, QZ=%d\n"), i, j, QZ);
			
			QiZiBianMa(&i, &j, &QZ, &m_QiJu[--m_iBuShu], JieMa);
			m_ChessBoard[i][j] = QZ;
			TRACE(_T("i=%d, j=%d, QZ=%d\n"), i, j, QZ);
			m_TiShiBoxPostion.p1.x = i;
			m_TiShiBoxPostion.p1.y = j;
			InvalidateRectage(m_TiShiBoxPostion.p1);
			InvalidateRectage(m_TiShiBoxPostion.p2);
            TRACE(_T("%s(%d) : m_iBuShu=%d\n"), __FILE__, __LINE__, m_iBuShu);

			m_iBuShu--;
			switch(m_WalkState)
			{
			case RedReadly:
			case RedWalked:
				m_WalkState = BlackReadly;
			    break;
			case BlackReadly:
			case BlackWalked:
				m_WalkState = RedReadly;
			}
			break;
		}
	}
	else
	{
		PromptSound();
		return 0;
	}
	return m_iBuShu;
}

/*******************************************************************************************************
函数名：InterConvertCoordinate
描  述：把棋子坐标转换成对方位置的坐标,主要用于网络中把对方传过来的位置改为对方位置
参  数：
         short x：源坐标x
         short y：源坐标y
         short FAR* pi：目的坐标x
         short FAR* pj：目的坐标y
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-9 14:18:30
*******************************************************************************************************/
void CXQCtrl::InterConvertCoordinate(short x, short y, short FAR* pi, short FAR* pj) 
{
	 *pi = 8 - x;
	 *pj = 9 - y;
}

/*******************************************************************************************************
函数名：Walk
功  能：走棋
参  数：
         short i：横坐标
         short j：纵坐标
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-6-9
时  间：14:25:34
*******************************************************************************************************/
BOOL CXQCtrl::Walk(short i, short j) 
{
    if(WalkChess(i, j, FALSE))
	{
	 	return TRUE; 
	}
	return FALSE;
}

//
//以上是完成 ===中国象棋控件方法=== 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
