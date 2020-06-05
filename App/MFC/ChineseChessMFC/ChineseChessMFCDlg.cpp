
// ChineseChessMFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ChineseChessMFC.h"
#include "ChineseChessMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChineseChessMFCDlg 对话框

CChineseChessMFCDlg::CChineseChessMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHINESECHESSMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pChess = new CChineseChessView();
}

void CChineseChessMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEXT, m_btNext);
	DDX_Control(pDX, IDC_PREVIOU, m_btPreviou);
	DDX_Control(pDX, IDC_SAVE, m_btSave);
	DDX_Control(pDX, IDC_LOAD, m_btLoad);
}

BEGIN_MESSAGE_MAP(CChineseChessMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PREVIOU, &CChineseChessMFCDlg::OnBnClickedPreviou)
	ON_BN_CLICKED(IDC_NEXT, &CChineseChessMFCDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_SAVE, &CChineseChessMFCDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CChineseChessMFCDlg::OnBnClickedLoad)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CChineseChessMFCDlg 消息处理程序

BOOL CChineseChessMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	CRect rect;
	this->GetClientRect(rect);

	m_pChess->Create(NULL, _T("Chinese chess"), WS_CHILD, rect, this, IDW_CHESS);
	m_pChess->ShowWindow(SW_SHOW);
	ReSize(rect.Width(), rect.Height());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChineseChessMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		m_pChess->AboutBox();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChineseChessMFCDlg::OnPaint()
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
HCURSOR CChineseChessMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CChineseChessMFCDlg::ReSize(int cx, int cy)
{
	CRect rect1, rect2;
	if (NULL == m_pChess || NULL == m_pChess->GetSafeHwnd())
		return -1;

	if (!m_btNext.GetSafeHwnd())
		return -1;

	m_btNext.GetWindowRect(&rect1);
	m_btPreviou.GetWindowRect(&rect2);
	int y = cy - max(rect1.Height(), rect2.Height()) - 5;

	m_pChess->MoveWindow(0, 0, cx, y);

	m_btNext.MoveWindow(cx - rect1.Width() - 5, y + 5, rect1.Width(), rect1.Height());
	m_btPreviou.MoveWindow(cx - rect1.Width() - rect2.Width() - 5, y + 5, rect1.Width(), rect1.Height());

	m_btLoad.GetWindowRect(&rect1);
	m_btLoad.MoveWindow(0, y + 5, rect1.Width(), rect1.Height());
	m_btSave.GetWindowRect(&rect2);
	m_btSave.MoveWindow(rect1.Width() + 5, y + 5, rect2.Width(), rect2.Height());
	return 0;
}

void CChineseChessMFCDlg::OnBnClickedPreviou()
{
	m_pChess->PreviouStep();
}

void CChineseChessMFCDlg::OnBnClickedNext()
{
	m_pChess->NextStep();
}

void CChineseChessMFCDlg::OnBnClickedSave()
{
	CString szFile;
	CFileDialog dlg(FALSE);
	if (dlg.DoModal() == IDOK)
	{
		szFile = dlg.GetPathName();
		m_pChess->SaveChessGame(szFile);
	}
}

void CChineseChessMFCDlg::OnBnClickedLoad()
{
	CString szFile;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		szFile = dlg.GetPathName();
		m_pChess->LoadChessGame(szFile);
	}
}

void CChineseChessMFCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	ReSize(cx, cy);
}
