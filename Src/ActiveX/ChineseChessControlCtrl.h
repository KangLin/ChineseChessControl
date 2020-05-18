/**
 * @file ChineseChessControlCtrl.h.
 *
 * 中国象棋 ActiveX 控件的界面实现
 */
 
#pragma once

// ChineseChessControlCtrl.h : CChineseChessControlCtrl ActiveX 控件类的声明。


// CChineseChessControlCtrl : 请参阅 ChineseChessControlCtrl.cpp 了解实现。

#include "../ChineseChess.h"

/**
 * 中国象棋 ActiveX 控件的界面实现类
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CChineseChessControlCtrl : public COleControl, CChineseChess
{
	DECLARE_DYNCREATE(CChineseChessControlCtrl)

// 构造函数
public:
	CChineseChessControlCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CChineseChessControlCtrl();

	DECLARE_OLECREATE_EX(CChineseChessControlCtrl) // 类工厂和 guid
	DECLARE_OLETYPELIB(CChineseChessControlCtrl)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(CChineseChessControlCtrl)  // 属性页 ID
	DECLARE_OLECTLTYPE(CChineseChessControlCtrl)   // 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// 调度映射
	DECLARE_DISPATCH_MAP()

	void OnQiPangColorChanged();
	OLE_COLOR m_QiPangColor;
	void OnTiShiBoxColorChanged();
	OLE_COLOR m_TiShiBoxColor;
	void OnBoardLayoutChanged();
	ENUM_BoardLayout m_BoardLayout;
	void OnEnablePromptSoundChanged();
	VARIANT_BOOL m_EnablePromptSound;

	afx_msg void AboutBox();
	VARIANT_BOOL NextStep();    //下一步
	VARIANT_BOOL PreviouStep(); //上一步
	VARIANT_BOOL GoChess(SHORT i, SHORT j);
	VARIANT_BOOL SaveChessGame(LPCTSTR szFile);
	VARIANT_BOOL LoadChessGame(LPCTSTR szFile);

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidEnablePromptSound = 4,
		dispidPreviouStep = 10L,
		dispidNextStep = 9L,
		dispidLoadChessGame = 8L,
		dispidSaveChessGame = 7L,
		dispidGoChess = 6L,
		dispidBoardLayout = 3,
		dispidTiShiBoxColor = 2,
		dispidQiPangColor = 1,
	};

protected:
	virtual int onPromptSound(PROMPT_SOUND sound);
	virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val);

	virtual int onCleanPrompt(int i, int j);
	virtual int onDrawPrompt(int i, int j);
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess);

private:
	LONG m_QiPangStartX;   //棋盘的开始横坐标
	LONG m_QiPangStartY;   //棋盘的开始横坐标
	LONG m_QiPangDistance; //棋盘格的距离

	CBitmap m_QiPangPicture;			  //棋盘背景图片
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

	
	//坐标转换
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//棋盘星位
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);

	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

};

