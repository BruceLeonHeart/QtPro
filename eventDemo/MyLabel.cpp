#include "MyLabel.h"
//#include<QEvent>
#include<QDebug>
MyLabel::MyLabel()
{

}

void MyLabel::mouseMoveEvent(QMouseEvent *event)

{

this->setText(QString("<center><h1>Move: (%1, %2)</h1></center>").arg(QString::number(event->x()),

            QString::number(event->y())));

}



void MyLabel::mousePressEvent(QMouseEvent *event)

{

    this->setText(QString("<center><h1>Press:(%1, %2)</h1></center>").arg(QString::number(event->x()),

                QString::number(event->y())));

}



void MyLabel::mouseReleaseEvent(QMouseEvent *event)

{

    QString msg;

    msg.sprintf("<center><h1>Release: (%d, %d)</h1></center>",

                event->x(), event->y());

    this->setText(msg);

}

bool MyLabel::event(QEvent *e)

{
    switch(e->type())
    {
        case QEvent::MouseMove:
            qDebug() << "You Move Mouse.";
            break;
        case QEvent::MouseButtonPress:
            qDebug() << "You Press Mouse.";
            break;
        case QEvent::MouseButtonRelease:
            qDebug() << "You Release Mouse.";
            break;
        default:
            break;
    }

    return QWidget::event(e);

}
