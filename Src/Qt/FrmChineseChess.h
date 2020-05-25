#ifndef FRMCHINESECHESS_H
#define FRMCHINESECHESS_H

#include <QWidget>
#include <QImage>
#include <QPainter>

#include "ChineseChess.h"

namespace Ui {
class CFrmChineseChess;
}

class CFrmChineseChess : public QWidget, public CChineseChess
{
    Q_OBJECT
    
public:
    explicit CFrmChineseChess(QWidget *parent = nullptr);
    virtual ~CFrmChineseChess();
    
protected:
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;

protected:
	virtual int onPromptSound(PROMPT_SOUND sound);
	virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val);

	virtual int onCleanPrompt(int i, int j);
	virtual int onDrawPrompt(int i, int j);
	virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess);

private:
    Ui::CFrmChineseChess *ui;
    
    int m_QiPangStartX;   //棋盘的开始横坐标
    int m_QiPangStartY;   //棋盘的开始横坐标
    int m_QiPangDistance; //棋盘格的距离
    
    QColor m_QiPangColor;
    QColor m_TiShiBoxColor;
    
    QImage m_QiPangPicture;			  //棋盘背景图片
    //CPictureHolder m_QiPangPictureHolder; //棋盘背景图片的CPictureHolder对象
    
    //棋子图片
    QImage m_RedShuai;     //红帅
    QImage m_RedShi;       //红仕
    QImage m_RedXiang;     //红相
    QImage m_RedMa;        //红马
    QImage m_RedChe;       //红车
    QImage m_RedBing;      //红兵
    QImage m_RedPao;       //红炮
    
    QImage m_BlackShuai;   //黑帅
    QImage m_BlackShi;     //黑仕
    QImage m_BlackXiang;   //黑相
    QImage m_BlackMa;      //黑马
    QImage m_BlackChe;     //黑车
    QImage m_BlackBing;    //黑兵
    QImage m_BlackPao;     //黑炮
    
	QImage m_Chu;
	QImage m_He;
	QImage m_Han;
	QImage m_Jie;
	QImage m_KL;
    
    //坐标转换
    enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
    bool ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);
    bool SetQiPang(int width, int height);
    
    //棋盘星位
    enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
    void DrawXinWei(QPainter *pPainter, int i, int j, ENUM_XINWEI xinwei = XinWei);
    bool DrawTiShiBox(QPainter *pPainter, int i, int j);
    bool DrawPicture(QPainter *pPainter, int i, int j, QImage pbmp, bool CHHJKL = false);
    bool DrawQiZi(QPainter *pPainter, int i, int j, CPiece::ENUM_QiZi eQiZi);
    void DrawQiPang(QPainter *pPainter, QRect rect);
    
//    void InvalidateRectage(int i, int j);
    
//    bool PromptSound(LPCTSTR ID = NULL);
    
};

#endif // FRMCHINESECHESS_H
