#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPoint>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:



private:
    Ui::MainWindow *ui;
    QPoint m_begin;

//signals:
//    void sng_txtEdit_txtEdit();


private slots:
    void on_connect_clicked();
    void on_disconnect_clicked();
};

#endif // MAINWINDOW_H
