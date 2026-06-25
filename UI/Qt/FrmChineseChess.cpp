// 作者：康林 <kl222@126.com>

#include "FrmChineseChess.h"
#include "ui_FrmChineseChess.h"
#include "DlgAbout/DlgAbout.h"
#include "RabbitCommonTools.h"

#include <QResizeEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    #include <QSoundEffect>
#else
    #include <QSound>
#endif
#include <QBitmap>

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
    SetTransparentImage(m_QiPangPicture);
    m_RedShuai.load(":/image/RSHUAI");
    //SetTransparentImage(m_RedShuai);
    m_RedShi.load(":/image/RSHI");
    //SetTransparentImage(m_RedShi);
    m_RedXiang.load(":/image/RXIANG");
    //SetTransparentImage(m_RedXiang);
    m_RedMa.load(":/image/RMA");
    //SetTransparentImage(m_RedMa);
    m_RedChe.load(":/image/RCHE");
    //SetTransparentImage(m_RedChe);
    m_RedBing.load(":/image/RBING");
    //SetTransparentImage(m_RedBing);
    m_RedPao.load(":/image/RPAO");
    //SetTransparentImage(m_RedPao);
    m_BlackShuai.load(":/image/BSHUAI");
    //SetTransparentImage(m_BlackShuai);
    m_BlackShi.load(":/image/BSHI");
    //SetTransparentImage(m_BlackShi);
    m_BlackXiang.load(":/image/BXIANG");
    //SetTransparentImage(m_BlackXiang);
    m_BlackMa.load(":/image/BMA");
    //SetTransparentImage(m_BlackMa);
    m_BlackChe.load(":/image/BCHE");
    //SetTransparentImage(m_BlackChe);
    m_BlackBing.load(":/image/BZU");
    //SetTransparentImage(m_BlackBing);
    m_BlackPao.load(":/image/BPAO");
    //SetTransparentImage(m_BlackPao);

    m_Chu.load(":/image/CHU");
    SetTransparentImage(m_Chu);
    m_He.load(":/image/HE");
    SetTransparentImage(m_He);
    m_Han.load(":/image/HAN");
    SetTransparentImage(m_Han);
    m_Jie.load(":/image/JIE");
    SetTransparentImage(m_Jie);
    m_KL.load(":/image/KL");
}

CFrmChineseChess::~CFrmChineseChess()
{
    delete ui;
}

static QSharedPointer<QTranslator> g_Translator;
int CFrmChineseChess::InitResource(const QString szLanguage)
{
    Q_INIT_RESOURCE(ResourceChineseChess);
#if (defined(DEBUG) || defined(_DEBUG)) && !defined (BUILD_SHARED_LIBS)
    Q_INIT_RESOURCE(translations_ChineseChessQt);
#endif
    g_Translator = RabbitCommon::CTools::Instance()->InstallTranslator(
        "ChineseChessQt",
        RabbitCommon::CTools::TranslationType::Library,
        "",
        szLanguage);
    if(g_Translator)
        return 0;
    return -1;
}

int CFrmChineseChess::CleanResource()
{
    RabbitCommon::CTools::Instance()->RemoveTranslator(g_Translator);

#if (defined(DEBUG) || defined(_DEBUG)) && !defined (BUILD_SHARED_LIBS)
    Q_CLEANUP_RESOURCE(translations_ChineseChessQt);
#endif
    Q_CLEANUP_RESOURCE(ResourceChineseChess);
    return 0;
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
}

void CFrmChineseChess::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    
    // 设置平滑模式
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    DrawQiPang(&painter, rect());
}

void CFrmChineseChess::resizeEvent(QResizeEvent *event)
{
    QSize s = event->size();
    SetQiPang(s.width(), s.height());
}

int CFrmChineseChess::onPromptSound(PROMPT_SOUND sound)
{
    QString szFile;
    switch (sound)
    {
    case JiangJun:
        szFile = ":/sound/CHECK";
        break;
    case Eat:
        szFile = ":/sound/EAT";
        break;
    case Go:
        szFile = ":/sound/GO";
        break;
    case NoGo:
        szFile = ":/sound/DEAD";
        break;
    case Select:
        szFile = ":/sound/SELECT";
        break;
    default:
        return 0;
    }
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    static QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(szFile));
    //effect.setLoopCount(1);
    //effect.setVolume(1);
    if(effect.isPlaying())
        effect.stop();
    effect.play();
#else
    QSound::play(szFile);
#endif
    return 0;
}

int CFrmChineseChess::onPromptMessage(CGoRule::ENUM_ReturnValue val)
{
    QMessageBox msg(this);
    switch (val)
    {
    case CGoRule::BEIJIANGJUN:
        msg.setText(tr("This step cannot be taken, otherwise you will lose"));
        msg.setWindowTitle(tr("checked"));
        break;
    case CGoRule::JIANGDUIMIAN:
        msg.setText(tr("This step cannot be taken, otherwise you will lose"));
        msg.setWindowTitle(tr("Opposite"));
        break;
    default:
        return 0;
    }
    msg.exec();
    return 0;
}

int CFrmChineseChess::onCleanPrompt(int i, int j)
{
    Q_UNUSED(i)
    Q_UNUSED(j)
    int nRet = 0;
    this->update();
    return nRet;
}

int CFrmChineseChess::onDrawPrompt(int i, int j)
{
    Q_UNUSED(i)
    Q_UNUSED(j)
    int nRet = 0;
    this->update();
    return nRet;
}

int CFrmChineseChess::onGoChess(int i, int j, CPiece::ENUM_QiZi chess)
{
    emit sigGoChess(i, j, chess);
    return 0;
}

void CFrmChineseChess::AboutBox()
{
    CDlgAbout about(this);
    about.m_AppIcon = QImage(":/image/Chess");
    about.m_szAppName = tr("Chinese chess control");
    about.m_szHomePage = "https://github.com/KangLin/ChineseChessControl";
    about.m_szCopyrightTime = "1994 - " + QString::number(QDate::currentDate().year());
#ifdef ChineseChessQt_VERSION
    about.m_szVersion = ChineseChessQt_VERSION;
#endif
#ifdef ChineseChessQt_REVISION
    about.m_szVersionRevision = ChineseChessQt_REVISION;
#endif
    RC_SHOW_WINDOW(&about);
}

QDateTime CFrmChineseChess::GetStartTime()
{
    time_t t = CChineseChess::GetStartTime();
    QDateTime time;
    time.setMSecsSinceEpoch(t);
    return time;
}

int CFrmChineseChess::SetStartTime(const QDateTime &t)
{
    return CChineseChess::SetStartTime(t.toMSecsSinceEpoch());
}

QDateTime CFrmChineseChess::GetEndTime()
{
    QDateTime t;
    t.setMSecsSinceEpoch(CChineseChess::GetEndTime());
    return t;
}

int CFrmChineseChess::SetEndTime(const QDateTime &t)
{
    return CChineseChess::SetEndTime(t.toMSecsSinceEpoch());
}

QString CFrmChineseChess::GetRedName()
{
    return CChineseChess::GetRedName().c_str();
}

int CFrmChineseChess::SetRedName(const QString &name)
{
    return CChineseChess::SetRedName(name.toStdString().c_str());
}

QString CFrmChineseChess::GetBlackName()
{
    return CChineseChess::GetBlackName().c_str();
}

int CFrmChineseChess::SetBlackName(const QString &name)
{
    return CChineseChess::SetBlackName(name.toStdString().c_str());
}

/*!
 * \brief 坐标转换
 * \param x: 设备横坐标
 * \param y: 设备纵坐标
 * \param i: 棋盘横坐标[0,8]
 * \param j: 棋盘纵坐标[0,9]
 * \param eCC: 转换方式
 *        - XYToIJ: 从设备坐标转换到棋盘坐标(默认值)
 *        - IJToXY: 从棋盘坐标转换到设备坐标
 * \return 返回真值。成功：返回 true；失败：返回 false。
 */
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

/*!
 * \brief 设置棋盘位置
 * \param width: 控件窗口宽度
 * \param height: 控件窗口高度
 * \return 返回真值。成功：返回 true；失败：返回 false。
 */
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

/*!
 * \brief 画棋盘
 * \param pPainter: 设备上下文
 * \param rect: 控件区域(包括边界)
 */
void CFrmChineseChess::DrawQiPang(QPainter *pPainter, QRect rect)
{
    if(nullptr == pPainter)
        return;

    pPainter->save();
    
    DrawImage(pPainter, rect, m_QiPangPicture);
    
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

/*!
 * \brief 画星位
 * \param pPainter: 设备上下文
 * \param i: 星位的横坐标[0-8]
 * \param j: 星位的纵坐标[0-9]
 * \param xinwei: 画的位置取下列值勤之一:
 *        - XinWei:全画(默认值)
 *        - Left_XinWei:画左边的星位
 *        - Right_XinWei:画右边的星位
 */
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

/*!
 * \brief 画提示框
 * \param pPainter: 设备上下文
 * \param i: 棋盘横坐标[0-8]
 * \param j: 棋盘纵坐标[0-9]
 * \return 返回真值。成功：返回 true；失败：返回 false。
 */
bool CFrmChineseChess::DrawTiShiBox(QPainter *pPainter, int i, int j)
{
    //    CClientDC dc(this);

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

/*!
 * \brief 画棋子
 * \param pPainter: 设备上下文
 * \param i: 棋盘横坐标[0-8]
 * \param j: 棋盘纵坐标[0-9]
 * \param eQiZi: 棋子
 * \return 如果成功返回 0,否则返回 非零
 */
int CFrmChineseChess::DrawQiZi(QPainter *pPainter, int i, int j, CPiece::ENUM_QiZi eQiZi)
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
        return DrawPicture(pPainter, i, j, qz);
    
    return -1;
}

/*!
 * \brief 画图片
 * \param pPainter
 * \param i: 图片位置横坐标[0-8]
 * \param j: 图片位置纵坐标[0-9]
 * \param image: 图片
 * \param CHHJKL: 画楚河汉界（默认值为 false）
 * \return 如果成功返回 0,否则返回 非零
 */
int CFrmChineseChess::DrawPicture(QPainter *pPainter, int i, int j, QImage image, bool CHHJKL)
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
    return DrawImage(pPainter, r, image);
}

/**
 * @brief 在指定位置绘图
 * @param pPainter: 设备上下文
 * @param rect: 绘图区域
 * @param image: 图片
 * @return 如果成功返回 0,否则返回 非零
 */
int CFrmChineseChess::DrawImage(QPainter *pPainter, QRect rect, QImage image)
{
    pPainter->drawImage(rect, image);
    
    ////设置平滑缩放图片，也可以用 QPainter::setRenderHint 设置 Qpainter
    //QImage bmp = image.scaled(rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //pPainter->drawImage(rect, bmp, bmp.rect());
    
    //QPixmap p = QPixmap::fromImage(image);
    //p = p.scaled(r.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //pPainter->drawPixmap(r, p, p.rect());
    return 0;
}

/**
 * @brief 设置 QImage 透明
 * @param image: 
 * @param col: 透明颜色
 * @return 如果成功返回 0,否则返回 非零
 */
int CFrmChineseChess::SetTransparentImage(QImage &image, const QColor &col)
{
    //设置位图透明
    QImage mask = image.createMaskFromColor(col.rgb(), Qt::MaskOutColor);
    image.setAlphaChannel(mask);
    return 0;
}

/**
 * @brief 设置 Pixmap 透明
 * @param pixmap: 
 * @param col: 透明颜色
 * @return 如果成功返回 0,否则返回 非零
 */
int CFrmChineseChess::SetTransparentPixmap(QPixmap &pixmap, const QColor &col)
{
    QBitmap bmp = pixmap.createMaskFromColor(col, Qt::MaskOutColor);
    pixmap.setMask(bmp);
    return 0;
}
