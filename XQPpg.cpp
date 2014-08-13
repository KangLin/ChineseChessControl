// XQPpg.cpp : Implementation of the CXQPropPage property page class.

#include "stdafx.h"
#include "ChinesChessCtr.h"
#include "XQPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CXQPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXQPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CXQPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXQPropPage, "MY.XQPropPage.1",
	0x6386faf3, 0x3b5b, 0x45bf, 0x93, 0xa2, 0xa7, 0x5d, 0xeb, 0xde, 0x45, 0xef)


/////////////////////////////////////////////////////////////////////////////
// CXQPropPage::CXQPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CXQPropPage

BOOL CXQPropPage::CXQPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_XQ_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CXQPropPage::CXQPropPage - Constructor

CXQPropPage::CXQPropPage() :
	COlePropertyPage(IDD, IDS_XQ_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CXQPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CXQPropPage::DoDataExchange - Moves data between page and properties

void CXQPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CXQPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CXQPropPage message handlers
