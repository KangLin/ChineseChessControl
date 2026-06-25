#include <QMessageBox>
#include <QCursor>
#include <QToolButton>
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include "DlgAbout.h"
#include "FrmUpdater.h"

#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Chess(this)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RabbitCommon::CTools::AddStyleMenu(ui->menuTools);
    ui->menuTools->addMenu(RabbitCommon::CTools::GetLogMenu(this));

#if defined(Q_OS_ANDROID) && QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    auto pTbMenu = new QToolButton(ui->toolBar);
    pTbMenu->setFocusPolicy(Qt::NoFocus);
    pTbMenu->setPopupMode(QToolButton::InstantPopup);
    //m_pTbMenu->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    pTbMenu->setText(tr("menu")); //tr("⋮"));
    pTbMenu->setIcon(QIcon::fromTheme("menu"));
    pTbMenu->setToolTip(tr("menu"));
    pTbMenu->setStatusTip(tr("menu"));
    QMenu *pMenu = new QMenu(pTbMenu);
    pMenu->addActions(this->menuBar()->actions());
    pTbMenu->setMenu(pMenu);
    ui->toolBar->addWidget(pTbMenu);
#endif

    //m_Chess.SetBoardLayout(CChineseChess::TopRedAndBottomBlack);
    this->setCentralWidget(&m_Chess);
    ui->actionPrompt_sound_S->setChecked(m_Chess.getEnablePromptSound());
    ui->actionPrompt_message_M->setChecked(m_Chess.getEnablePromptMessage());

    CFrmUpdater updater;
    ui->actionUpdate_U->setIcon(updater.windowIcon());
    RabbitCommon::CTools::Instance()->RestoreWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    RabbitCommon::CTools::Instance()->SaveWidget(this);
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionOpen_O_triggered()
{
    QString szFile = QFileDialog::getOpenFileName(this, tr("Open chess game"));
    if(szFile.isEmpty()) return;
    int nRet = m_Chess.LoadChessGame(szFile.toStdString().c_str());
    if(nRet) return;
    QMessageBox::information(
        this, "Load chess game",
        tr("Load chess game from file %1 successfully!").arg(szFile));
    m_Chess.update();
}

void MainWindow::on_actionSave_S_triggered()
{
    QString szFile = QFileDialog::getSaveFileName(
        this, tr("Save chess game"), QString(),
        tr("Chinese chess control file(*.ccc);; Portable game notation file(*.pgn);; All files(*.*)"));
    if(szFile.isEmpty()) return;
    int nRet = m_Chess.SaveChessGame(szFile.toStdString().c_str());
    if(nRet) return;
    QMessageBox::information(
        this, tr("Save chess game"),
        tr("Save chess game to file %1 successfully!").arg(szFile));
}

void MainWindow::on_actionPrevious_P_triggered()
{
    m_Chess.PreviouStep();
}

void MainWindow::on_actionNext_N_triggered()
{
    m_Chess.NextStep();
}

void MainWindow::on_actionExit_E_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionAbout_A_triggered()
{
    CDlgAbout about(this);
    about.m_AppIcon = QImage(":/image/Chess");
    about.m_szAppName = tr("Chinese chess");
    about.m_szHomePage = "https://github.com/KangLin/ChineseChessControl";
    about.m_szCopyrightStartTime = "1994";
#ifdef ChineseChessApp_VERSION
    about.m_szVersion = ChineseChessApp_VERSION;
#endif
#ifdef ChineseChessApp_REVISION
    about.m_szVersionRevision = ChineseChessApp_REVISION;
#endif
    RC_SHOW_WINDOW(&about);
    
    //m_Chess.AboutBox();
}

void MainWindow::on_actionPrompt_sound_S_triggered(bool checked)
{
    m_Chess.EnablePromptSound(checked);
}

void MainWindow::on_actionPrompt_message_M_triggered(bool checked)
{
    m_Chess.EnablePromptMessage(checked);
}

void MainWindow::on_actionUpdate_U_triggered()
{
    CFrmUpdater* m_pfrmUpdater = new CFrmUpdater();
    m_pfrmUpdater->SetTitle(QImage(":/image/Chess"));
    RC_SHOW_WINDOW(m_pfrmUpdater);
}
