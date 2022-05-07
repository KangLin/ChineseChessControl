/**
 * @file ChineseChessActiveXCtrl.h.
 *
 * �й����� ActiveX �ؼ��Ľ���ʵ��
 */
 
#pragma once

// ChineseChessActiveXCtrl.h : CChineseChessActiveXCtrl ActiveX �ؼ����������


// CChineseChessActiveXCtrl : ����� ChineseChessActiveXCtrl.cpp �˽�ʵ�֡�

#include "ChineseChessView.h"

class CChineseChessActiveXCtrl;
class CChineseChessActiveXHandler : public CChineseChessHandler
{
public:
	CChineseChessActiveXHandler(CChineseChessActiveXCtrl* pAcitveX)
	{
		m_pActiveX = pAcitveX;
	}
	virtual int OnGoChess(int i, int j, CPiece::ENUM_QiZi chess);

private:
	CChineseChessActiveXCtrl* m_pActiveX;
};

/**
 * �й����� ActiveX �ؼ��Ľ���ʵ����
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CChineseChessActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CChineseChessActiveXCtrl)

// ���캯��
public:
	CChineseChessActiveXCtrl();

// ��д
public:
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CChineseChessActiveXCtrl();

	DECLARE_OLECREATE_EX(CChineseChessActiveXCtrl) // �๤���� guid
	DECLARE_OLETYPELIB(CChineseChessActiveXCtrl)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(CChineseChessActiveXCtrl)  // ����ҳ ID
	DECLARE_OLECTLTYPE(CChineseChessActiveXCtrl)   // �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	OLE_COLOR GetQiPangColor();
	void SetQiPangColor(OLE_COLOR val);
	void SetTiShiBoxColor(OLE_COLOR val);
	OLE_COLOR GetTiShiBoxColor();
	void SetBoardLayout(SHORT layout);
	SHORT GetBoardLayout();
	void OnEnablePromptSoundChanged();
	VARIANT_BOOL m_EnablePromptSound;
	void OnEnablePromptMessageChanged();
	VARIANT_BOOL m_EnablePromptMessage;

	BSTR GetRedName();
	void SetRedName(LPCTSTR newVal);
	BSTR GetBlackName();
	void SetBlackName(LPCTSTR newVal);
	LONG GetStartTime();
	void SetStartTime(LONG val);
	LONG GetEndTime();
	void SetEndTime(LONG val);
	
	afx_msg void AboutBox();
	VARIANT_BOOL NextStep();    //��һ��
	VARIANT_BOOL PreviouStep(); //��һ��
	VARIANT_BOOL GoChess(SHORT i, SHORT j);
	VARIANT_BOOL SaveChessGame(LPCTSTR szFile);
	VARIANT_BOOL LoadChessGame(LPCTSTR szFile);
	VARIANT_BOOL AddGameTag(LPCTSTR szTag, LPCTSTR szVal);
	BSTR GetgameTag(LPCTSTR szTag);

// �¼�ӳ��
	DECLARE_EVENT_MAP()

public:
	void EventGoChess(SHORT i, SHORT j, LONG qz)
	{
		FireEvent(eventidEventGoChess, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I4), i, j, qz);
	}

// ���Ⱥ��¼� ID
public:
	enum {
		eventidEventGoChess = 1L,
		dispidGetgameTag = 16L,
		dispidAddGameTag = 15L,
		dispidEndTime = 14,
		dispidStartTime = 13,
		dispidBlackName = 12L,
		dispidRedName = 11L,
		dispidPreviouStep = 10L,
		dispidNextStep = 9L,
		dispidLoadChessGame = 8L,
		dispidSaveChessGame = 7L,
		dispidGoChess = 6L,
		dispidEnablePromptMessage = 5,
		dispidEnablePromptSound = 4,
		dispidBoardLayout = 3,
		dispidTiShiBoxColor = 2,
		dispidQiPangColor = 1,
	};

private:
	CChineseChessView* m_pChess;

	CChineseChessActiveXHandler* m_pHandler;
};

