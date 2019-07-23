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
     //读取路网结构
     mOpenDriveParser.mOpenDriveStruct = &mOpenDriveStruct;
     //string fileName = "/home/pz1_ad_04/qtcreater/pathPlan3/demomap.xml";
     //string fileName = "/home/pz1_ad_04/qtcreater/source/RealMap2.xml";
     //string fileName = "/home/pz1_ad_04/qtcreater/pathPlan5/Realmap_20190701.xml";
     string fileName = "/home/pz1_ad_04/qtcreater/pathPlan6/Realmap20190624.xml";

     mOpenDriveParser.ReadFile(fileName);
     mOpenDriveParser.getMapDataSet();
     mOpenDriveParser.getGeoDataSet();
     vector<RoadNet>* tmp = &mOpenDriveStruct.mRoadNetVector;
     ui->mapView->axisRect()->setupFullAxesBox(true);
     ui->mapView->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     plotMap();
     //plotMap(ui->mapView,tmp);


     mAStarRoute.mOpenDriveStruct = &mOpenDriveStruct;
     //demomap
//     Point start = mAStarRoute.pointBelong(tmp,1000,250);
//     Point end = mAStarRoute.pointBelong(tmp,1000,400);
     //0701
//     Point start = mAStarRoute.pointBelong(tmp,-50,-20);
//     Point end = mAStarRoute.pointBelong(tmp,-50,20);
     //0624
     Point start = mAStarRoute.pointBelong(tmp,-132,3.701);
     Point end = mAStarRoute.pointBelong(tmp,9.95,-71.79);

     mAStarRoute.AStarMain(&start,&end,tmp);//执行算法后路径内容进行了填充，得到道路级别的序列

     mAStarRoute.getDataSet(&mAStarRoute.mPath,&start,&end,tmp);//利用道路级别的序列，得到轨迹点级别的序列
     mAStarRoute.getDataFile(); //得到文件
//     vector<double> x_set = mAStarRoute.path_x;
//     vector<double> y_set = mAStarRoute.path_y;;
//     char path[64] = "/home/pz1_ad_04/桌面/2.txt";
//     ofstream fout(path);
//     assert(x_set.size() == y_set.size());
//     for (unsigned long i = 0; i <x_set.size(); i++)
//     {
//      fout <<x_set.at(i)<<","<<y_set.at(i)<< endl; // 使用与cout同样的方式进行写入
//     }

    //100ms刷新页面
//    Display_timer = new QTimer(this);
//    connect(Display_timer,SIGNAL(timeout()),this,SLOT(Display_timerUpDate()));
//    Display_timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::plotMap(QCustomPlot* mapView,vector<RoadNet>* mRoadNetVector){
//    int RoadNetNum = mRoadNetVector->size();
//    int i;
//    for(i=0;i<RoadNetNum;i++){
//        vector<GeoObj>* mGeos;
//        mGeos = &mRoadNetVector->at(i).Geos;
//        int mGeoslength = mGeos->size();
//        double RoadGeoEnd = mGeos->at(mGeoslength-1).s + mGeos->at(mGeoslength-1).length;
//        //打印参考线
//        for(int j =0;j<mGeoslength;j++){
//            plotGeo(mapView,&mGeos->at(j),mRoadNetVector,i);
//        }
//        //打印车道线
//        vector<offsetObj>* mOffsets;
//        mOffsets = &mRoadNetVector->at(i).Offsets;
//        //统计需要显示的车道，并剔除重复元素，这里使用set
//        set<int> laneId;
//        int mOffsetsLength = mOffsets->size();
//        for (int m=0;m<mOffsetsLength;m++) {
//            string s1 = mOffsets->at(m).type;
//            string s2 = "driving";
//            if (s1.compare(s2) == 0)
//                laneId.insert(mOffsets->at(m).id);
//        }

//        for (int n=0;n<mGeoslength;n++) {
//            for(set<int>::iterator it = laneId.begin(); it != laneId.end(); it++){
//                plotLane(mapView,mRoadNetVector,i,n,*it);
//            }

//        }


//    }


//}

////打印参考线
//void  MainWindow::plotGeo(QCustomPlot* mapView,GeoObj* mObj,vector<RoadNet>* mRoadNetVector,unsigned long RoadIdx){
//    double delta_s = 0.5;
//    int N = floor(mObj->length/delta_s);
//    QVector<double> X;
//    QVector<double> Y;
//    double sValueset[N];
//    double data[3]={0} ;
//    for (int var = 0; var < N; ++var) {
//        sValueset[var] = mObj->s + delta_s *var;
//        mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
//        double x = data[0];
//        double y = data[1];
//        //double hdg = data[2];
//        X.append(x);
//        Y.append(y);
//    }
//    plotPointInMap(mapView,X,Y);


//}

////打印车道线
// void MainWindow::plotLane(QCustomPlot* mapView,vector<RoadNet>* mRoadNetVector,unsigned long RoadIdx,int GeoId,int id)
// {
//     double delta_s =0.5;
//     int N = floor(mRoadNetVector->at(RoadIdx).Geos.at(GeoId).length/delta_s);
//     QVector<double> X;
//     QVector<double> Y;

//     double sValueset[N];
//     double data[3]={0} ;

//     for (int var = 0; var < N; ++var) {
//         sValueset[var] = mRoadNetVector->at(RoadIdx).Geos.at(GeoId).s + delta_s *var;
//         mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
//         double x = data[0];
//         double y = data[1];
//         double hdg = data[2];
//         double offset = mOpenDriveStruct.GetSOffset(sValueset[var],id,mRoadNetVector,RoadIdx);
//         x = x + offset*cos(hdg + sign(id)*M_PI/2);
//         y = y + offset*sin(hdg + sign(id)*M_PI/2);
//         X.append(x);
//         Y.append(y);
//     }
//    plotPointInMap(mapView,X,Y);
// }


//void MainWindow::plotPointInMap(QCustomPlot* mapView,const QVector<double> x,const QVector<double> y)
//{
//    //设置画笔
//    QPen pen;
//    pen.setColor(Qt::blue);
//    //add Gragh
//    QCPGraph* currentGragh = NULL;
//    currentGragh = mapView->addGraph();
//    currentGragh->setPen(pen);
//    currentGragh->rescaleAxes(true);//自动调整轴上值的范围
//    currentGragh->setData(x,y);//设置数据

//}

void MainWindow::plotMap()
{
    vector<vector < PointData> >  mapData = mOpenDriveParser.lines;

    for (unsigned long i=0 ; i < mapData.size(); i++) {
        vector < PointData> line = mapData.at(i);
        vector<double> X ;
        vector<double> Y ;
        for (unsigned long j =0 ;j < line.size() ;j++)
        {
            X.push_back(line.at(j).x);
            Y.push_back(line.at(j).y);
        }
        QPen pen;
        pen.setColor(Qt::blue);
        //add Gragh
        QCPGraph* currentGragh = NULL;
        currentGragh = ui->mapView->addGraph();
        currentGragh->setPen(pen);
        currentGragh->rescaleAxes(true);//自动调整轴上值的范围
        currentGragh->setData(x.fromStdVector(X), y.fromStdVector(Y));//设置数据
        //ui->mapView->graph(0)->setData(x.fromStdVector(X), y.fromStdVector(Y));
    }
}

