#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H
#include<qcustomplot.h>

class CustomPlot: public QCustomPlot
{
public:
    CustomPlot(QCustomPlot* out);
    void initPlot();
    void mousePressEvent(QMouseEvent *event);
private:
    QCustomPlot* plot;


};

#endif // CUSTOMPLOT_H
