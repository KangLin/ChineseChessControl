/**
 * @file ChineseChessActiveXCtrl.h.
 *
 * 中国象棋 ActiveX 控件的界面实现
 */
 
#pragma once

// ChineseChessActiveXCtrl.h : CChineseChessActiveXCtrl ActiveX 控件类的声明。


// CChineseChessActiveXCtrl : 请参阅 ChineseChessActiveXCtrl.cpp 了解实现。

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
 * 中国象棋 ActiveX 控件的界面实现类
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CChineseChessActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CChineseChessActiveXCtrl)

// 构造函数
public:
	CChineseChessActiveXCtrl();

// 重写
public:
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CChineseChessActiveXCtrl();

	DECLARE_OLECREATE_EX(CChineseChessActiveXCtrl) // 类工厂和 guid
	DECLARE_OLETYPELIB(CChineseChessActiveXCtrl)   // GetTypeInfo
	DECLARE_PROPPAGEIDS(CChineseChessActiveXCtrl)  // 属性页 ID
	DECLARE_OLECTLTYPE(CChineseChessActiveXCtrl)   // 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// 调度映射
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
	BSTR GetGameTags();
	void SetGameTags(LPCTSTR val);
	LONG GetStartTime();
	void SetStartTime(LONG val);
	LONG GetEndTime();
	void SetEndTime(LONG val);
	
	afx_msg void AboutBox();
	VARIANT_BOOL NextStep();    //下一步
	VARIANT_BOOL PreviouStep(); //上一步
	VARIANT_BOOL GoChess(SHORT i, SHORT j);
	VARIANT_BOOL SaveChessGame(LPCTSTR szFile);
	VARIANT_BOOL LoadChessGame(LPCTSTR szFile);

// 事件映射
	DECLARE_EVENT_MAP()

public:
	void EventGoChess(SHORT i, SHORT j, LONG qz)
	{
		FireEvent(eventidEventGoChess, EVENT_PARAM(VTS_I2 VTS_I2 VTS_I4), i, j, qz);
	}

// 调度和事件 ID
public:
	enum {
		eventidEventGoChess = 1L,
		dispidGameTags = 15L,
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

