#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QMouseEvent>

class MyLabel : public QLabel
{
public:
    MyLabel();

protected:

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
    bool event(QEvent *e);
};

#endif // MYLABEL_H
