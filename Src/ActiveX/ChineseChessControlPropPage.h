#pragma once

// ChineseChessControlPropPage.h: CChineseChessControlPropPage 属性页类的声明。


// CChineseChessControlPropPage : 请参阅 ChineseChessControlPropPage.cpp 了解实现。

class CChineseChessControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CChineseChessControlPropPage)
	DECLARE_OLECREATE_EX(CChineseChessControlPropPage)

// 构造函数
public:
	CChineseChessControlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CHINESECHESSCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

