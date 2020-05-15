
#include "stdafx.h"
#include "ChineseChess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CChineseChess::CChineseChess()
{
	Initial();
}

CChineseChess::~CChineseChess()
{}

int CChineseChess::Initial()
{
	SetBoardLayout(TopBlackAndBottomRed);
	m_WalkState = RedReadly;
	m_PreviouPositionX = m_PreviouPositionX = -1;
	m_CurrentPositionX = m_CurrentPositionY = -1;
	m_iBuShu = -1;
	m_bFuPang = false;
	return 0;
}

int CChineseChess::GetBoard(int &row, int &col)
{
	row = GetBoardRow();
	col = GetBoardColumn();
	return 0;
}
int CChineseChess::GetBoardRow()
{
	return m_BoardRow;
}

int CChineseChess::GetBoardColumn()
{
	return m_BoardColumn;
}

int CChineseChess::SetBoardLayout(ENUM_BoardLayout layout)
{
	m_BoardLayout = layout;

	//��ʼ�������
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
			m_ChessBoard[i][j] = CPiece::NoQiZi;

	if (m_BoardLayout & OnlyTopBlack)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::RChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::RMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::RXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::RShi;
			m_ChessBoard[4][0] = CPiece::RShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::RPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::RBing;
		}
		else {
			m_ChessBoard[0][0] = m_ChessBoard[8][0] = CPiece::BChe;
			m_ChessBoard[1][0] = m_ChessBoard[7][0] = CPiece::BMa;
			m_ChessBoard[2][0] = m_ChessBoard[6][0] = CPiece::BXiang;
			m_ChessBoard[3][0] = m_ChessBoard[5][0] = CPiece::BShi;
			m_ChessBoard[4][0] = CPiece::BShuai;
			m_ChessBoard[1][2] = m_ChessBoard[7][2] = CPiece::BPao;
			m_ChessBoard[0][3] = m_ChessBoard[2][3] = m_ChessBoard[4][3] = m_ChessBoard[6][3] = m_ChessBoard[8][3] = CPiece::BBing;
		}
	}

	if (m_BoardLayout & OnlyBottomRed)
	{
		if (m_BoardLayout & SwapRedBetweenBlack)
		{
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::BChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::BMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::BXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::BShi;
			m_ChessBoard[4][9] = CPiece::BShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::BPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::BBing;
		}
		else {
			m_ChessBoard[0][9] = m_ChessBoard[8][9] = CPiece::RChe;
			m_ChessBoard[1][9] = m_ChessBoard[7][9] = CPiece::RMa;
			m_ChessBoard[2][9] = m_ChessBoard[6][9] = CPiece::RXiang;
			m_ChessBoard[3][9] = m_ChessBoard[5][9] = CPiece::RShi;
			m_ChessBoard[4][9] = CPiece::RShuai;
			m_ChessBoard[1][7] = m_ChessBoard[7][7] = CPiece::RPao;
			m_ChessBoard[0][6] = m_ChessBoard[2][6] = m_ChessBoard[4][6] = m_ChessBoard[6][6] = m_ChessBoard[8][6] = CPiece::RBing;
		}
	}


	return 0;
}

/*******************************************************************************************************
��������QiZiBianMa
��  �ܣ����ӱ����
��  ����
		 int *i�����̺�����[0-8]
		 int *j������������[0-9]
		 CPiece::ENUM_QiZi *QZ������
		 int *Code�����ӱ���
		 ENUM_BianMa��ö�ٳ�����BianMa:����(Ĭ��ֵ)��JieMa�����룩
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-2
ʱ  �䣺7:36:32
*******************************************************************************************************/
int CChineseChess::QiZiBianMa(int *i, int *j, CPiece::ENUM_QiZi *QZ, int *Code, ENUM_BianMa bianma)
{
	switch (bianma)
	{
	case BianMa:
		int val;
		if (CPiece::IsExistQiZi(*QZ))
		{
			val = sig(*QZ) * (*i + *j * 10 + abs(*QZ) * 100);
		}
		else
		{
			val = *i + *j * 10;
		}
		*Code = val;
		return val;
		break;
	case JieMa:
		*QZ = (CPiece::ENUM_QiZi)(*Code / 100);
		//TRACE(_T("CODE=%d,QZ=%d\n"), *Code, *QZ);
		int v;
		v = abs(*Code) % 100;
		*j = v / 10;
		*i = v % 10;
		return 0;
		break;
	}
	return 0;
}

bool CChineseChess::IsValidPosition(int i, int j)
{
	if (i < 0 || i > m_BoardRow - 1 || j < 0 || j > m_BoardColumn - 1)
	{   //����
		return false;
	}
	return true;
}

/*******************************************************************************************************
��������GoChess
��  �ܣ�����
��  ����
		 int i�����̸������[0-8]
		 int j�����̸�������[0-9]
����ֵ���ɹ�����true�����򷵻�false��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-10-5
ʱ  �䣺10:17:56
*******************************************************************************************************/
bool CChineseChess::GoChess(int i, int j)
{
	int code;
	if (IsGoChess(i, j))
	{ //����

		onGoChess(i, j, m_ChessBoard[i][j]); //�¼�

		QiZiBianMa(&i, &j, &m_ChessBoard[i][j], &code);
		m_iBuShu++;
		if (!m_bFuPang)
		{   //���浽�����
			if (m_iBuShu < m_QiJu.size())
			{
				m_QiJu[m_iBuShu] = code;
			}
			else//����
			{
				m_QiJu.push_back(code);//���浽�����
			}
		}

		// ��ʾ��ʾ��
		switch (m_WalkState)
		{
		case RedReadly:
			onPromptSound(Select);

			if(IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
				onCleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			if(IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
				onCleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			m_CurrentPositionX = -1;
			m_CurrentPositionY = -1;

			onDrawPrompt(i, j);

			m_WalkState = RedWalked;
			break;
		case RedWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);
			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_WalkState = BlackReadly;
			break;
		case BlackReadly:
			onPromptSound(Select);

			if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
				onCleanPrompt(m_PreviouPositionX, m_PreviouPositionY);
			if (IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
				onCleanPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_PreviouPositionX = i;
			m_PreviouPositionY = j;
			m_CurrentPositionX = -1;
			m_CurrentPositionY = -1;
			onDrawPrompt(i, j);

			m_WalkState = BlackWalked;
			break;
		case BlackWalked:
			m_CurrentPositionX = i;
			m_CurrentPositionY = j;

			m_ChessBoard[i][j] = m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY];
			m_ChessBoard[m_PreviouPositionX][m_PreviouPositionY] = CPiece::NoQiZi;

			onDrawPrompt(m_PreviouPositionX, m_PreviouPositionY);
			onDrawPrompt(m_CurrentPositionX, m_CurrentPositionY);

			m_WalkState = RedReadly;
			break;
		}
		return true;
	}
	else//������
	{
		onPromptSound(NoGo);
		return false;
	}
}

/*******************************************************************************************************
��������IsGoChess
��  �ܣ��ж��ܷ�����
��  ����
		 int i����ǰ�����λ��,������[0-8]
		 int j����ǰ�����λ��,������[0-9]
		 CPiece::ENUM_QiZi qz����ǰ����
����ֵ������������巵�� true,���򷵻� false
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-9-26
ʱ  �䣺10:47:40
*******************************************************************************************************/
bool CChineseChess::IsGoChess(int i, int j)
{
	if(!IsValidPosition(i, j))
	{   //����
		return false;
	}

	switch (m_WalkState)
	{
	case RedReadly:
		return CPiece::IsRedQiZi(m_ChessBoard[i][j]) ? true : false;
	case RedWalked:
		//��������,����ѡȡ
		if (CPiece::IsRedQiZi(m_ChessBoard[i][j]))
		{
			m_iBuShu--;//�ض�����ʱ������һλ��
			m_WalkState = RedReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://����
			onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://��������
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case CGoRule::BEIJIANGJUN://����
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case CGoRule::JIANGDUIMIAN://������
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case CGoRule::RETURNFALSE://�Ƿ�����
		default:
			return false;
		}

		break;
	case BlackReadly:
		return CPiece::IsBlackQiZi(m_ChessBoard[i][j]) ? true : false;
	case BlackWalked:
		//��������,����ѡȡ
		if (CPiece::IsBlackQiZi(m_ChessBoard[i][j]))
		{
			m_iBuShu--;//�ض�����ʱ������һλ��
			m_WalkState = BlackReadly;
			return true;
		}
		//�ж��ܷ�����
		switch (m_GoRule.GoChess(i, j, m_PreviouPositionX, m_PreviouPositionY, m_ChessBoard))
		{
		case CGoRule::JIANGJUN://����
			onPromptSound(JiangJun);
			return true;
		case CGoRule::RETURNTRUE://��������
			m_ChessBoard[i][j] ? onPromptSound(Eat) : onPromptSound(Go);
			return true;
		case CGoRule::BEIJIANGJUN://����
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case CGoRule::JIANGDUIMIAN://������
			onPromptMessage("�ⲽ�岻���ߣ�������Ҫ���ˡ�", "������");
			return false;
		case CGoRule::RETURNFALSE://�Ƿ�����
		default:
			return false;
		}

		break;
	}

	return false;
}