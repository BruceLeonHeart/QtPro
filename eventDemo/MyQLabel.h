#ifndef MYQLABEL
#define MYQLABEL
#include<QLabel>
class MyQLabel:public QLabel
{

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
}

#endif // MYQLABEL

