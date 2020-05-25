#include "FrmChineseChess.h"
#include "ui_FrmChineseChess.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPoint>

CFrmChineseChess::CFrmChineseChess(QWidget *parent) :
    QWidget(parent),
    CChineseChess(),
    ui(new Ui::CFrmChineseChess),
    m_QiPangColor(0, 0, 0),
    m_TiShiBoxColor(0, 255, 0)
{
    ui->setupUi(this);
        
    m_QiPangStartX = m_QiPangStartY = 0;
    m_QiPangDistance = 0;
    
    m_QiPangPicture.load(":/image/QIPANG");
    m_RedShuai.load(":/image/RSHUAI");
    m_RedShi.load(":/image/RSHI");
    m_RedXiang.load(":/image/RXIANG");
    m_RedMa.load(":/image/RMA");
    m_RedChe.load(":/image/RCHE");
    m_RedBing.load(":/image/RBING");
    m_RedPao.load(":/image/RPAO");
    m_BlackShuai.load(":/image/BSHUAI");
    m_BlackShi.load(":/image/BSHI");
    m_BlackXiang.load(":/image/BXIANG");
    m_BlackMa.load(":/image/BMA");
    m_BlackChe.load(":/image/BCHE");
    m_BlackBing.load(":/image/BZU");
    m_BlackPao.load(":/image/BPAO");

	m_Chu.load(":/image/CHU");
	m_He.load(":/image/HE");
	m_Han.load(":/image/HAN");
	m_Jie.load(":/image/JIE");
	m_KL.load(":/image/KL");
}

CFrmChineseChess::~CFrmChineseChess()
{
    delete ui;
}

void CFrmChineseChess::mouseReleaseEvent(QMouseEvent *event)
{
	int i = 0, j = 0;
	long x = 0, y = 0;
	QPoint p = event->pos();
	x = p.x();
	y = p.y();
	ConvertCoordinate(&x, &y, &i, &j);
	if (GoChess(i, j))
	{

	}
	this->update();
}

void CFrmChineseChess::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    DrawQiPang(&painter, rect());
}

void CFrmChineseChess::resizeEvent(QResizeEvent *event)
{
    QSize s = event->size();
    SetQiPang(s.width(), s.height());
}

int CFrmChineseChess::onPromptSound(PROMPT_SOUND sound)
{
	return 0;
}

int CFrmChineseChess::onPromptMessage(CGoRule::ENUM_ReturnValue val)
{
    
	return 0;
}

int CFrmChineseChess::onCleanPrompt(int i, int j)
{
	int nRet = 0;

	return nRet;
}

int CFrmChineseChess::onDrawPrompt(int i, int j)
{
	int nRet = 0;

	return nRet;
}

int CFrmChineseChess::onGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
	return 0;
}

/*******************************************************************************************************
函数名：ConvertCoordinate
功  能：坐标转换
参  数：
		 long *x：设备横坐标
		 long *y：设备纵坐标
		 int *i：棋盘横坐标[0,8]
		 int *j：棋盘纵坐标[0,9]
		 ENUM_ConvertCoordinate eCC：转换方式
		 XYToIJ:从设备坐标转换到棋盘坐标(默认值)
		 IJToXY:从棋盘坐标转换到设备坐标
返回值：返回真值。
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-24
时  间：15:01:37
*******************************************************************************************************/
bool CFrmChineseChess::ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC)
{
	switch (eCC)
	{
	case XYToIJ:
		*i = (*x - m_QiPangStartX + m_QiPangDistance / 2) / m_QiPangDistance;
		*j = (*y - m_QiPangStartY + m_QiPangDistance / 2) / m_QiPangDistance;
		break;
	case IJToXY:
		*x = m_QiPangStartX + *i * m_QiPangDistance;
		*y = m_QiPangStartY + *j * m_QiPangDistance;
		break;
	}
	return true;
}

/*******************************************************************************************************
函数名：SetQiPang
功  能：设置棋盘位置
参  数：
		 int width：控件窗口宽度
		 int height：控件窗口高度
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2020-5-12
时  间：11:27:12
*******************************************************************************************************/
bool CFrmChineseChess::SetQiPang(int width, int height)
{
	if (width > height)
	{
		m_QiPangDistance = height / 11;
		m_QiPangStartX = (width - m_QiPangDistance * 10) / 2 + m_QiPangDistance;
		m_QiPangStartY = m_QiPangDistance;
	}
	else
	{
		m_QiPangDistance = width / 10;
		m_QiPangStartX = m_QiPangDistance;
		m_QiPangStartY = (height - m_QiPangDistance * 11) / 2 + m_QiPangDistance;
	}
	return true;
}

/*******************************************************************************************************
函数名：DrawQiPang
功  能：画棋盘
参  数：
		 CDC *pdc：设备上下文
		 CRect rcBounds：控件区域(包括边界)
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：17:10:23
*******************************************************************************************************/
void CFrmChineseChess::DrawQiPang(QPainter *pPainter, QRect rect)
{
	if(nullptr == pPainter)
        return;

    pPainter->save();
    
    pPainter->drawImage(this->rect(), m_QiPangPicture, m_QiPangPicture.rect());
    
	int i, j;
	for (i = 0; i < 9; i++) //纵格
	{
		if (i == 0 || i == 8)
		{
            QPen pen;
            pen.setColor(m_QiPangColor);
            pen.setWidth(2);
            pPainter->setPen(pen);
            pPainter->drawLine(m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY, 
                               m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY + 9 * m_QiPangDistance);
		}
		else
		{
            QPen pen(QBrush(m_QiPangColor), 1);
            pPainter->setPen(pen);
            pPainter->drawLine(m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY, 
                               m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY + 4 * m_QiPangDistance);
            pPainter->drawLine(m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY + 5 * m_QiPangDistance,
                               m_QiPangStartX + i * m_QiPangDistance,
                               m_QiPangStartY + 9 * m_QiPangDistance);
		}
	}

	for (i = 0; i < 10; i++)  //横格
	{
        QPen pen;
        pen.setColor(m_QiPangColor);
        if (i == 0 || i == 9)
		{
			pen.setWidth(2);
		}
		else
		{
			pen.setWidth(1);
		}
        
        pPainter->setPen(pen);

		pPainter->drawLine(m_QiPangStartX,
			m_QiPangStartY + i * m_QiPangDistance,
                           m_QiPangStartX + 8 * m_QiPangDistance,
			m_QiPangStartY + i * m_QiPangDistance);

	}

    //九宫
    QPen pen;
    pen.setColor(m_QiPangColor);
    pen.setWidth(1);
    pPainter->setPen(pen);
    pPainter->drawLine(m_QiPangStartX + 3 * m_QiPangDistance,
                       m_QiPangStartY,
                       m_QiPangStartX + 5 * m_QiPangDistance,
                       m_QiPangStartY + 2 * m_QiPangDistance);
    
    pPainter->drawLine(m_QiPangStartX + 5 * m_QiPangDistance,
                       m_QiPangStartY,
                       m_QiPangStartX + 3 * m_QiPangDistance,
                       m_QiPangStartY + 2 * m_QiPangDistance);
    
    pPainter->drawLine(m_QiPangStartX + 3 * m_QiPangDistance,
                       m_QiPangStartY + 7 * m_QiPangDistance,
                       m_QiPangStartX + 5 * m_QiPangDistance,
                       m_QiPangStartY + 9 * m_QiPangDistance);
    
    pPainter->drawLine(m_QiPangStartX + 5 * m_QiPangDistance,
                       m_QiPangStartY + 7 * m_QiPangDistance,
                       m_QiPangStartX + 3 * m_QiPangDistance,
                       m_QiPangStartY + 9 * m_QiPangDistance);
    

	//星位
	DrawXinWei(pPainter, 1, 2);
	DrawXinWei(pPainter, 7, 2);
	DrawXinWei(pPainter, 1, 7);
	DrawXinWei(pPainter, 7, 7);
	DrawXinWei(pPainter, 0, 3, Right_XinWei);
	DrawXinWei(pPainter, 2, 3);
	DrawXinWei(pPainter, 4, 3);
	DrawXinWei(pPainter, 6, 3);
	DrawXinWei(pPainter, 8, 3, Left_XinWei);
	DrawXinWei(pPainter, 0, 6, Right_XinWei);
	DrawXinWei(pPainter, 2, 6);
	DrawXinWei(pPainter, 4, 6);
	DrawXinWei(pPainter, 6, 6);
	DrawXinWei(pPainter, 8, 6, Left_XinWei);

	//楚河汉界
	//楚
	DrawPicture(pPainter, 7, 4, m_Chu, true);
	//河
	DrawPicture(pPainter, 6, 4, m_He, true);
	//汉
	DrawPicture(pPainter, 1, 4, m_Han, true);
	//界
	DrawPicture(pPainter, 2, 4, m_Jie, true);
	  //KL
	DrawPicture(pPainter, 4, 4, m_KL, true);

	//画棋子
	for (i = 0; i < 9; i++)
		for (j = 0; j < 10; j++)
		{
			DrawQiZi(pPainter, i, j, m_ChessBoard[i][j]);
		}

	//显示提示框
	if (IsValidPosition(m_PreviouPositionX, m_PreviouPositionY))
		DrawTiShiBox(pPainter, m_PreviouPositionX, m_PreviouPositionY);
	if (IsValidPosition(m_CurrentPositionX, m_CurrentPositionY))
		DrawTiShiBox(pPainter, m_CurrentPositionX, m_CurrentPositionY);

    pPainter->restore();
}

/*******************************************************************************************************
函数名：DrawXinWei
功  能：画星位
参  数：
		 CDC *pdc：设备上下文
		 int i：星位的横坐标[0-8]
		 int j：星位的纵坐标[0-9]
		 ENUM_XINWEI xinwei：画的位置取下列值勤之一:
		 XinWei:全画(默认值),
		 Left_XinWei:画左边的星位
		 Right_XinWei:画右边的星位
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-8-18
时  间：17:56:58
*******************************************************************************************************/
void CFrmChineseChess::DrawXinWei(QPainter *pPainter, int i, int j, ENUM_XINWEI xinwei)
{
	int d, ds;
	long x, y;

	d = m_QiPangDistance * 4 / 10;
	ds = m_QiPangDistance * 2 / 10;

	ConvertCoordinate(&x, &y, &i, &j, IJToXY);

    QPen pen;
    pen.setColor(m_QiPangColor);
    pen.setWidth(1);
    pPainter->setPen(pen);
    
    if (xinwei != Left_XinWei)
    {
		pPainter->drawLine(x + ds, y + ds, x + d, y + ds);
        pPainter->drawLine(x + ds, y - ds, x + d, y - ds);
        
        pPainter->drawLine(x + ds, y + ds, x + ds, y + d);
        
        pPainter->drawLine(x + ds, y - ds, x + ds, y - d);
    }
    
    if (xinwei != Right_XinWei)
    {
        pPainter->drawLine(x - ds, y - ds, x - ds, y - d);
        
        pPainter->drawLine(x - ds, y + ds, x - ds, y + d);
        
        pPainter->drawLine(x - ds, y + ds, x - d, y + ds);
        
        pPainter->drawLine(x - ds, y - ds, x - d, y - ds);
    }
}

/*******************************************************************************************************
函数名：DrawTiShiBox
功  能：画提示框
参  数：
		 int i：棋盘横坐标[0-8]
		 int j：棋盘纵坐标[0-9]
返回值：成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：04-9-2
时  间：21:01:23
*******************************************************************************************************/
bool CFrmChineseChess::DrawTiShiBox(QPainter *pPainter, int i, int j)
{
	//	CClientDC dc(this);

	long m_X, m_Y, m_L = m_QiPangDistance / 2;
    
    QPen pen;
    pen.setColor(m_TiShiBoxColor);
    pen.setWidth(1);
    pPainter->setPen(pen);
    
	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	pPainter->drawLine(m_X - m_L, m_Y - m_L, m_X - m_L, m_Y - m_L / 2);

	pPainter->drawLine(m_X - m_L, m_Y - m_L, m_X - m_L / 2, m_Y - m_L);

	pPainter->drawLine(m_X + m_L, m_Y + m_L, m_X + m_L, m_Y + m_L / 2);

	pPainter->drawLine(m_X + m_L, m_Y + m_L, m_X + m_L / 2, m_Y + m_L);

	pPainter->drawLine(m_X - m_L, m_Y + m_L, m_X - m_L, m_Y + m_L / 2);

	pPainter->drawLine(m_X - m_L, m_Y + m_L, m_X - m_L / 2, m_Y + m_L);

	pPainter->drawLine(m_X + m_L, m_Y - m_L, m_X + m_L, m_Y - m_L / 2);

	pPainter->drawLine(m_X + m_L, m_Y - m_L, m_X + m_L / 2, m_Y - m_L);

	return true;
}

/*******************************************************************************************************
函数名：DrawQiZi
功  能：画棋子
参  数：
		 int i：棋子横坐标[0-8]
		 int j：棋子纵坐标[0-9]
		 CPiece::ENUM_QiZi eQiZi：棋子
返回值：如果成功返回 true,否则返回 false
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-1
时  间：19:47:24
*******************************************************************************************************/
bool CFrmChineseChess::DrawQiZi(QPainter *pPainter, int i, int j, CPiece::ENUM_QiZi eQiZi)
{

	QImage qz;
#pragma warning( disable : 4806 )

	switch (eQiZi)
	{
	case CPiece::NoQiZi:
		return false;
	case CPiece::RShuai:
		qz = m_RedShuai;
		break;
	case CPiece::RShi:
		qz = m_RedShi;
		break;
	case CPiece::RXiang:
		qz = m_RedXiang;
		break;
	case CPiece::RMa:
		qz = m_RedMa;
		break;
	case CPiece::RChe:
		qz = m_RedChe;
		break;
	case CPiece::RPao:
		qz = m_RedPao;
		break;
	case CPiece::RBing:
		qz = m_RedBing;
		break;
	case CPiece::BShuai:
		qz = m_BlackShuai;
		break;
	case CPiece::BShi:
		qz = m_BlackShi;
		break;
	case CPiece::BXiang:
		qz = m_BlackXiang;
		break;
	case CPiece::BMa:
		qz = m_BlackMa;
		break;
	case CPiece::BChe:
		qz = m_BlackChe;
		break;
	case CPiece::BPao:
		qz = m_BlackPao;
		break;
	case CPiece::BBing:
		qz = m_BlackBing;
		break;
	}

#pragma warning( default : 4806 )

	if (!qz.isNull())
	{
		return DrawPicture(pPainter, i, j, qz);
	}
	else
	{
		return false;
	}
}


/*******************************************************************************************************
函数名：DrawPicture
功  能：画图片
参  数：
		 CDC *pdc：设备上下文
		 int i：图片位置横坐标[0-8]
		 int j：图片位置纵坐标[0-9]
		 CBitmap *pbmp：图片指针
		 BOOL CHHJKL：画楚河汉界（默认值为 false）
返回值：成功返回 true
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-1
时  间：18:59:53
*******************************************************************************************************/
bool CFrmChineseChess::DrawPicture(QPainter *pPainter, int i, int j, QImage bmp, bool CHHJKL)
{
	long m_X, m_Y;

	ConvertCoordinate(&m_X, &m_Y, &i, &j, IJToXY);
	if (CHHJKL) //画楚河汉界
	{
		m_X -= m_QiPangDistance / 2;
	}
	else
	{
		m_X -= m_QiPangDistance / 2;
		m_Y -= m_QiPangDistance / 2;
	}

    QRect r(m_X, m_Y, m_QiPangDistance, m_QiPangDistance);
    pPainter->drawImage(r, bmp, bmp.rect());
	
	return true;
}
