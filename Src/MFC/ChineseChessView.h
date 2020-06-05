#pragma once

#include "ChineseChess.h"
// CChineseChessView

#ifdef USE_PNG
#include<atlimage.h>
#endif

class AFX_EXT_CLASS CChineseChessHandler
{
public:
	CChineseChessHandler() {}
	~CChineseChessHandler() {}
	
	/**
	 * Executes the go chess action
	 *
	 * @author KangLin(kl222@126.com)
	 * @date 2020/5/24
	 *
	 * @param  int i：当前下棋的位置,横坐标[0-8]
     * @param  int j：当前下棋的位置,纵坐标[0-9]
	 * @param  CPiece::ENUM_QiZi chess：棋子
	 *
	 * @returns An int.
	 *
	 * @see CPiece::ENUM_QiZi
	 */
	virtual int OnGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;
};

class AFX_EXT_CLASS CChineseChessView : public CView, public CChineseChess
{
	DECLARE_DYNAMIC(CChineseChessView)

public:
	CChineseChessView();
	virtual ~CChineseChessView();
	void AboutBox();

	int SetQiPangColor(COLORREF col);
	COLORREF GetQiPangColor();
	int SetTiShiBoxColor(COLORREF col);
	COLORREF GetTiShiBoxColor();
	virtual int SaveChessGame(LPCTSTR pszFile);
	virtual int LoadChessGame(LPCTSTR pszFile);
	virtual int SetRedName(LPCTSTR pszName);
	virtual int SetBlackName(LPCTSTR pszName);
	virtual int SetGameTags(LPCTSTR pszTags);

	int SetChineseChessHandler(CChineseChessHandler* handler);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual void OnDraw(CDC* pDC);

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
	
	COLORREF m_QiPangColor;
	COLORREF m_TiShiBoxColor;
	
	CBitmap m_QiPangPicture;			  //棋盘背景图片
	//楚河汉界
	CBitmap m_Chu;
	CBitmap m_He;
	CBitmap m_Han;
	CBitmap m_Jie;
	CBitmap m_Copyright;

	//棋子图片
#ifdef USE_PNG
	CImage m_RedShuai;     //红帅
	CImage m_RedShi;       //红仕
	CImage m_RedXiang;     //红相
	CImage m_RedMa;        //红马
	CImage m_RedChe;       //红车
	CImage m_RedBing;      //红兵
	CImage m_RedPao;       //红炮

	CImage m_BlackShuai;   //黑帅
	CImage m_BlackShi;     //黑仕
	CImage m_BlackXiang;   //黑相
	CImage m_BlackMa;      //黑马
	CImage m_BlackChe;     //黑车
	CImage m_BlackBing;    //黑兵
	CImage m_BlackPao;     //黑炮
#else
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
#endif

#ifdef USE_PNG
	// 从资源中加载图片到 CImage
	BOOL LoadImageFromResource(CImage *pImage, UINT ID, LPCTSTR pType = _T("PNG"));
	BOOL LoadImageFromResource(CImage *pImage, LPCTSTR pID, LPCTSTR pType = _T("PNG"));
#endif

	//坐标转换
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//棋盘星位
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);
#ifdef USE_PNG
	BOOL DrawImage(CDC *pdc, int i, int j, CImage* pImage);
#endif
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);

	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

	CChineseChessHandler* m_pGoChessHandler;
};
