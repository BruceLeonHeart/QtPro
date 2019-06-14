#include <QCoreApplication>
#include<QTextStream>
#include"/home/pz1_ad_04/qtcreater/demoSoPro/DemoSoPro.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin,QIODevice::ReadOnly);
    QTextStream cout(stdout,QIODevice::WriteOnly);
    QTextStream cerr(stderr,QIODevice::WriteOnly);
    QString qstrText("QString object");

    DemoSoPro obj;
    int n;
//    typedef int(* SpecialgetSquare)(int);
//    SpecialgetSquare specialgetSquare = SpecialgetSquare
    n = getSquare(10);
    cout<<qstrText<<endl;
    cout<<obj.getHelloWorld()<<endl;
    cerr<<n<<endl;
    char ch;
    cin>>ch;

    return a.exec();
}

