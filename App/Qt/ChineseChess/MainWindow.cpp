#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include "DlgAbout.h"
#include "FrmUpdater.h"
#include "FrmStyle.h"

#include <QCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuTools->addMenu(RabbitCommon::CTools::GetLogMenu(this));
    m_pChess = new CFrmChineseChess(this);
    //m_pChess->SetBoardLayout(CChineseChess::TopRedAndBottomBlack);
    this->setCentralWidget(m_pChess);
    ui->actionPrompt_sound_S->setChecked(m_pChess->getEnablePromptSound());
    ui->actionPrompt_message_M->setChecked(m_pChess->getEnablePromptMessage());

    CFrmUpdater updater;
    ui->actionUpdate_U->setIcon(updater.windowIcon());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_O_triggered()
{
    if(!m_pChess) return;
    QString szFile = RabbitCommon::CDir::GetOpenFileName(this,
                                                         tr("Open chess game"));
    m_pChess->LoadChessGame(szFile.toStdString().c_str());
    m_pChess->update();
}

void MainWindow::on_actionSave_S_triggered()
{
    if(!m_pChess) return;
    QString szFile = RabbitCommon::CDir::GetSaveFileName(this,
                                                         tr("Open chess game"),
                                                         QString(),
        tr("Chinese chess control file(*.ccc);;Portable game notation file(*.pgn);;All files(*.*)"));
    m_pChess->SaveChessGame(szFile.toStdString().c_str());
}

void MainWindow::on_actionPreviou_P_triggered()
{
    if(m_pChess)
        m_pChess->PreviouStep();
}

void MainWindow::on_actionNext_N_triggered()
{
    if(m_pChess)
        m_pChess->NextStep();
}

void MainWindow::on_actionExit_E_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionAbout_A_triggered()
{
    QCursor cursor = this->cursor();
    setCursor(Qt::WaitCursor);
    CDlgAbout about(this);
    about.m_AppIcon = QImage(":/image/Chess");
    about.m_szAppName = tr("Chinese chess");
    about.m_szHomePage = "https://github.com/KangLin/ChineseChessControl";
    about.m_szCopyrightStartTime = "1994";
    about.m_szVersion = ChineseChessApp_VERSION;
    about.m_szVersionRevision = ChineseChessApp_REVISION;
    if(about.isHidden())
#if defined (Q_OS_ANDROID)
        about.showMaximized();
#endif
    about.exec();
    setCursor(cursor);
}

void MainWindow::on_actionPrompt_sound_S_triggered(bool checked)
{
    if(m_pChess)
        m_pChess->EnablePromptSound(checked);
}

void MainWindow::on_actionPrompt_message_M_triggered(bool checked)
{
    if(m_pChess)
        m_pChess->EnablePromptMessage(checked);
}

void MainWindow::on_actionUpdate_U_triggered()
{
    CFrmUpdater* m_pfrmUpdater = new CFrmUpdater();
    m_pfrmUpdater->SetTitle(QImage(":/image/Chess"));
    #if defined (Q_OS_ANDROID)
        m_pfrmUpdater->showMaximized();
    #else
        m_pfrmUpdater->show();
    #endif
}

void MainWindow::on_actionStyle_T_triggered()
{
    CFrmStyle* s = new CFrmStyle();
    s->show();
}
