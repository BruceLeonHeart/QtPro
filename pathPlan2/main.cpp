#include "MainWindow.h"
#include <QApplication>
#include <OpenDrive/OpenDriveParser.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    OpenDriveStruct mOpenDriveStruct;
    OpenDriveParser mOpenDriveParser;
    mOpenDriveParser.mOpenDriveStruct = &mOpenDriveStruct;
    string fileName = "/home/pz1_ad_04/qtcreater/pathPlan2/demomap.xml";
    mOpenDriveParser.ReadFile(fileName);
    w.show();
    cout<<"HAPPY END"<<endl;
    return a.exec();
}
