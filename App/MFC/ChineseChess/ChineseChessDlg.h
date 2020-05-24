
// ChineseChessDlg.h : 头文件
//

#pragma once
#include "chess.h"
#include "afxwin.h"


// CChineseChessDlg 对话框
class CChineseChessDlg : public CDialogEx
{
// 构造
public:
	CChineseChessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHINESECHESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedPreviou();
	afx_msg void OnBnClickedNext();

	DECLARE_MESSAGE_MAP()

	DECLARE_EVENTSINK_MAP()
	void EventGoChess(short i, short j, long qz);

private:
	CChess m_Chess;
	int ReSize(int cx, int cy);

	CButton m_btnPreviou;
	CButton m_btnNext;

};
