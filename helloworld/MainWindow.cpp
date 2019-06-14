#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QMessageBox>
#include<QTextEdit>
#include<QMouseEvent>
#include<QListWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        m_begin = e->pos();
    QListWidget::mousePressEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->button()&Qt::LeftButton)
    {

    }
}


void MainWindow::on_connect_clicked()
{
    connect(ui->inputEdit,SIGNAL(textChanged(const QString &)),ui->showEdit,SLOT(setText(const QString &)));
    connect(ui->inputEdit,SIGNAL(textChanged(const QString &)),ui->showEdit_2,SLOT(setText(const QString &)));
    connect(ui->inputEdit,SIGNAL(textChanged(const QString &)),ui->showEdit_3,SLOT(setText(const QString &)));

}

void MainWindow::on_disconnect_clicked()
{
    disconnect(ui->inputEdit,0,0,0);
}

