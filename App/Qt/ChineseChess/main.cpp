// Author: Kang Lin <kl222@126.com>

#include <QApplication>
#include <QLoggingCategory>
#include <QTranslator>

#include "FrmChineseChess.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include "FrmUpdater/FrmUpdater.h"

#include "MainWindow.h"

static Q_LOGGING_CATEGORY(log, "App.Main")
int main(int argc, char *argv[])
{
    int nRet = 0;
#ifdef ChineseChessApp_VERSION
    QApplication::setApplicationVersion(ChineseChessApp_VERSION);
#endif
    QApplication::setApplicationName("ChineseChessControl");
    QApplication app(argc, argv);

    RabbitCommon::CTools::Instance()->Init();
    CFrmChineseChess::InitResource(RabbitCommon::CTools::Instance()->GetLanguage());

    QSharedPointer<QTranslator> translator =
        RabbitCommon::CTools::Instance()->InstallTranslator("ChineseChessApp");

    app.setApplicationDisplayName(QObject::tr("Chinese chess"));

#ifdef HAVE_UPDATE
    // Check update version
    QScopedPointer<CFrmUpdater> pUpdater(new CFrmUpdater());
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    if(qEnvironmentVariable("SNAP").isEmpty()
        && qEnvironmentVariable("FLATPAK_ID").isEmpty())
#else
    if(qgetenv("SNAP").isEmpty()
        && qgetenv("FLATPAK_ID").isEmpty())
#endif
    {
        if(pUpdater) {
            pUpdater->setAttribute(Qt::WA_DeleteOnClose, false);
            QIcon icon = QIcon::fromTheme(":/image/Chess");
            if(!icon.isNull()) {
                auto sizeList = icon.availableSizes();
                if(!sizeList.isEmpty()) {
                    QPixmap p = icon.pixmap(*sizeList.begin());
                    pUpdater->SetTitle(p.toImage());
                }
            }
            if(app.arguments().length() > 1) {
                try {
                    pUpdater->GenerateUpdateJson();
                    pUpdater->GenerateUpdateXml();
                } catch(...) {
                    qCritical(log) << "Generate update fail";
                }
                qInfo(log) << app.applicationName() + " " + app.applicationVersion()
                                  + " " + QObject::tr("Generate update json file End");
                return 0;
            }
        } else {
            qCritical(log) << "new CFrmUpdater() fail";
        }
    }
#endif // #ifdef HAVE_UPDATE

    MainWindow w;
    RC_SHOW_WINDOW(&w);

    nRet = app.exec();

    if(translator)
        RabbitCommon::CTools::Instance()->RemoveTranslator(translator);
    CFrmChineseChess::CleanResource();
    RabbitCommon::CTools::Instance()->Clean();

    return nRet;
}
