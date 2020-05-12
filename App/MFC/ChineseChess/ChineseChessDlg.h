
// ChineseChessDlg.h : 头文件
//

#pragma once
#include "Chess.h"


// CChineseChessDlg 对话框
class CChineseChessDlg : public CDialogEx
{
// 构造
public:
	CChineseChessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHINESECHESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CChess m_Chess;
	DECLARE_EVENTSINK_MAP()
	void MoveChessChess(short x, short y, long chess);
};
