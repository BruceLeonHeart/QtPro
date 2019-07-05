#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QTimer>
#include<QPen>

#include <iostream>
#include <fstream>
using std::ofstream;
#define M_PI 3.14159265358979323846
QTimer *Display_timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     mOpenDriveParser.mOpenDriveStruct = &mOpenDriveStruct;

     string fileName = "/home/pz1_ad_04/qtcreater/pathPlan3/demomap.xml";
     //string fileName = "/home/pz1_ad_04/qtcreater/pathPlan3/RealMap2.xml";
     mOpenDriveParser.ReadFile(fileName);
     vector<RoadNet>* tmp = &mOpenDriveStruct.mRoadNetVector;
     ui->mapView->axisRect()->setupFullAxesBox(true);
     ui->mapView->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     plotMap(ui->mapView,tmp);


     mAStarRoute.mOpenDriveStruct = &mOpenDriveStruct;
     Point start = mAStarRoute.pointBelong(tmp,1000,250);
     Point end = mAStarRoute.pointBelong(tmp,1000,400);
     mAStarRoute.AStarMain(&start,&end,tmp);//执行算法后路径内容进行了填充
     vector<double> x_set;
     vector<double> y_set;
     mAStarRoute.getDataSet(&mAStarRoute.mPath,&start,&end,tmp,&x_set,&y_set);
     char path[64] = "/home/pz1_ad_04/桌面/2.txt";
     ofstream fout(path);
     assert(x_set.size() == y_set.size());
     for (int i = 0; i <x_set.size(); i++)
     {
      fout <<x_set.at(i)<<","<<y_set.at(i)<< endl; // 使用与cout同样的方式进行写入
     }





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
        double RoadGeoEnd = mGeos->at(mGeoslength-1).s + mGeos->at(mGeoslength-1).length;
        //打印参考线

        for(int j =0;j<mGeoslength;j++){
            plotGeo(mapView,&mGeos->at(j),mRoadNetVector,i);
        }

        //打印车道线
        vector<offsetObj>* mOffsets;
        mOffsets = &mRoadNetVector->at(i).Offsets;

        //统计需要显示的车道，并剔除重复元素，这里使用set
        set<int> laneId;


        int mOffsetsLength = mOffsets->size();
        for (int m=0;m<mOffsetsLength;m++) {
            string s1 = mOffsets->at(m).type;
            string s2 = "driving";
            if (s1.compare(s2) == 0)
                laneId.insert(mOffsets->at(m).id);
        }

        for (int n=0;n<mGeoslength;n++) {
            for(set<int>::iterator it = laneId.begin(); it != laneId.end(); it++){
                plotLane(mapView,mRoadNetVector,i,n,*it);
            }

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

//打印车道线
 void MainWindow::plotLane(QCustomPlot* mapView,vector<RoadNet>* mRoadNetVector,int RoadIdx,int GeoId,int id)
 {
     double delta_s =0.5;
     int N = floor(mRoadNetVector->at(RoadIdx).Geos.at(GeoId).length/delta_s);
     vector<double> x_set;
     vector<double> y_set;

     double sValueset[N];
     double data[3]={0} ;

     for (int var = 0; var < N; ++var) {
         sValueset[var] = mRoadNetVector->at(RoadIdx).Geos.at(GeoId).s + delta_s *var;
         mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
         double x = data[0];
         double y = data[1];
         double hdg = data[2];
         double offset = mOpenDriveStruct.GetSOffset(sValueset[var],id,mRoadNetVector,RoadIdx);
         x = x + offset*cos(hdg + sign(id)*M_PI/2);
         y = y + offset*sin(hdg + sign(id)*M_PI/2);
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
