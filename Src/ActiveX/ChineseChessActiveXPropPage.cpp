// ChineseChessActiveXPropPage.cpp : CChineseChessActiveXPropPage 属性页类的实现。

#include "stdafx.h"
#include "ChineseChessActiveX.h"
#include "ChineseChessActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessActiveXPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CChineseChessActiveXPropPage, "ChineseChessActiveXPropPage.2.0.3",
	0x035c7fb0,0x47a0,0x45fb,0xa4,0x5a,0xc2,0x9d,0xcf,0xe9,0xe0,0x01)

// CChineseChessActiveXPropPage::CChineseChessActiveXPropPageFactory::UpdateRegistry -
// 添加或移除 CChineseChessActiveXPropPage 的系统注册表项

BOOL CChineseChessActiveXPropPage::CChineseChessActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CHINESECHESSACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CChineseChessActiveXPropPage::CChineseChessActiveXPropPage - 构造函数

CChineseChessActiveXPropPage::CChineseChessActiveXPropPage() :
	COlePropertyPage(IDD, IDS_CHINESECHESSACTIVEX_PPG_CAPTION)
{
}

// CChineseChessActiveXPropPage::DoDataExchange - 在页和属性间移动数据

void CChineseChessActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CChineseChessActiveXPropPage 消息处理程序
