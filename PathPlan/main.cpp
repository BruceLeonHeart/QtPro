#include "MainWindow.h"
#include <QApplication>
#include <iostream>
#include<Path_Plan/OpenDrive/OpenDriveXmlParser.h>
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Creates the OpenDrive structure


    OpenDrive mOpenDrive;

    OpenDriveXmlParser* mOpenDriveXmlParser = new OpenDriveXmlParser(&mOpenDrive);
    mOpenDriveXmlParser->ReadFile("/home/pz1_ad_04/qtcreater/PathPlan/demomap.xml");
    int roadNum = mOpenDrive.GetRoadCount();
    cout<<"roadNum is :"<<roadNum<<endl;
    MainWindow w;
    w.show();

    return a.exec();
}
