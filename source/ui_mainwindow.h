/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QPushButton *Open_CAN_Button;
    QGroupBox *groupBox;
    QPushButton *ADAS_Enable_Button;
    QComboBox *Gear_Switch_Button;
    QPushButton *Acclerate_Reset_Button;
    QPushButton *SteeringAngle_Reset_Button;
    QPushButton *Fast_Break_Button;
    QLabel *label;
    QLabel *label_2;
    QPushButton *Slow_Break_Button;
    QLineEdit *Acclerate_Send_Value;
    QLineEdit *SteeringAngle_Send_Value;
    QSlider *Steer_Slider;
    QSlider *Acclerate_Slider;
    QGroupBox *groupBox_2;
    QListView *Rec_Info_Box;
    QPushButton *Reflash_CPS_COM;
    QComboBox *GPS_COM_Port;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *GPS_BaudRate;
    QPushButton *GPS_Start;
    QGroupBox *groupBox_3;
    QPushButton *GPS_Data_Save_Button;
    QPushButton *Read_GPS_Data;
    QGroupBox *groupBox_4;
    QPushButton *Pure_Pursuit_Start_Button;
    QCustomPlot *plot;
    QPushButton *pushButton;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1351, 659);
        MainWindow->setSizeIncrement(QSize(0, 0));
        MainWindow->setBaseSize(QSize(100, 129));
        MainWindow->setCursor(QCursor(Qt::UpArrowCursor));
        MainWindow->setFocusPolicy(Qt::TabFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action->setIcon(icon);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Open_CAN_Button = new QPushButton(centralWidget);
        Open_CAN_Button->setObjectName(QString::fromUtf8("Open_CAN_Button"));
        Open_CAN_Button->setGeometry(QRect(10, 0, 91, 381));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(110, 0, 371, 181));
        ADAS_Enable_Button = new QPushButton(groupBox);
        ADAS_Enable_Button->setObjectName(QString::fromUtf8("ADAS_Enable_Button"));
        ADAS_Enable_Button->setGeometry(QRect(20, 24, 91, 31));
        ADAS_Enable_Button->setCheckable(true);
        ADAS_Enable_Button->setAutoExclusive(true);
        Gear_Switch_Button = new QComboBox(groupBox);
        Gear_Switch_Button->addItem(QString());
        Gear_Switch_Button->addItem(QString());
        Gear_Switch_Button->addItem(QString());
        Gear_Switch_Button->addItem(QString());
        Gear_Switch_Button->addItem(QString());
        Gear_Switch_Button->setObjectName(QString::fromUtf8("Gear_Switch_Button"));
        Gear_Switch_Button->setGeometry(QRect(20, 60, 91, 31));
        Acclerate_Reset_Button = new QPushButton(groupBox);
        Acclerate_Reset_Button->setObjectName(QString::fromUtf8("Acclerate_Reset_Button"));
        Acclerate_Reset_Button->setGeometry(QRect(320, 100, 41, 31));
        SteeringAngle_Reset_Button = new QPushButton(groupBox);
        SteeringAngle_Reset_Button->setObjectName(QString::fromUtf8("SteeringAngle_Reset_Button"));
        SteeringAngle_Reset_Button->setGeometry(QRect(320, 140, 41, 31));
        Fast_Break_Button = new QPushButton(groupBox);
        Fast_Break_Button->setObjectName(QString::fromUtf8("Fast_Break_Button"));
        Fast_Break_Button->setGeometry(QRect(240, 25, 111, 64));
        Fast_Break_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 81, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 140, 61, 31));
        Slow_Break_Button = new QPushButton(groupBox);
        Slow_Break_Button->setObjectName(QString::fromUtf8("Slow_Break_Button"));
        Slow_Break_Button->setGeometry(QRect(120, 25, 111, 64));
        Slow_Break_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 233, 79);"));
        Acclerate_Send_Value = new QLineEdit(groupBox);
        Acclerate_Send_Value->setObjectName(QString::fromUtf8("Acclerate_Send_Value"));
        Acclerate_Send_Value->setGeometry(QRect(240, 100, 71, 31));
        SteeringAngle_Send_Value = new QLineEdit(groupBox);
        SteeringAngle_Send_Value->setObjectName(QString::fromUtf8("SteeringAngle_Send_Value"));
        SteeringAngle_Send_Value->setGeometry(QRect(240, 140, 71, 31));
        Steer_Slider = new QSlider(groupBox);
        Steer_Slider->setObjectName(QString::fromUtf8("Steer_Slider"));
        Steer_Slider->setGeometry(QRect(90, 140, 141, 31));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Steer_Slider->sizePolicy().hasHeightForWidth());
        Steer_Slider->setSizePolicy(sizePolicy);
        Steer_Slider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"        height: 20px;\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(211, 215, 207), stop: 1.0 rgb(211, 215, 207));\n"
"}QSlider::handle:horizontal {\n"
"        width: 20px;\n"
"        background: rgb(0,0,0);\n"
"        margin: -6px 0px -6px 0px;\n"
"        border-radius: 9px;\n"
"}"));
        Steer_Slider->setMinimum(-550);
        Steer_Slider->setMaximum(550);
        Steer_Slider->setPageStep(1);
        Steer_Slider->setOrientation(Qt::Horizontal);
        Acclerate_Slider = new QSlider(groupBox);
        Acclerate_Slider->setObjectName(QString::fromUtf8("Acclerate_Slider"));
        Acclerate_Slider->setGeometry(QRect(90, 100, 141, 31));
        sizePolicy.setHeightForWidth(Acclerate_Slider->sizePolicy().hasHeightForWidth());
        Acclerate_Slider->setSizePolicy(sizePolicy);
        Acclerate_Slider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"        height: 20px;\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(211, 215, 207), stop: 1.0 rgb(211, 215, 207));\n"
"}QSlider::handle:horizontal {\n"
"        width: 20px;\n"
"        background: rgb(0,0,0);\n"
"        margin: -6px 0px -6px 0px;\n"
"        border-radius: 9px;\n"
"}"));
        Acclerate_Slider->setMinimum(-100);
        Acclerate_Slider->setMaximum(100);
        Acclerate_Slider->setSingleStep(1);
        Acclerate_Slider->setPageStep(1);
        Acclerate_Slider->setOrientation(Qt::Horizontal);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(110, 190, 651, 191));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        font.setKerning(true);
        groupBox_2->setFont(font);
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        Rec_Info_Box = new QListView(groupBox_2);
        Rec_Info_Box->setObjectName(QString::fromUtf8("Rec_Info_Box"));
        Rec_Info_Box->setGeometry(QRect(20, 30, 611, 151));
        Rec_Info_Box->setFocusPolicy(Qt::NoFocus);
        Rec_Info_Box->setSelectionMode(QAbstractItemView::SingleSelection);
        Reflash_CPS_COM = new QPushButton(centralWidget);
        Reflash_CPS_COM->setObjectName(QString::fromUtf8("Reflash_CPS_COM"));
        Reflash_CPS_COM->setGeometry(QRect(660, 30, 91, 25));
        GPS_COM_Port = new QComboBox(centralWidget);
        GPS_COM_Port->addItem(QString());
        GPS_COM_Port->setObjectName(QString::fromUtf8("GPS_COM_Port"));
        GPS_COM_Port->setGeometry(QRect(560, 30, 91, 25));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 30, 61, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(500, 60, 61, 21));
        GPS_BaudRate = new QComboBox(centralWidget);
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->addItem(QString());
        GPS_BaudRate->setObjectName(QString::fromUtf8("GPS_BaudRate"));
        GPS_BaudRate->setGeometry(QRect(560, 60, 91, 25));
        GPS_Start = new QPushButton(centralWidget);
        GPS_Start->setObjectName(QString::fromUtf8("GPS_Start"));
        GPS_Start->setGeometry(QRect(660, 60, 91, 25));
        GPS_Start->setCheckable(true);
        GPS_Start->setChecked(false);
        GPS_Start->setAutoRepeat(true);
        GPS_Start->setAutoExclusive(false);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(490, 0, 271, 121));
        GPS_Data_Save_Button = new QPushButton(groupBox_3);
        GPS_Data_Save_Button->setObjectName(QString::fromUtf8("GPS_Data_Save_Button"));
        GPS_Data_Save_Button->setEnabled(false);
        GPS_Data_Save_Button->setGeometry(QRect(170, 90, 91, 25));
        GPS_Data_Save_Button->setCheckable(true);
        GPS_Data_Save_Button->setChecked(false);
        GPS_Data_Save_Button->setAutoRepeat(true);
        GPS_Data_Save_Button->setAutoExclusive(false);
        Read_GPS_Data = new QPushButton(groupBox_3);
        Read_GPS_Data->setObjectName(QString::fromUtf8("Read_GPS_Data"));
        Read_GPS_Data->setGeometry(QRect(70, 90, 91, 25));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(490, 120, 271, 61));
        Pure_Pursuit_Start_Button = new QPushButton(groupBox_4);
        Pure_Pursuit_Start_Button->setObjectName(QString::fromUtf8("Pure_Pursuit_Start_Button"));
        Pure_Pursuit_Start_Button->setGeometry(QRect(70, 20, 141, 41));
        Pure_Pursuit_Start_Button->setCheckable(true);
        Pure_Pursuit_Start_Button->setAutoRepeat(true);
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(770, 20, 471, 361));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 490, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        groupBox_3->raise();
        groupBox->raise();
        groupBox_2->raise();
        Open_CAN_Button->raise();
        Reflash_CPS_COM->raise();
        GPS_COM_Port->raise();
        label_3->raise();
        label_4->raise();
        GPS_BaudRate->raise();
        GPS_Start->raise();
        groupBox_4->raise();
        plot->raise();
        pushButton->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1351, 28));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(action_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DNTC-AD", nullptr));
        action->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        Open_CAN_Button->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200CAN", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\275\246\346\216\247\345\217\202\346\225\260", nullptr));
        ADAS_Enable_Button->setText(QApplication::translate("MainWindow", "ADAS", nullptr));
        Gear_Switch_Button->setItemText(0, QApplication::translate("MainWindow", "\346\241\243\344\275\215:\346\227\240", nullptr));
        Gear_Switch_Button->setItemText(1, QApplication::translate("MainWindow", "\346\241\243\344\275\215:N", nullptr));
        Gear_Switch_Button->setItemText(2, QApplication::translate("MainWindow", "\346\241\243\344\275\215:D", nullptr));
        Gear_Switch_Button->setItemText(3, QApplication::translate("MainWindow", "\346\241\243\344\275\215:R", nullptr));
        Gear_Switch_Button->setItemText(4, QApplication::translate("MainWindow", "\346\241\243\344\275\215:P", nullptr));

        Gear_Switch_Button->setCurrentText(QApplication::translate("MainWindow", "\346\241\243\344\275\215:\346\227\240", nullptr));
        Acclerate_Reset_Button->setText(QApplication::translate("MainWindow", "\345\275\222\351\233\266", nullptr));
        SteeringAngle_Reset_Button->setText(QApplication::translate("MainWindow", "\345\275\222\351\233\266", nullptr));
        Fast_Break_Button->setText(QApplication::translate("MainWindow", "\346\200\245\345\210\271", nullptr));
        label->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\212\240\351\200\237\345\272\246", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\350\275\254\350\247\222", nullptr));
        Slow_Break_Button->setText(QApplication::translate("MainWindow", "\347\274\223\345\210\271\350\275\246", nullptr));
        Acclerate_Send_Value->setText(QApplication::translate("MainWindow", "0", nullptr));
        SteeringAngle_Send_Value->setText(QApplication::translate("MainWindow", "0", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\350\275\246\350\276\206\344\277\241\346\201\257", nullptr));
        Reflash_CPS_COM->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        GPS_COM_Port->setItemText(0, QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        GPS_BaudRate->setItemText(0, QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251", nullptr));
        GPS_BaudRate->setItemText(1, QApplication::translate("MainWindow", "4800", nullptr));
        GPS_BaudRate->setItemText(2, QApplication::translate("MainWindow", "9600", nullptr));
        GPS_BaudRate->setItemText(3, QApplication::translate("MainWindow", "14400", nullptr));
        GPS_BaudRate->setItemText(4, QApplication::translate("MainWindow", "19200", nullptr));
        GPS_BaudRate->setItemText(5, QApplication::translate("MainWindow", "38400", nullptr));
        GPS_BaudRate->setItemText(6, QApplication::translate("MainWindow", "56000", nullptr));
        GPS_BaudRate->setItemText(7, QApplication::translate("MainWindow", "57600", nullptr));
        GPS_BaudRate->setItemText(8, QApplication::translate("MainWindow", "115200", nullptr));
        GPS_BaudRate->setItemText(9, QApplication::translate("MainWindow", "460800", nullptr));

        GPS_Start->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245GPS", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "GPS\351\205\215\347\275\256", nullptr));
        GPS_Data_Save_Button->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230GPS\346\225\260\346\215\256", nullptr));
        Read_GPS_Data->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226GPS\346\225\260\346\215\256", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\347\256\227\346\263\225", nullptr));
        Pure_Pursuit_Start_Button->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257Pure_Pursite", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
