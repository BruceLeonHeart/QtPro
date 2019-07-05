#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QObject>
//#include <QPen>
#include "../qcustomplot.h"
//界面UI类
class CustomPlot
{
public:
     CustomPlot(QCustomPlot qCustomPlot);
    virtual ~CustomPlot();
private:
    QCustomPlot* plot;
public:
    //绘制图层

};

#endif // CUSTOMPLOT_H
