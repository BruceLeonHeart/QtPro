#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QTimer>
#include<QPen>

QTimer *Display_timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
    for(int i =0;i<3;i++){
        x.push_back(i);
        y.push_back(2*i);
    }
    plotPointInMap(ui->mapView,x,y);


    //100ms刷新页面
    Display_timer = new QTimer(this);
    connect(Display_timer,SIGNAL(timeout()),this,SLOT(Display_timerUpDate()));
    Display_timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotPointInMap(QCustomPlot* mapView,const QVector<double> x,const QVector<double> y)
{
    //设置画笔
    QPen pen;
    pen.setColor(Qt::blue);
    //add Gragh
    QCPGraph* currentGragh = NULL;
    currentGragh = mapView->addGraph();
    currentGragh->setPen(pen);
    currentGragh->rescaleAxes(true);//自动调整轴上值的范围
    currentGragh->setData(x,y);//设置数据

}
