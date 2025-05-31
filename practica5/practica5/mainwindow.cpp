#include "mainwindow.h"
#include "game_widget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setCentralWidget(new game_widget(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
