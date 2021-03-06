﻿#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QObject>
//#include <QPen>
#include "../qcustomplot.h"
#include "Path_Plan/OpenDrive/OpenDriveStruct.h"
#include "Path_Plan/OpenDrive/OpenDriveParser.h"
#include "Path_Plan/AStarRoute/AStarRoute.h"

#include <set>
using std::set;
//界面UI类
class CustomPlot : public QCustomPlot
{
public:
    CustomPlot();
    virtual ~CustomPlot();
    double point[2];
public:
    QCustomPlot* plot;
public:
    //初始化
    void initPlot();
public://地图相关
    void plotPointInMap(const QVector<double> x,const QVector<double> y);
    //打印地图
    void plotMap();
    //打印参考线
    void plotGeo(GeoObj* mObj,unsigned long RoadIdx);
    //打印车道线
    void plotLane(unsigned long RoadIdx,unsigned long GeoId,unsigned long id);

    void mousePressEvent(QMouseEvent *event);


public://OpenDrive
    AStarRoute mAStarRoute;
    QVector<double> x;
    QVector<double> y;
};

#endif // CUSTOMPLOT_H
