#if !defined(AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED_)
#define AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED_

// 象棋控件头文件

#include <afxtempl.h>
#include <vector>
#include <mmsystem.h>
#include "GoRule.h"
#include "EnumAndStructAndConst.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment(lib, "winmm")
#pragma comment(lib, "Msimg32")

/*******************************************************************************************************
常量
*******************************************************************************************************/

//棋盘星位
enum ENUM_XINWEI{XinWei, Left_XinWei, Right_XinWei};
//坐标转换
enum ENUM_ConvertCoordinate{XYToIJ, IJToXY};
//棋盘布局
enum ENUM_QiPang{
	NoQi = 0,
	OnlyTopRed = 1,
	OnlyBottomBlack = 2,
	SwapRedBetweenBlack = 4,
	OnlyTopBlack = OnlyTopRed | SwapRedBetweenBlack,
	OnlyBottomRed = OnlyBottomBlack | SwapRedBetweenBlack,
	TopRedAndBottomBlack = OnlyTopRed | OnlyBottomBlack,
	TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed | SwapRedBetweenBlack
};
//走棋状态
enum ENUM_WalkState{RedReadly, RedWalked, BlackReadly, BlackWalked};

/*******************************************************************************************************
结构
*******************************************************************************************************/

//提示框的位置
struct struct_TiShiBoxPostion{          
		CPoint p1;
		CPoint p2;
};

//文件头
struct struct_File{
	TCHAR szAppName[MAX_STRING_BUFFER];    //程序名,在Restart中设置
	TCHAR szAuthor[MAX_STRING_BUFFER];     //程序作者：康林,在Restart中设置
	DWORD dwVersion;                       //版本,在Restart中设置
	time_t timeStart;                      //开始下棋的时间,在Restart中设置
	time_t timeEnd;                        //结束下棋的时间,在Restart中设置
	TCHAR szRedName[MAX_STRING_BUFFER];    //红方用户名
    TCHAR szBlackName[MAX_STRING_BUFFER];  //黑方用户名
	int iStartSide;                        //保存本局哪方先走棋,在Restart和SetStartSide中都有设置
	int iBuShu;                            //步数，在SaveChess中设置
	DWORD dwReserve;                       //保留
};

#define AUTHOR _T("作者：康林。版权所有。")

/*******************************************************************************************************
函数
*******************************************************************************************************/

//画透明图片
void TransparentBlt2(HDC hdcDest,         // 目标DC
                     int nXOriginDest,    // 目标X偏移
                     int nYOriginDest,    // 目标Y偏移
                     int nWidthDest,      // 目标宽度
                     int nHeightDest,     // 目标高度
                     HDC hdcSrc,          // 源DC
                     int nXOriginSrc,     // 源X起点
                     int nYOriginSrc,     // 源Y起点
                     int nWidthSrc,       // 源宽度
                     int nHeightSrc,      // 源高度
                     UINT crTransparent   // 透明色,COLORREF类型
					 );
/////////////////////////////////////////////////////////////////////////////
// CXQCtrl : See XQCtl.cpp for implementation.

class CXQCtrl : public COleControl
{
	DECLARE_DYNCREATE(CXQCtrl)

// Constructor
public:
	CXQCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXQCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CXQCtrl();

	DECLARE_OLECREATE_EX(CXQCtrl) // Class factory and guid
	DECLARE_OLETYPELIB(CXQCtrl)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(CXQCtrl)  // Property page IDs
	DECLARE_OLECTLTYPE(CXQCtrl)   // Type name and misc status

// Message maps
	//{{AFX_MSG(CXQCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CXQCtrl)
	OLE_COLOR m_QiPangColor;
	afx_msg void OnQiPangColorChanged();
	OLE_COLOR m_TiShiBoxColor;
	afx_msg void OnTiShiBoxColorChanged();
	long m_QiPang;
	afx_msg void OnQiPangLayoutChanged();
	afx_msg LPPICTUREDISP GetQiPangPicture();
	afx_msg void SetQiPangPicture(LPPICTUREDISP newValue);
	afx_msg long GetStartSide();
	afx_msg void SetStartSide(long nNewValue);
	afx_msg short GetCurrentSide();
	afx_msg void SetCurrentSide(short nNewValue);
    afx_msg long NextStep();                              //下一步
    afx_msg long PreviouStep();                           //上一步
    afx_msg void ReStart();                               //重新开始
    afx_msg BOOL SaveChess(LPCTSTR lpcszFileName);        //保存棋局
    afx_msg BOOL LoadChess(LPCTSTR lpcszFileName);        //装载棋局，并设置为结束状态
    afx_msg BOOL LoadChessStart(LPCTSTR lpcszFileName);   //装载棋局，并设置为开始状态
    afx_msg void QiPangInterconvert();                    //棋子互换
	afx_msg BOOL Walk(short i, short j);
	afx_msg void InterConvertCoordinate(short x, short y, short FAR* pi, short FAR* pj);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CXQCtrl)
	void FireMoveChess(short x, short y, long chess)
		{FireEvent(eventidMoveChess,EVENT_PARAM(VTS_I2  VTS_I2  VTS_I4), x, y, chess);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
    //{{AFX_DISP_ID(CXQCtrl)
	dispidQiPangColor = 1L,
	dispidTiShiBoxColor = 2L,
	dispidQiPangPicture = 4L,
	dispidQiPangLayout = 3L,
	dispidStartSide = 5L,
	dispidCurrentSide = 6L,
	dispidNextStep = 7L,
	dispidPreviouStep = 8L,
	dispidReStart = 9L,
	dispidSaveChess = 10L,
	dispidLoadChess = 11L,
	dispidLoadChessStart = 12L,
	dispidQiPangInterconvert = 13L,
	dispidWalk = 14L,
	dispidInterConvertCoordinate = 15L,
	eventidMoveChess = 1L,
	//}}AFX_DISP_ID
	};

private:	
    BOOL WalkChess(int i, int j, BOOL bEvent = TRUE);
	BOOL bWalkChess(int i, int j);

	int QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code,  ENUM_BianMa bianma= BianMa);
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC= XYToIJ);

	BOOL PromptSound(LPCTSTR ID = NULL);
	
	BOOL GetCBitmapFromCPictureHolder(CPictureHolder *ph, CBitmap *pb);
	
	void InvalidateRectage(CPoint p);
	void InvalidateRectage(int i, int j);
	
	BOOL DrawTiShiBox(CDC *pdc, CPoint p);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	void DrawQiPang(CDC *pdc, CRect rcBounds);

	BOOL Inital();
	BOOL SetQiPang(int width, int height);

	LONG m_QiPangStartX;                             //棋盘的开始横坐标
	LONG m_QiPangStartY;                             //棋盘的开始横坐标
	LONG m_QiPangDistance;                           //棋盘格的距离
	struct struct_TiShiBoxPostion m_TiShiBoxPostion; //提示框位置

	ENUM_WalkState m_WalkState;    //走棋状态（红方选棋，红方走棋，黑方先棋，黑方走棋）
	CPiece::ENUM_QiZi m_ChessBoard[9][10]; //棋盘 m_ChessBoard[i][j]
    CArray<int, int> m_QiJu;       //棋局

	INT m_iBuShu;                  //走棋步数
	BOOL m_bFuPang;                //复盘标志

	CBitmap m_QiPangPicture;              //棋盘背景图片
	CPictureHolder m_QiPangPictureHolder; //棋盘背景图片的CPictureHolder对象
	
	//棋子图片
    CBitmap m_RedShuai;     //红帅
    CBitmap m_RedShi;       //红仕
    CBitmap m_RedXiang;     //红相
    CBitmap m_RedMa;        //红马
    CBitmap m_RedChe;       //红车
    CBitmap m_RedBing;      //红兵
    CBitmap m_RedPao;       //红炮
	
    CBitmap m_BlackShuai;   //黑帅
    CBitmap m_BlackShi;     //黑仕
    CBitmap m_BlackXiang;   //黑相
    CBitmap m_BlackMa;      //黑马
    CBitmap m_BlackChe;     //黑车
    CBitmap m_BlackBing;    //黑兵
    CBitmap m_BlackPao;     //黑炮

	/*ENUM_QiPang m_QiPang; /*初始化棋盘（无棋，只摆上方红棋，只摆下方红棋，
						                只摆上方黑棋，只摆下方黑棋、
										上红下黑棋都摆，上黑下红都摆）
										*/
	CGoRule m_GoRule;       //走棋规则
	struct_File m_FileHead; //棋局文件头
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_XQCTL_H__8A497636_8516_444B_868E_0E753A2D3BA9__INCLUDED)
