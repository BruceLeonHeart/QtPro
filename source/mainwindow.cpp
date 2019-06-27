#include "mainwindow.h"
#include "ui_mainwindow.h"
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

using namespace std;

QTimer *Rec_timer;
QTimer *Send_timer;
QTimer *Display_timer;
QTimer *GPS_timer;
QTimer *Pure_Pursuit_timer;
extern Msg_Send SendMsg;
extern Msg_Rec RecMsg;
extern system_state_packet_t system_state_packet;
extern raw_sensors_packet_t raw_sensors_packet;
extern vector<double> target_x;
extern vector<double> target_y;

#define RADIANS_TO_DEGREES (180.0/M_PI) //for GPS


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //100ms刷新页面
    Display_timer = new QTimer(this);
    connect(Display_timer,SIGNAL(timeout()),this,SLOT(Display_timerUpDate()));
    Display_timer->start(100);
    //第三方绘图初始化
    //目标点
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot->graph(0)->rescaleAxes();
    //实时GPS点转笛卡尔坐标
    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    ui->plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot->graph(1)->rescaleAxes();
    //行驶轨迹轨迹
    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::green));
    ui->plot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot->graph(2)->rescaleAxes();

    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Open_CAN_Button_clicked()
{
    if(ui->Open_CAN_Button->text()== QObject::tr("打开CAN"))
    {
      ui->Open_CAN_Button->setText(QObject::tr("关闭CAN"));
      if (CAN_Init())
      {
          Rec_timer = new QTimer(this);
          connect(Rec_timer,SIGNAL(timeout()),this,SLOT(RectimerUpDate()));
          Rec_timer->start(10);

          Send_timer = new QTimer(this);
          connect(Send_timer,SIGNAL(timeout()),this,SLOT(SendtimerUpDate()));
          Send_timer->start(10);
      }
      else
      {
          QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("打开CAN卡失败"), QMessageBox::Ok);
          ui->Open_CAN_Button->setText(QObject::tr("打开CAN"));
      }
    }
    else if (ui->Open_CAN_Button->text()== QObject::tr("关闭CAN"))
    {
        ui->Open_CAN_Button->setText(QObject::tr("打开CAN"));
        if (Rec_timer->isActive())
        Rec_timer->stop();
        if (Send_timer->isActive())
        Send_timer->stop();
        if(CAN_Close()!=1)
        {
           QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("关闭CAN卡失败"), QMessageBox::Ok);
        }
    }
}

void MainWindow::RectimerUpDate()
{
    if(receive_func()==0)
    {
       QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("接收失败"), QMessageBox::Ok);
       if (Rec_timer->isActive())
       Rec_timer->stop();
       if(CAN_Close()!=1)
       {
          QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("关闭CAN卡失败"), QMessageBox::Ok);
       }
    }
}


void MainWindow::SendtimerUpDate()
{
    if(ui->Pure_Pursuit_Start_Button->isChecked() == false)//确认算法没运行
    {
     SendMsg.ADAS.ADAS_AcceleratedSpd=ui->Acclerate_Send_Value->text().toFloat()*0.01;
     SendMsg.PAS2EPS.PAS_TargetSteerAngle=ui->SteeringAngle_Send_Value->text().toFloat();
    }
     if(send_func()==0)
     {
         QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("发送失败"), QMessageBox::Ok);
         if (Send_timer->isActive())
         Send_timer->stop();
         if(CAN_Close()!=1)
         {
            QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("关闭CAN卡失败"), QMessageBox::Ok);
         }
     }
}

void MainWindow::Display_timerUpDate()
{
    QStringList num;
//    num<<QString("目标车速：%1").arg(RecMsg.VCM2ADAS.ADASCOMFAIL);
    num<<QString("实际车速：%1").arg(double(RecMsg.WheelSpeed_F.VehicleSpeed_copy));
//    num<<QString("目标加速度：%1").arg(double(ui->Acclerate_Send_Value->text().toDouble()*0.01));
//    num<<QString("目标转角：%1").arg(double(ui->SteeringAngle_Send_Value->text().toFloat()));
    num<<QString("实际转角：%1").arg(double(RecMsg.EPS_1.EPS_SteerWheelAngle));
//    num<<QString("目标角速度：%1").arg(SendMsg.PAS2EPS.PAS_TargetSteerAngleSpeed);

    QStringListModel *model = new QStringListModel(num);

    ui->Rec_Info_Box->setModel(model);

    // The following plot setup is mostly taken from the plot demos:


    static QVector<double> x_GPS, y_GPS;
    const double longitude_orig = 113.171198359442;
    const double latitude_orig = 23.384265425953;
    const int longitude_step = 101950;
    const int latitude_step = 111210;

    //打印GPS实时轨迹
    x_GPS.prepend((system_state_packet.longitude * RADIANS_TO_DEGREES - longitude_orig) * longitude_step);
    y_GPS.prepend((system_state_packet.latitude * RADIANS_TO_DEGREES - latitude_orig) * latitude_step);
    ui->plot->graph(1)->setData(x_GPS, y_GPS);
    if(x_GPS.size()>100 || y_GPS.size()>100 )
    {
        x_GPS.remove(100,1);
        y_GPS.remove(100,1);
    }
    ui->plot->replot();
}

void MainWindow::on_Acclerate_Reset_Button_clicked()
{
    ui->Acclerate_Send_Value->setText("0");
    ui->Acclerate_Slider->setValue(0);
}

void MainWindow::on_SteeringAngle_Reset_Button_clicked()
{
    ui->SteeringAngle_Send_Value->setText("0");
    ui->Steer_Slider->setValue(0);
}

void MainWindow::on_ADAS_Enable_Button_clicked(bool checked)
{
    if(checked)
    {
       ui->ADAS_Enable_Button->setStyleSheet("background-color: rgb(78, 154, 6);");
       SendMsg.ADAS.ADAS_Mode = checked;
       SendMsg.ADAS.ADAS_TO_VCM_EN = 1;
       SendMsg.PAS2EPS.PAS_SteerControlReq = 1;
       SendMsg.PAS2EPS.PAS_TargetSteerAngleSpeed = 200;
       SendMsg.PAS2EPS.PAS_TargetSteerAngleValid = 1;
    }
    else
    {
       ui->ADAS_Enable_Button->setStyleSheet("background-color: rgb(255, 255, 255);");
//       SendMsg.ADAS.ADAS_Mode = 0;
//       SendMsg.ADAS.ADAS_TO_VCM_EN = 0;
       SendMsg.PAS2EPS.PAS_SteerControlReq = 0;
//       SendMsg.PAS2EPS.PAS_TargetSteerAngleSpeed = 0;
//       SendMsg.PAS2EPS.PAS_TargetSteerAngleValid = 0;
    }
}

void MainWindow::on_Slow_Break_Button_clicked()
{
    SendMsg.ADAS.SS_Stop_Flag = 1;
}

void MainWindow::on_Gear_Switch_Button_activated(int index)
{
    switch(index)
    {
        case 1:
            SendMsg.ADAS.ADAS_TO_VCM_Shift = 0;
            break;
        case 2:
            SendMsg.ADAS.ADAS_TO_VCM_Shift = 1;
            break;
        case 3:
            SendMsg.ADAS.ADAS_TO_VCM_Shift = 2;
        break;
        default:
            SendMsg.ADAS.ADAS_TO_VCM_Shift = 4;
            break;
    }
}
void MainWindow::on_Fast_Break_Button_clicked()
{
    SendMsg.ADAS.AEB_ACT_Flag = 1;
}
void MainWindow::on_Acclerate_Slider_valueChanged(int value)
{
    ui->Acclerate_Send_Value->setText(QString::number(value));
}

void MainWindow::on_Steer_Slider_valueChanged(int value)
{
    ui->SteeringAngle_Send_Value->setText(QString::number(value));
}

void MainWindow::on_Reflash_CPS_COM_clicked()
{
    ui->GPS_COM_Port->clear();
    foreach(const QSerialPortInfo &qspinfo,QSerialPortInfo::availablePorts())
    {
        ui->GPS_COM_Port->addItem(qspinfo.portName());
    }
}

void MainWindow::GPS_timerUpDate()
{
    static unsigned int Recoed_Line;
    QString Record_Data;
    static QFile csvFile;
    QString time;

    //获取GPS数据
    if(GPS_main()!=1)
    {
//        if (GPS_timer->isActive())
//        GPS_timer->stop();
//        ui->GPS_Start->setText(QObject::tr("连接GPS"));
//        QMessageBox::warning(this, QObject::tr("提示"), QObject::tr("无数据"), QMessageBox::Ok);
    }
    //保存GPS数据
    if(ui->GPS_Data_Save_Button->isChecked())
    {
        ui->GPS_Data_Save_Button->setStyleSheet("background-color: rgb(78, 154, 6);");
        ui->GPS_Data_Save_Button->setText(QObject::tr("停止记录"));
        if (Recoed_Line==0)
        {
            time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"); //设置显示格式
            csvFile.setFileName(QCoreApplication::applicationDirPath()+"/"+time+"_GPS_Data.csv");
            Record_Data=tr("时间,经度,纬度,高度,翻滚角,俯仰角,航向角\n");
            Recoed_Line++;
            csvFile.open(QIODevice::ReadWrite);
            csvFile.write(Record_Data.toUtf8());
        }
        else
        {
            time = QDateTime::currentDateTime().toString("yyyy-MM-dd/hh:mm:ss.zzz"); //设置显示格式
            Record_Data=time+","+QString::number(system_state_packet.latitude*RADIANS_TO_DEGREES)+","+QString::number(system_state_packet.longitude * RADIANS_TO_DEGREES)+","+QString::number(system_state_packet.height)+","+QString::number(system_state_packet.orientation[0] * RADIANS_TO_DEGREES)+","+QString::number(system_state_packet.orientation[1] * RADIANS_TO_DEGREES)+","+QString::number(system_state_packet.orientation[2] * RADIANS_TO_DEGREES)+"\n";
            csvFile.write(Record_Data.toLatin1().data());
        }
    }
    else
    {
        ui->GPS_Data_Save_Button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->GPS_Data_Save_Button->setText(QObject::tr("保存GPS数据"));
        csvFile.close();
    }
}

void MainWindow::on_GPS_Start_clicked(bool checked)
{
    QString COM_Port=ui->GPS_COM_Port->currentText();
    COM_Port="/dev/"+COM_Port;
    int BaudRate=ui->GPS_BaudRate->currentText().toInt();
    GPS_timer = new QTimer(this);
    if(checked)
    {
        if(GPS_Open(COM_Port.toLatin1().data(),BaudRate)==1)
        {
            connect(GPS_timer,SIGNAL(timeout()),this,SLOT(GPS_timerUpDate()));
            GPS_timer->start(10);
            ui->GPS_Start->setText(QObject::tr("关闭GPS"));
            ui->GPS_Start->setStyleSheet("background-color: rgb(78, 154, 6);");
            ui->GPS_Data_Save_Button->setEnabled(checked);
        }
        else
        {
           QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("请更新串口或选择波特率"), QMessageBox::Ok);
           ui->GPS_Start->setChecked(false);
        }
    }
    else
    {
        if (GPS_timer->isActive()){GPS_timer->stop();}
        ui->GPS_Start->setText(QObject::tr("连接GPS"));
        ui->GPS_Data_Save_Button->setEnabled(checked);
        ui->GPS_Start->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
}

void MainWindow::on_Read_GPS_Data_clicked()
{
    QUrl fileNames=QFileDialog::getOpenFileName(this,tr("请选择文件"),QDir::currentPath(),"CSV Files(*.csv)");
    QFile csvFile(fileNames.toString());
    QString CSVLine;
    QString temp;
    QVector<double> msgcolumn;
    QVector< QVector<double>> msg;
    QVector<double> targetx;
    QVector<double> targety;

    const double longitude_orig = 113.171198359442;
    const double latitude_orig = 23.384265425953;
    const int longitude_step = 101950;
    const int latitude_step = 111210;

    ui->Read_GPS_Data->setEnabled(false);
    if (csvFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&csvFile);
        while (!stream.atEnd())
        {
            CSVLine=stream.readLine()+',';
            for (int i=0;i<CSVLine.size();i++)
            {
                if(CSVLine[i]!=',')
                {
                    temp=temp+CSVLine[i];
                }
                else
                {
                    msgcolumn.append(temp.toDouble());
                    temp.clear();
                }
            }
            //打印GPS轨迹记录
            targetx.append((msgcolumn[2] - longitude_orig) * longitude_step);
            targety.append((msgcolumn[1] - latitude_orig) * latitude_step);

            msg.push_back(msgcolumn);
            msgcolumn.clear();
        }
        ui->plot->graph(2)->setData(targetx, targety); //打印
        csvFile.close();
        QMessageBox::warning(this, QObject::tr("成功"), QObject::tr("读取完成"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, QObject::tr("错误"), QObject::tr("打开文件失败"), QMessageBox::Ok);
    }
    ui->Read_GPS_Data->setEnabled(true);
}


void MainWindow::on_Pure_Pursuit_Start_Button_clicked(bool checked)
{
    if(checked)
    {
      //计算目标点
      Target_route();
      //打印目标点
      QVector<double> x, y;
      ui->plot->graph(0)->setData(x.fromStdVector(target_x), y.fromStdVector(target_y));
      //开启Pur_pursuit
      ui->Pure_Pursuit_Start_Button->setStyleSheet("background-color: rgb(78, 154, 6);");
      ui->Pure_Pursuit_Start_Button->setText(QObject::tr("停止Pure_Pursite"));
      Pure_Pursuit_timer = new QTimer(this);
      connect(Pure_Pursuit_timer,SIGNAL(timeout()),this,SLOT(Pure_Pursuit_timer_timerUpDate()));
      Pure_Pursuit_timer->start(100);
    }
    else
    {
      ui->Pure_Pursuit_Start_Button->setText(QObject::tr("开启Pure_Pursite"));
      ui->Pure_Pursuit_Start_Button->setStyleSheet("background-color: rgb(255, 255, 255);");
      if (Pure_Pursuit_timer->isActive())
      Pure_Pursuit_timer->stop();
    }
}


void MainWindow::Pure_Pursuit_timer_timerUpDate()
{
   Pure_Pursuit_main();
}
