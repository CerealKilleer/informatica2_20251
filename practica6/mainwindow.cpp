#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    m_system_widget = new System_Widget(this);

    setCentralWidget(m_system_widget);

    resize(1000, 1000);
    setWindowTitle("Simulación Planetaria");
}

MainWindow::~MainWindow() {
    delete m_system_widget;
}
