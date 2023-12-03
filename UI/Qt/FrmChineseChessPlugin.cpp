#include "FrmChineseChess.h"
#include "FrmChineseChessPlugin.h"

#include <QtPlugin>
#include <QIcon>

CFrmChineseChessPlugin::CFrmChineseChessPlugin(QObject *parent)
    : QObject(parent),
    QDesignerCustomWidgetInterface()
{
    m_initialized = false;
}

void CFrmChineseChessPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool CFrmChineseChessPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CFrmChineseChessPlugin::createWidget(QWidget *parent)
{
    return new CFrmChineseChess(parent);
}

QString CFrmChineseChessPlugin::name() const
{
    return tr("Chinese chess");
}

QString CFrmChineseChessPlugin::group() const
{
    return QLatin1String("");
}

QIcon CFrmChineseChessPlugin::icon() const
{
    return QIcon(QLatin1String(":/image/Chess"));
}

QString CFrmChineseChessPlugin::toolTip() const
{
    return tr("Chinese chess");
}

QString CFrmChineseChessPlugin::whatsThis() const
{
    return tr("Chinese chess");
}

bool CFrmChineseChessPlugin::isContainer() const
{
    return false;
}

QString CFrmChineseChessPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CFrmChineseChess\" name=\"frmChineseChess\">\n</widget>\n");
}

QString CFrmChineseChessPlugin::includeFile() const
{
    return QLatin1String("FrmChineseChess.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(FrmChineseChessPlugin, CFrmChineseChessPlugin)
#endif // QT_VERSION < 0x050000
