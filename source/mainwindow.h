#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QMouseEvent>



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

public:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
