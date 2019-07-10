#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 15));
    ui->plot->graph(0)->rescaleAxes();
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

MainWindow::~MainWindow()
{
    delete ui;
}
