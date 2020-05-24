#pragma once

#include "ChineseChess.h"
// CChineseChessView


class AFX_EXT_CLASS CChineseChessHandler
{
public:
	CChineseChessHandler() {}
	~CChineseChessHandler() {}

	virtual int OnGoChess(int i, int j, CPiece::ENUM_QiZi chess) = 0;
};

class AFX_EXT_CLASS CChineseChessView : public CView, public CChineseChess
{
	DECLARE_DYNAMIC(CChineseChessView)

public:
	CChineseChessView();
	virtual ~CChineseChessView();
	void AboutBox();

	virtual int SaveChessGame(LPCTSTR pszFile);
	virtual int LoadChessGame(LPCTSTR pszFile);
	virtual int SetRedName(LPCTSTR pszName);
	virtual int SetBlackName(LPCTSTR pszName);

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
	LONG m_QiPangStartX;   //ÆåÅÌµÄ¿ªÊ¼ºá×ø±ê
	LONG m_QiPangStartY;   //ÆåÅÌµÄ¿ªÊ¼ºá×ø±ê
	LONG m_QiPangDistance; //ÆåÅÌ¸ñµÄ¾àÀë
	
	COLORREF m_QiPangColor;
	COLORREF m_TiShiBoxColor;
	
	CBitmap m_QiPangPicture;			  //ÆåÅÌ±³¾°Í¼Æ¬
	//CPictureHolder m_QiPangPictureHolder; //ÆåÅÌ±³¾°Í¼Æ¬µÄCPictureHolder¶ÔÏó

	//Æå×ÓÍ¼Æ¬
	CBitmap m_RedShuai;     //ºìË§
	CBitmap m_RedShi;       //ºìÊË
	CBitmap m_RedXiang;     //ºìÏà
	CBitmap m_RedMa;        //ºìÂí
	CBitmap m_RedChe;       //ºì³µ
	CBitmap m_RedBing;      //ºì±ø
	CBitmap m_RedPao;       //ºìÅÚ

	CBitmap m_BlackShuai;   //ºÚË§
	CBitmap m_BlackShi;     //ºÚÊË
	CBitmap m_BlackXiang;   //ºÚÏà
	CBitmap m_BlackMa;      //ºÚÂí
	CBitmap m_BlackChe;     //ºÚ³µ
	CBitmap m_BlackBing;    //ºÚ±ø
	CBitmap m_BlackPao;     //ºÚÅÚ


	//×ø±ê×ª»»
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//ÆåÅÌÐÇÎ»
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);

	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

	CChineseChessHandler* m_pGoChessHandler;
};


