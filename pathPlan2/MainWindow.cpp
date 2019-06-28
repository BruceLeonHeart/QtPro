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
     mOpenDriveParser.mOpenDriveStruct = &mOpenDriveStruct;
     string fileName = "/home/pz1_ad_04/qtcreater/pathPlan2/demomap.xml";
     mOpenDriveParser.ReadFile(fileName);
     vector<RoadNet>* tmp = &mOpenDriveStruct.mRoadNetVector;
     ui->mapView->axisRect()->setupFullAxesBox(true);
     ui->mapView->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     plotMap(ui->mapView,tmp);




    //100ms刷新页面
//    Display_timer = new QTimer(this);
//    connect(Display_timer,SIGNAL(timeout()),this,SLOT(Display_timerUpDate()));
//    Display_timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotMap(QCustomPlot* mapView,vector<RoadNet>* mRoadNetVector){
    int RoadNetNum = mRoadNetVector->size();
    int i;
    for(i=0;i<RoadNetNum;i++){
        vector<GeoObj>* mGeos;
        mGeos = &mRoadNetVector->at(i).Geos;
        int mGeoslength = mGeos->size();
        //打印参考线

        for(int j =0;j<mGeoslength;j++){
            plotGeo(mapView,&mGeos->at(j),mRoadNetVector,i);
        }


    }


}

//打印参考线
void  MainWindow::plotGeo(QCustomPlot* mapView,GeoObj* mObj,vector<RoadNet>* mRoadNetVector,int RoadIdx){
    double delta_s = 0.5;
    int N = floor(mObj->length/delta_s);
    vector<double> x_set;
    vector<double> y_set;

    double sValueset[N];
    double data[3]={0} ;
    for (int var = 0; var < N; ++var) {
        sValueset[var] = mObj->s + delta_s *var;
        mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
        double x = data[0];
        double y = data[1];
        double hdg = data[2];
        x_set.push_back(x);
        y_set.push_back(y);
    }
     QVector<double> X;
     QVector<double> Y;
    for (int i =0 ;i<N;i++) {
        X.append(x_set.at(i));
        Y.append(y_set.at(i));
    }
    plotPointInMap(mapView,X,Y);


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
