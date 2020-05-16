// ChineseChessControlPropPage.cpp : CChineseChessControlPropPage 属性页类的实现。

#include "pch.h"
#include "framework.h"
#include "ChineseChessControl.h"
#include "ChineseChessControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessControlPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CChineseChessControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CChineseChessControlPropPage, "ChineseChessControlPropPage.1.1.1",
	0x7f26ea27,0xd2da,0x4300,0xb1,0x72,0x58,0x8b,0x36,0xe0,0x7f,0x17)

// CChineseChessControlPropPage::CChineseChessControlPropPageFactory::UpdateRegistry -
// 添加或移除 CChineseChessControlPropPage 的系统注册表项

BOOL CChineseChessControlPropPage::CChineseChessControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CHINESECHESSCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CChineseChessControlPropPage::CChineseChessControlPropPage - 构造函数

CChineseChessControlPropPage::CChineseChessControlPropPage() :
	COlePropertyPage(IDD, IDS_CHINESECHESSCONTROL_PPG_CAPTION)
{
}

// CChineseChessControlPropPage::DoDataExchange - 在页和属性间移动数据

void CChineseChessControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CChineseChessControlPropPage 消息处理程序
