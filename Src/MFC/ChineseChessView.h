#pragma once

#include "ChineseChess.h"

#ifdef CHINESE_CHESS_USE_PNG
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
	 * @param  int i����ǰ�����λ��,������[0-8]
     * @param  int j����ǰ�����λ��,������[0-9]
	 * @param  CPiece::ENUM_QiZi chess������
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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
	LONG m_QiPangStartX;   //���̵Ŀ�ʼ������
	LONG m_QiPangStartY;   //���̵Ŀ�ʼ������
	LONG m_QiPangDistance; //���̸�ľ���
	
	COLORREF m_QiPangColor;
	COLORREF m_TiShiBoxColor;
	
	
	//���Ӻ���
	CBitmap m_Chu;
	CBitmap m_He;
	CBitmap m_Han;
	CBitmap m_Jie;
	CBitmap m_Copyright;

#ifdef CHINESE_CHESS_USE_PNG
	ATL::CImage m_QiPangPicture; //���̱���ͼƬ

	//����ͼƬ
	ATL::CImage m_RedShuai;     //��˧
	ATL::CImage m_RedShi;       //����
	ATL::CImage m_RedXiang;     //����
	ATL::CImage m_RedMa;        //����
	ATL::CImage m_RedChe;       //�쳵
	ATL::CImage m_RedBing;      //���
	ATL::CImage m_RedPao;       //����

	ATL::CImage m_BlackShuai;   //��˧
	ATL::CImage m_BlackShi;     //����
	ATL::CImage m_BlackXiang;   //����
	ATL::CImage m_BlackMa;      //����
	ATL::CImage m_BlackChe;     //�ڳ�
	ATL::CImage m_BlackBing;    //�ڱ�
	ATL::CImage m_BlackPao;     //����
#else
	CBitmap m_QiPangPicture; //���̱���ͼƬ

	//����ͼƬ
	CBitmap m_RedShuai;     //��˧
	CBitmap m_RedShi;       //����
	CBitmap m_RedXiang;     //����
	CBitmap m_RedMa;        //����
	CBitmap m_RedChe;       //�쳵
	CBitmap m_RedBing;      //���
	CBitmap m_RedPao;       //����

	CBitmap m_BlackShuai;   //��˧
	CBitmap m_BlackShi;     //����
	CBitmap m_BlackXiang;   //����
	CBitmap m_BlackMa;      //����
	CBitmap m_BlackChe;     //�ڳ�
	CBitmap m_BlackBing;    //�ڱ�
	CBitmap m_BlackPao;     //����
#endif

#ifdef CHINESE_CHESS_USE_PNG
	// ����Դ�м���ͼƬ�� CImage
	BOOL LoadImageFromResource(ATL::CImage *pImage, UINT ID, LPCTSTR pType = _T("PNG"));
	BOOL LoadImageFromResource(ATL::CImage *pImage, LPCTSTR pID, LPCTSTR pType = _T("PNG"));
#endif

	//����ת��
	enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
	BOOL ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);

	//������λ
	enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
	void DrawXinWei(CDC *pdc, int i, int j, ENUM_XINWEI xinwei = XinWei);
	BOOL DrawTiShiBox(CDC *pdc, int i, int j);
	BOOL DrawQiZi(CDC *pdc, int i, int j, CPiece::ENUM_QiZi eQiZi);
	void DrawQiPang(CDC *pdc, CRect rcBounds);
#ifdef CHINESE_CHESS_USE_PNG
	BOOL DrawPicture(CDC *pdc, int i, int j, ATL::CImage* pImage);
#endif
	BOOL DrawPicture(CDC *pdc, int i, int j, CBitmap* pbmp, BOOL CHHJKL = false);
	
	void InvalidateRectage(int i, int j);

	BOOL SetQiPang(int width, int height);
	BOOL PromptSound(LPCTSTR ID = NULL);

	CChineseChessHandler* m_pGoChessHandler;
};
