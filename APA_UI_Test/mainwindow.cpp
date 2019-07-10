#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCustomPlot  = new CustomPlot(ui->plot);
    mCustomPlot->initPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
