// ChineseChessActiveXPropPage.cpp : CChineseChessActiveXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "ChineseChessActiveX.h"
#include "ChineseChessActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChineseChessActiveXPropPage, COlePropertyPage)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CChineseChessActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CChineseChessActiveXPropPage, "ChineseChessActiveXPropPage.2.0.4",
	0x035c7fb0,0x47a0,0x45fb,0xa4,0x5a,0xc2,0x9d,0xcf,0xe9,0xe0,0x01)

// CChineseChessActiveXPropPage::CChineseChessActiveXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CChineseChessActiveXPropPage ��ϵͳע�����

BOOL CChineseChessActiveXPropPage::CChineseChessActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CHINESECHESSACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CChineseChessActiveXPropPage::CChineseChessActiveXPropPage - ���캯��

CChineseChessActiveXPropPage::CChineseChessActiveXPropPage() :
	COlePropertyPage(IDD, IDS_CHINESECHESSACTIVEX_PPG_CAPTION)
{
}

// CChineseChessActiveXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CChineseChessActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CChineseChessActiveXPropPage ��Ϣ�������
