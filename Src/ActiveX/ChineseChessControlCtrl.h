/**
 * @file ChineseChessControlCtrl.h.
 *
 * 中国象棋 ActiveX 控件的界面实现
 */
 
#pragma once

// ChineseChessControlCtrl.h : CChineseChessControlCtrl ActiveX 控件类的声明。


// CChineseChessControlCtrl : 请参阅 ChineseChessControlCtrl.cpp 了解实现。

#include "../MFC/ChineseChessView.h"

/**
 * 中国象棋 ActiveX 控件的界面实现类
 *
 * @author KangLin(kl222@126.com)
 * @date 2020/5/17
 */
class CChineseChessControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CChineseChessControlCtrl)

// 构造函数
public:
	CChineseChessControlCtrl();

// 重写
public:
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// 调度映射
	DECLARE_DISPATCH_MAP()

	void OnQiPangColorChanged();
	OLE_COLOR m_QiPangColor;
	void OnTiShiBoxColorChanged();
	OLE_COLOR m_TiShiBoxColor;
	void OnBoardLayoutChanged();
	CChineseChess::ENUM_BoardLayout m_BoardLayout;
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

protected:
	void OnEnablePromptMessageChanged();
	VARIANT_BOOL m_EnablePromptMessage;
};

