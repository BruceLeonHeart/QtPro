#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QMouseEvent>
#include <set>
#include "qcustomplot.h"

#include "UI/CustomPlot.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>//定时器
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "CAN_Driver/ICANCmd.h"//CAN
#include "Pure_Pursuit_Contorl/Pure_Pursuit.h"
#include <QMessageBox>
#include <QtCore>
#include <QSlider>//滑槽
//串口
#include <GPS_Driver/spatial_packets.h>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
//保存txt
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QString>
#include <QPainter>
#include <QOpenGLWidget>
#include "QOpenGLFunctions"
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>
#include <QVector>
using std::set;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Open_CAN_Button_clicked();
    void RectimerUpDate();
    void SendtimerUpDate();
    void Display_timerUpDate();
    void GPS_timerUpDate();
    void Pure_Pursuit_timer_timerUpDate();

    void on_Acclerate_Reset_Button_clicked();

    void on_SteeringAngle_Reset_Button_clicked();

    void on_ADAS_Enable_Button_clicked(bool checked);

    void on_Slow_Break_Button_clicked();

    void on_Gear_Switch_Button_activated(int index);

    void on_Fast_Break_Button_clicked();

    void on_Acclerate_Slider_valueChanged(int value);

    void on_Steer_Slider_valueChanged(int value);

    void on_Reflash_CPS_COM_clicked();

    void on_GPS_Start_clicked(bool checked);

    void on_Pure_Pursuit_Start_Button_clicked(bool checked);

    void on_Read_GPS_Data_clicked();

    void on_pushButton_clicked();

public: //OpenDrive


public:
    Ui::MainWindow *ui;
    CustomPlot mCustomPlot;
private: //定时器
    QTimer *Rec_timer; //CAN定时接受
    QTimer *Send_timer; //CAN定时发送
    QTimer *Display_timer; //打印图层刷新
    QTimer *GPS_timer; //GPS信息定时接受
    QTimer *Pure_Pursuit_timer; //PID算法迭代时间
};

#endif // MAINWINDOW_H
