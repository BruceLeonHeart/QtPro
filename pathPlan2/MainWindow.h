#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include<QVector>
#include <OpenDrive/OpenDriveParser.h>
#include <OpenDrive/OpenDriveStruct.h>
extern "C"{
#include"OpenDrive/mathTools.h"
}
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
     void plotPointInMap(QCustomPlot* mapView,const QVector<double> x,const QVector<double> y);
     //打印地图
     void plotMap(QCustomPlot* mapView,vector<RoadNet>* mRoadNetVector);
     //打印参考线
     void plotGeo(QCustomPlot* mapView,GeoObj* mObj,vector<RoadNet>* mRoadNetVector,int RoadIdx);
     //打印车道线
     void plotLane();
private:
    Ui::MainWindow *ui;
    OpenDriveStruct mOpenDriveStruct;
    OpenDriveParser mOpenDriveParser;
    QVector<double> x;
    QVector<double> y;
};

#endif // MAINWINDOW_H
