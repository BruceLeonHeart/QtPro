#include "CustomPlot.h"

CustomPlot::CustomPlot(QCustomPlot* out)
{
    plot = out;
}

void CustomPlot::initPlot()
{
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 15));
    plot->graph(0)->rescaleAxes();
    plot->axisRect()->setupFullAxesBox(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void CustomPlot::mousePressEvent(QMouseEvent *event)
{
  emit mousePress(event);
  // save some state to tell in releaseEvent whether it was a click:
  mMouseHasMoved = false;
  mMousePressPos = event->pos();
  if(plot->graph(0))
  {
      //graph(0)->addData(xAxis->pixelToCoord(mMousePressPos.x()),yAxis->pixelToCoord(mMousePressPos.y()));
      qDebug()<<xAxis->pixelToCoord(mMousePressPos.x())<<"\n";
      //replot();
  }
}
