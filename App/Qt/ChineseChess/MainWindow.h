#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FrmChineseChess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_actionOpen_O_triggered();
    
    void on_actionSave_S_triggered();
    
    void on_actionPreviou_P_triggered();
    
    void on_actionNext_N_triggered();
    
    void on_actionExit_E_triggered();
    
private:
    Ui::MainWindow *ui;
    
    CFrmChineseChess *m_pChess;
};
#endif // MAINWINDOW_H
