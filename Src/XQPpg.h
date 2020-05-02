#if !defined(AFX_XQPPG_H__B3ABF197_1087_4A72_927E_F1C01DC05E95__INCLUDED_)
#define AFX_XQPPG_H__B3ABF197_1087_4A72_927E_F1C01DC05E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// XQPpg.h : Declaration of the CXQPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CXQPropPage : See XQPpg.cpp.cpp for implementation.

class CXQPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CXQPropPage)
	DECLARE_OLECREATE_EX(CXQPropPage)

// Constructor
public:
	CXQPropPage();

// Dialog Data
	//{{AFX_DATA(CXQPropPage)
	enum { IDD = IDD_PROPPAGE_XQ };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CXQPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XQPPG_H__B3ABF197_1087_4A72_927E_F1C01DC05E95__INCLUDED)
