﻿// 实现文件
//
#include "framework.h"
#include <afxdialogex.h>
#include "Resource.h"       // 主符号

#include <atlconv.h>
#include "ChineseChessView.h"

//播放音频
#include <mmsystem.h>
#pragma comment(lib, "winmm")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// CChineseChessView

IMPLEMENT_DYNAMIC(CChineseChessView, CView)

CChineseChessView::CChineseChessView()
{
    m_pGoChessHandler = nullptr;
    
    m_QiPangColor = RGB(0, 0, 0);
    m_TiShiBoxColor = RGB(0, 255, 0);
    
    m_QiPangStartX = m_QiPangStartY = 0;
    m_QiPangDistance = 0;

	if (m_Chu.GetSafeHandle() == NULL)
		m_Chu.LoadBitmap(IDB_CHU);  //楚
	if (m_He.GetSafeHandle() == NULL)
		m_He.LoadBitmap(IDB_HE);   //河
	if (m_Han.GetSafeHandle() == NULL)
		m_Han.LoadBitmap(IDB_HAN);  //汉
	if (m_Jie.GetSafeHandle() == NULL)
		m_Jie.LoadBitmap(IDB_JIE);  //界
	if (m_Copyright.GetSafeHandle() == NULL)
		m_Copyright.LoadBitmap(IDB_KL);   //KL

#ifdef CHINESE_CHESS_USE_PNG
	LoadImageFromResource(&m_QiPangPicture, _T("IDJ_QIPANG"), _T("JPG"));
	LoadImageFromResource(&m_RedShuai, IDP_RSHUAI);
	LoadImageFromResource(&m_RedShi, IDP_RSHI);
	LoadImageFromResource(&m_RedXiang, IDP_RXIANG);
	LoadImageFromResource(&m_RedMa, IDP_RMA);
	LoadImageFromResource(&m_RedChe, IDP_RJU);
	LoadImageFromResource(&m_RedPao, IDP_RPAO);
	LoadImageFromResource(&m_RedBing, IDP_RBING);

	LoadImageFromResource(&m_BlackShuai, IDP_BJIANG);
	LoadImageFromResource(&m_BlackShi, IDP_BSHI);
	LoadImageFromResource(&m_BlackXiang, IDP_BXIANG);
	LoadImageFromResource(&m_BlackMa, IDP_BMA);
	LoadImageFromResource(&m_BlackChe, IDP_BJU);
	LoadImageFromResource(&m_BlackPao, IDP_BPAO);
	LoadImageFromResource(&m_BlackBing, IDP_BBING);
#else
	if (m_QiPangPicture.GetSafeHandle() == NULL)
		m_QiPangPicture.LoadBitmap(IDB_QIPANG);

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
#endif

}

CChineseChessView::~CChineseChessView()
{}

BEGIN_MESSAGE_MAP(CChineseChessView, CView)
ON_WM_LBUTTONUP()
ON_WM_KEYUP()
ON_WM_SIZE()
ON_WM_CREATE()
END_MESSAGE_MAP()

// CChineseChessView 消息处理程序
int CChineseChessView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}

void CChineseChessView::OnLButtonUp(UINT nFlags, CPoint point)
{
    int i = 0, j = 0;
    ConvertCoordinate(&point.x, &point.y, &i, &j);
    TRACE(_T("point: i = %d j = %d\n"), i, j);
    TRACE(_T("CXQCtrl::OnLButtonUp的当前线程:%x\n"), ::GetCurrentThreadId());
    if (GoChess(i, j))
    {
        
    }
    
    CView::OnLButtonUp(nFlags, point);
}


void CChineseChessView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    
    CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CChineseChessView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
    
    SetQiPang(cx, cy);
    Invalidate();
}

void CChineseChessView::OnDraw(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
	pDC->SetStretchBltMode(HALFTONE);
    DrawQiPang(pDC, rect);   //画棋盘
}

void CChineseChessView::AboutBox()
{
    CDialogEx dlgAbout(IDD_ABOUTBOX_CHINESECHESSACTIVEX);
    dlgAbout.DoModal();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 === 虚拟函数实现 === 的函数块
//

int CChineseChessView::onPromptSound(PROMPT_SOUND sound)
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

int CChineseChessView::onPromptMessage(CGoRule::ENUM_ReturnValue val)
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

int CChineseChessView::onCleanPrompt(int i, int j)
{
    InvalidateRectage(i, j);
    return 0;
}

int CChineseChessView::onDrawPrompt(int i, int j)
{
    InvalidateRectage(i, j);
    return 0;
}

int CChineseChessView::onGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
    if (m_pGoChessHandler)
        m_pGoChessHandler->OnGoChess(i, j, chess);
    return 0;
}

int CChineseChessView::SetChineseChessHandler(CChineseChessHandler* handler)
{
    m_pGoChessHandler = handler;
    return 0;
}

int CChineseChessView::SaveChessGame(LPCTSTR pszFile)
{
    USES_CONVERSION;
    return __super::SaveChessGame(T2CA(pszFile));
}

int CChineseChessView::LoadChessGame(LPCTSTR pszFile)
{
    USES_CONVERSION;
	int nRet = 0;
	nRet = __super::LoadChessGame(T2CA(pszFile));
	if (nRet) return nRet;
	Invalidate();
	return nRet;
}

int CChineseChessView::SetRedName(LPCTSTR pszName)
{
    USES_CONVERSION;
    return __super::SetRedName(T2CA(pszName));
}

int CChineseChessView::SetBlackName(LPCTSTR pszName)
{
    USES_CONVERSION;
    return __super::SetBlackName(T2CA(pszName));
}

int CChineseChessView::AddGameTag(LPCTSTR pszTag, LPCTSTR pszVal)
{
	USES_CONVERSION;
	return __super::AddGameTag(T2CA(pszTag), T2CA(pszVal));
}

CString CChineseChessView::GetGameTag(LPCTSTR pszTag)
{
	USES_CONVERSION;
	return A2CT(__super::GetGameTag(T2CA(pszTag)).c_str());
}

//
//以上是完成 === 虚拟函数实现 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int CChineseChessView::SetQiPangColor(COLORREF col)
{
	m_QiPangColor = col;
	Invalidate();
	return 0;
}

COLORREF CChineseChessView::GetQiPangColor()
{
	return m_QiPangColor;
}

int CChineseChessView::SetTiShiBoxColor(COLORREF col)
{
	m_TiShiBoxColor = col;
	Invalidate();
	return 0;
}

COLORREF CChineseChessView::GetTiShiBoxColor()
{
	return m_TiShiBoxColor;
}

/*******************************************************************************************************
函数名：SetQiPang
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
BOOL CChineseChessView::SetQiPang(int width, int height)
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

#ifdef CHINESE_CHESS_USE_PNG
BOOL CChineseChessView::LoadImageFromResource(CImage *pImage, UINT ID, LPCTSTR pType)
{
	return LoadImageFromResource(pImage, MAKEINTRESOURCE(ID), pType);
}

/**
 * Loads image from resource.
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/6/5
 *
 * @param [in,out] pImage If non-null, the image.
 * @param 		   ID	  The resource identifier.
 * @param 		   lpTyp  The resource type.
 *
 * @returns True if it succeeds, false if it fails.
 */

BOOL CChineseChessView::LoadImageFromResource(CImage* pImage, LPCTSTR pID, LPCTSTR lpType)
{
	if (pImage == NULL) return false;

	pImage->Destroy();

#ifdef _AFXEXT  // MFC 扩展动态库
	HINSTANCE hInstance = AfxFindResourceHandle(pID, lpType); //得到资源在哪个模块里，返回这个模块实例句柄
#else
	HINSTANCE hInstance = AfxGetInstanceHandle();
#endif

	// 查找资源
	HRSRC hRsrc = ::FindResource(hInstance, pID, lpType);
	if (hRsrc == NULL) return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(hInstance, hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(hInstance, hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);

		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}
#endif

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
BOOL CChineseChessView::PromptSound(LPCTSTR ID)
{
	if (NULL != ID)
	{
		// @see https://docs.microsoft.com/en-us/cpp/build/extension-dlls?view=vs-2019
#ifdef _AFXEXT  // MFC 扩展动态库
		HINSTANCE hInstance = AfxFindResourceHandle(ID, _T("WAVE")); //得到资源在哪个模块里，返回这个模块实例句柄
#else
		HINSTANCE hInstance = AfxGetInstanceHandle();
#endif

		HRSRC hr = FindResource(hInstance, ID, _T("WAVE"));
		if (NULL == hr) return false;

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
BOOL CChineseChessView::ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC)
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
void CChineseChessView::DrawQiPang(CDC *pdc, CRect rcBounds)
{
    ASSERT(pdc != NULL);
	
    //棋盘图片
#ifdef CHINESE_CHESS_USE_PNG
	m_QiPangPicture.Draw(pdc->m_hDC, rcBounds);
#else
    BITMAP bitmap;
    m_QiPangPicture.GetBitmap(&bitmap);
    
    CDC psdc;
    psdc.CreateCompatibleDC(pdc);
    psdc.SelectObject(&m_QiPangPicture);
    
    pdc->StretchBlt(0, 0, rcBounds.Width(), rcBounds.Height(),
                    &psdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
    
    psdc.DeleteDC();
#endif
    
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
    DrawPicture(pdc, 7, 4, &m_Chu, true);
    DrawPicture(pdc, 6, 4, &m_He, true);
    DrawPicture(pdc, 1, 4, &m_Han, true);
    DrawPicture(pdc, 2, 4, &m_Jie, true);
    DrawPicture(pdc, 4, 4, &m_Copyright, true);
    
    //画棋子
    for (i = 0; i < 9; i++)
        for (j = 0; j < 10; j++)
        {
            DrawQiZi(pdc, i, j, m_ChessBoard[i][j]);
        }
    
    //显示提示框
    if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
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
void CChineseChessView::DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei)
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
BOOL CChineseChessView::DrawTiShiBox(CDC *pdc, int i, int j)
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
BOOL CChineseChessView::DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi)
{
    ASSERT(pdc != NULL);
#ifdef CHINESE_CHESS_USE_PNG
	CImage *pQiZi = NULL;
#else
    CBitmap *pQiZi = NULL;
#endif

#pragma warning( disable : 4806 )
    
    switch (eQiZi)
    {
    case CPiece::NoQiZi:
        return false;
    case CPiece::RShuai:
        pQiZi = &m_RedShuai;
        break;
    case CPiece::RShi:
        pQiZi = &m_RedShi;
        break;
    case CPiece::RXiang:
        pQiZi = &m_RedXiang;
        break;
    case CPiece::RMa:
        pQiZi = &m_RedMa;
        break;
    case CPiece::RChe:
        pQiZi = &m_RedChe;
        break;
    case CPiece::RPao:
        pQiZi = &m_RedPao;
        break;
    case CPiece::RBing:
        pQiZi = &m_RedBing;
        break;
    case CPiece::BShuai:
        pQiZi = &m_BlackShuai;
        break;
    case CPiece::BShi:
        pQiZi = &m_BlackShi;
        break;
    case CPiece::BXiang:
        pQiZi = &m_BlackXiang;
        break;
    case CPiece::BMa:
        pQiZi = &m_BlackMa;
        break;
    case CPiece::BChe:
        pQiZi = &m_BlackChe;
        break;
    case CPiece::BPao:
        pQiZi = &m_BlackPao;
        break;
    case CPiece::BBing:
        pQiZi = &m_BlackBing;
        break;
    }
    
#pragma warning( default : 4806 )
    
    if (NULL != pQiZi)
    {
        return DrawPicture(pdc, i, j, pQiZi);
    }

    return false;
}

#ifdef CHINESE_CHESS_USE_PNG
BOOL CChineseChessView::DrawPicture(CDC *pdc, int i, int j, CImage* pImage)
{
	ASSERT(pdc != NULL && pImage != NULL);

	long x, y;
	
	ConvertCoordinate(&x, &y, &i, &j, IJToXY);
	x -= m_QiPangDistance / 2;
	y -= m_QiPangDistance / 2;
	return pImage->Draw(pdc->m_hDC, x, y, m_QiPangDistance, m_QiPangDistance);
}
#endif

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
BOOL CChineseChessView::DrawPicture(CDC *pdc, int i, int j, CBitmap *pbmp, BOOL CHHJKL)
{
    ASSERT(pdc != NULL && pbmp != NULL);
	if (pbmp->GetSafeHandle() == NULL)
		return false;

    long x, y;
    
    ConvertCoordinate(&x, &y, &i, &j, IJToXY);
    if (CHHJKL)//画楚河汉界
    {
        x -= m_QiPangDistance / 2;
    }
    else
    {
        x -= m_QiPangDistance / 2;
        y -= m_QiPangDistance / 2;
    }
    
    //棋盘图片
    BITMAP bitmap;
    pbmp->GetBitmap(&bitmap);
    
    CDC psdc;
    psdc.CreateCompatibleDC(pdc);
    psdc.SelectObject(pbmp);
    
    TransparentBlt2(pdc->GetSafeHdc(), x, y, m_QiPangDistance, m_QiPangDistance,
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
void CChineseChessView::InvalidateRectage(int i, int j)
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
        InvalidateRect(&rect);
    }
}

//
//以上是完成 === 中国象棋界面处理 === 的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
