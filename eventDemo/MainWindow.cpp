#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MyLabel *mQLabel = new MyLabel;
    mQLabel->setMouseTracking(true);

    mQLabel->setWindowTitle("MouseEvent Demo");

    mQLabel->resize(300, 200);

    mQLabel->show();
    //ui->label =  mQLabel;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


