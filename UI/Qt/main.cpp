
#include <QApplication>
#include "FrmChineseChess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CFrmChineseChess w;
    w.show();
    return a.exec();
}
