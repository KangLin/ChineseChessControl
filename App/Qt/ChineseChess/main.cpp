#include "MainWindow.h"
#include "FrmChineseChess.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    int nRet = 0;
    QApplication a(argc, argv);
    
    QString szLoacleName = QLocale::system().name();
    RabbitCommon::CTools::Instance()->Init(szLoacleName);
    CFrmChineseChess::InitResource(szLoacleName);

#if _DEBUG
    Q_INIT_RESOURCE(translations_ChineseChessApp);
#endif
    QTranslator translator;
    translator.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
                      + "/ChineseChessApp_" + szLoacleName + ".qm");
    qApp->installTranslator(&translator);

    MainWindow w;
    w.show();
    
    nRet = a.exec();
    
    qApp->removeTranslator(&translator);
    CFrmChineseChess::CleanResource();
    RabbitCommon::CTools::Instance()->Clean();
    
    return nRet;
}
