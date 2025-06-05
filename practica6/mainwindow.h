#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "system_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    System_Widget *m_system_widget;
};
#endif // MAINWINDOW_H
