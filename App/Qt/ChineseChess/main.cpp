#include "MainWindow.h"
#include "FrmChineseChess.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include "FrmUpdater/FrmUpdater.h"

#include <QApplication>
#include <QDebug>
#include <QTranslator>

int main(int argc, char *argv[])
{
    int nRet = 0;
    QApplication a(argc, argv);

    a.setApplicationName("ChineseChessControl");

    QString szLoacleName = QLocale::system().name();
    RabbitCommon::CTools::Instance()->Init(szLoacleName);
    CFrmChineseChess::InitResource(szLoacleName);

    QSharedPointer<QTranslator> translator =
        RabbitCommon::CTools::Instance()->InstallTranslator("ChineseChessApp");

    a.setApplicationDisplayName(QObject::tr("Chinese chess"));

    CFrmUpdater *pUpdate = new CFrmUpdater();
    pUpdate->SetTitle(QImage(":/image/Chess"));
    if(a.arguments().length() > 1) {
        pUpdate->GenerateUpdateJson();
        pUpdate->GenerateUpdateXml();
        return 0;
    }

    MainWindow w;
    w.show();

    nRet = a.exec();

    if(translator)
        RabbitCommon::CTools::Instance()->RemoveTranslator(translator);
    CFrmChineseChess::CleanResource();
    RabbitCommon::CTools::Instance()->Clean();

    return nRet;
}
