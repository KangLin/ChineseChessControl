#pragma once

// ChineseChessActiveXPropPage.h: CChineseChessActiveXPropPage 属性页类的声明。


// CChineseChessActiveXPropPage : 请参阅 ChineseChessActiveXPropPage.cpp 了解实现。

class CChineseChessActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CChineseChessActiveXPropPage)
	DECLARE_OLECREATE_EX(CChineseChessActiveXPropPage)

// 构造函数
public:
	CChineseChessActiveXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CHINESECHESSACTIVEX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

