// 作者：康林 <kl222@126.com>

#ifndef FRMCHINESECHESS_H
#define FRMCHINESECHESS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDateTime>
#include <QTranslator>

#include "ChineseChess.h"
#include "chinesechessqt_export.h"

namespace Ui {
class CFrmChineseChess;
}

/*!
 * \brief 中国象棋窗体，完成中国象棋的界面
 * \note
 *   \li 在程序开始时，仅调用一次 InitResource
 *   \li 在程序结束时，仅调用一次 CleanResource
 */
class CHINESECHESSQT_EXPORT CFrmChineseChess
        : public QWidget, public CChineseChess
{
    Q_OBJECT
    Q_PROPERTY(QString RedName READ GetRedName WRITE SetRedName)
    Q_PROPERTY(QString BlackName READ GetBlackName WRITE SetBlackName)
    Q_PROPERTY(QDateTime StartTime READ GetStartTime WRITE SetStartTime)
    Q_PROPERTY(QDateTime EndTime READ GetEndTime WRITE SetEndTime)
    
public:
    explicit CFrmChineseChess(QWidget *parent = nullptr);
    virtual ~CFrmChineseChess() override;
    
    //! @{ \name 资源
    /*!
     * \brief 初始化资源，仅在程序开始时调用一次
     * \param szLanguage: 使用语言
     * \return 
     */
    static int InitResource(const QString szLanguage);
    //! 清理资源，仅在程序结束时调用一次
    static int CleanResource();
    //! @}

    //! @{
    //!  \name 棋局信息

    //! 得到开始时间
    QDateTime GetStartTime();
    int SetStartTime(const QDateTime &t);
    QDateTime GetEndTime();
    int SetEndTime(const QDateTime &t);
    QString GetRedName();
    int SetRedName(const QString &name);
    QString GetBlackName();
    int SetBlackName(const QString &name);

    //! @}

    void AboutBox();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    virtual int onPromptSound(PROMPT_SOUND sound) override;
    virtual int onPromptMessage(CGoRule::ENUM_ReturnValue val) override;

    virtual int onCleanPrompt(int i, int j) override;
    virtual int onDrawPrompt(int i, int j) override;
    virtual int onGoChess(int i, int j, CPiece::ENUM_QiZi chess) override;

Q_SIGNALS:
    void sigGoChess(int i, int j, CPiece::ENUM_QiZi chess);

private:
    Ui::CFrmChineseChess *ui;
    
    int m_QiPangStartX;     //!< 棋盘的开始横坐标
    int m_QiPangStartY;     //!< 棋盘的开始横坐标
    int m_QiPangDistance;   //!< 棋盘格的距离

    QColor m_QiPangColor;   //!< 棋盘格的颜色
    QColor m_TiShiBoxColor; //!< 提示框的颜色

    QImage m_QiPangPicture; //!< 棋盘背景图片
    //CPictureHolder m_QiPangPictureHolder; //棋盘背景图片的CPictureHolder对象

    //! @{
    //! \name 棋子图片

    QImage m_RedShuai;      //!< 红帅
    QImage m_RedShi;        //!< 红仕
    QImage m_RedXiang;      //!< 红相
    QImage m_RedMa;         //!< 红马
    QImage m_RedChe;        //!< 红车
    QImage m_RedBing;       //!< 红兵
    QImage m_RedPao;        //!< 红炮

    QImage m_BlackShuai;    //!< 黑帅
    QImage m_BlackShi;      //!< 黑仕
    QImage m_BlackXiang;    //!< 黑相
    QImage m_BlackMa;       //!< 黑马
    QImage m_BlackChe;      //!< 黑车
    QImage m_BlackBing;     //!< 黑兵
    QImage m_BlackPao;      //!< 黑炮

    //! @}

    //! @{
    //!  \name 楚河汉界图片

    QImage m_Chu;           //!< 楚
    QImage m_He;            //!< 河
    QImage m_Han;           //!< 汉
    QImage m_Jie;           //!< 界
    QImage m_KL;            //!< 版本图片

    //! @}

    //! 坐标转换
    enum ENUM_ConvertCoordinate { XYToIJ, IJToXY };
    bool ConvertCoordinate(long *x, long *y, int *i, int *j, ENUM_ConvertCoordinate eCC = XYToIJ);
    bool SetQiPang(int width, int height);

    //! 棋盘星位
    enum ENUM_XINWEI { XinWei, Left_XinWei, Right_XinWei };
    // 画星位
    void DrawXinWei(QPainter *pPainter, int i, int j, ENUM_XINWEI xinwei = XinWei);
    // 画提示框
    bool DrawTiShiBox(QPainter *pPainter, int i, int j);
    int DrawQiZi(QPainter *pPainter, int i, int j, CPiece::ENUM_QiZi eQiZi);
    void DrawQiPang(QPainter *pPainter, QRect rect);
    int DrawPicture(QPainter *pPainter, int i, int j, QImage image, bool CHHJKL = false);
    // 在指定位置绘图
    int DrawImage(QPainter *pPainter, QRect rect, QImage image);
    // 设置 QImage 透明
    int SetTransparentImage(QImage &image, const QColor& col = QColor(255, 255, 255));
    // 设置 Pixmap 透明
    int SetTransparentPixmap(QPixmap &pixmap, const QColor &col = QColor(255, 255, 255));    
};

#endif // FRMCHINESECHESS_H
