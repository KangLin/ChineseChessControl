#pragma once

// ChineseChessActiveXPropPage.h: CChineseChessActiveXPropPage ����ҳ���������


// CChineseChessActiveXPropPage : ����� ChineseChessActiveXPropPage.cpp �˽�ʵ�֡�

class CChineseChessActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CChineseChessActiveXPropPage)
	DECLARE_OLECREATE_EX(CChineseChessActiveXPropPage)

// ���캯��
public:
	CChineseChessActiveXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CHINESECHESSACTIVEX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

