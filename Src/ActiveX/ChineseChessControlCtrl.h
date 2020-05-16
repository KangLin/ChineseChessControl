#pragma once

// ChineseChessControlCtrl.h : CChineseChessControlCtrl ActiveX 控件类的声明。


// CChineseChessControlCtrl : 请参阅 ChineseChessControlCtrl.cpp 了解实现。

class CChineseChessControlCtrl : public COleControl
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

	DECLARE_OLECREATE_EX(CChineseChessControlCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CChineseChessControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CChineseChessControlCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CChineseChessControlCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
	};
};

