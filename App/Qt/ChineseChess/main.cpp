#include "MainWindow.h"
#include "FrmChineseChess.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"

#include <QApplication>
#include <QDebug>
#include <QTranslator>

int main(int argc, char *argv[])
{
    int nRet = 0;
    QApplication a(argc, argv);
    
    QString szLoacleName = QLocale::system().name();
    RabbitCommon::CTools::Instance()->Init(szLoacleName);
    CFrmChineseChess::InitResource(szLoacleName);
#ifdef _DEBUG
    Q_INIT_RESOURCE(translations_ChineseChessApp);
#endif
    QString qmFile = RabbitCommon::CDir::Instance()->GetDirTranslations()
            + QDir::separator() + "ChineseChessApp_" + szLoacleName + ".qm";
    
    QTranslator translator;
    translator.load(qmFile);
    qApp->installTranslator(&translator);

    MainWindow w;
    w.show();
    
    nRet = a.exec();
    
    qApp->removeTranslator(&translator);
    CFrmChineseChess::CleanResource();
    RabbitCommon::CTools::Instance()->Clean();
    
    return nRet;
}
