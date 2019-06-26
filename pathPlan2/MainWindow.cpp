#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //之前的控件名对应着
    ImgQCustomPlot connect(ui.ImgQCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui.ImgQCustomPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui.ImgQCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui.ImgQCustomPlot->yAxis2, SLOT(setRange(QCPRange)));
    ui.ImgQCustomPlot->xAxis2->setVisible(true);
    ui.ImgQCustomPlot->xAxis2->setTickLabels(false);
    ui.ImgQCustomPlot->yAxis2->setVisible(true);
    ui.ImgQCustomPlot->yAxis2->setTickLabels(false);
    ui.ImgQCustomPlot->xAxis->setLabel(GBK::ToUnicode("参考方法值"));
    ui.ImgQCustomPlot->yAxis->setLabel(GBK::ToUnicode("对比方法值"));
    ui.ImgQCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui.ImgQCustomPlot->addGraph();
    //初始化
    //针对拟合直线进行初始化
    QPen pen(QColor("red"));
    ui.ImgQCustomPlot->graph()->setPen(pen);
    //设置点的颜色
    ui.ImgQCustomPlot->graph()->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui.ImgQCustomPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
    //1：点的尺寸
    //针对上边界线
    ui.ImgQCustomPlot->addGraph();
    QPen penUpper(QColor("black"));
    ui.ImgQCustomPlot->graph(1)->setPen(penUpper);
    //设置点的颜色
    ui.ImgQCustomPlot->graph(1)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui.ImgQCustomPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
    //1：点的尺寸
    //针对下边界线
    ui.ImgQCustomPlot->addGraph();
    QPen penLower(QColor("black"));
    ui.ImgQCustomPlot->graph(2)->setPen(penLower);
    //设置点的颜色
    ui.ImgQCustomPlot->graph(2)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui.ImgQCustomPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
    //1：点的尺寸
    //针对20组数据点集
    ui.ImgQCustomPlot->addGraph();
    QPen penPnts(QColor("blue"));
    ui.ImgQCustomPlot->graph(3)->setPen(penPnts);
    //设置点的颜色
    ui.ImgQCustomPlot->graph(3)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui.ImgQCustomPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    //1：点的尺寸
    ui.ImgQCustomPlot->yAxis->ticker()->setTickStepStrategy(ui.ImgQCustomPlot->xAxis->ticker()->tickStepStrategy());
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
