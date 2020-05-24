
// ChineseChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChineseChess.h"
#include "ChineseChessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChineseChessDlg 对话框



CChineseChessDlg::CChineseChessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChineseChessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChineseChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Chess, m_Chess);
	DDX_Control(pDX, IDC_PREVIOU, m_btnPreviou);
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_LOAD, m_btLoad);
	DDX_Control(pDX, IDC_SAVE, m_btSave);
}

BEGIN_MESSAGE_MAP(CChineseChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PREVIOU, &CChineseChessDlg::OnBnClickedPreviou)
	ON_BN_CLICKED(IDC_NEXT, &CChineseChessDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_LOAD, &CChineseChessDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SAVE, &CChineseChessDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CChineseChessDlg 消息处理程序

BOOL CChineseChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CRect rect;
	GetClientRect(&rect);
	ReSize(rect.Width(), rect.Height());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChineseChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		m_Chess.AboutBox();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChineseChessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChineseChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChineseChessDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	ReSize(cx, cy);
}

int CChineseChessDlg::ReSize(int cx, int cy)
{
	CRect rect1, rect2;
	if (NULL == m_Chess.GetSafeHwnd())
		return -1;
	m_btnNext.GetWindowRect(&rect1);
	m_btnPreviou.GetWindowRect(&rect2);
	int y = cy - max(rect1.Height(), rect2.Height()) - 5;
	m_Chess.MoveWindow(0, 0, cx, y);

	m_btnNext.MoveWindow(cx - rect1.Width() - 5, y + 5, rect1.Width(), rect1.Height());
	m_btnPreviou.MoveWindow(cx - rect1.Width() - rect2.Width() - 5, y + 5, rect1.Width(), rect1.Height());

	m_btLoad.GetWindowRect(&rect1);
	m_btLoad.MoveWindow(0, y + 5, rect1.Width(), rect1.Height());
	m_btSave.GetWindowRect(&rect2);
	m_btSave.MoveWindow(rect1.Width() + 5, y + 5, rect2.Width(), rect2.Height());
	return 0;
}

void CChineseChessDlg::OnBnClickedPreviou()
{
	m_Chess.PreviouStep();
}

void CChineseChessDlg::OnBnClickedNext()
{
	m_Chess.NextStep();
}
BEGIN_EVENTSINK_MAP(CChineseChessDlg, CDialogEx)
	ON_EVENT(CChineseChessDlg, 1000, 1, CChineseChessDlg::EventGoChess, VTS_I2 VTS_I2 VTS_I4)
END_EVENTSINK_MAP()


void CChineseChessDlg::EventGoChess(short i, short j, long qz)
{
	
}


void CChineseChessDlg::OnBnClickedLoad()
{
	CString szFile;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		szFile = dlg.GetPathName();
		m_Chess.LoadChessGame(szFile);
	}
}


void CChineseChessDlg::OnBnClickedSave()
{
	CString szFile;
	CFileDialog dlg(FALSE);
	if (dlg.DoModal() == IDOK)
	{
		szFile = dlg.GetPathName();
		m_Chess.SaveChessGame(szFile);
	}
}
