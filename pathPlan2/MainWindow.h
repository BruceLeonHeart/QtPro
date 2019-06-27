#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include<QVector>
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
private:
    Ui::MainWindow *ui;
    QVector<double> x;
    QVector<double> y;
};

#endif // MAINWINDOW_H
