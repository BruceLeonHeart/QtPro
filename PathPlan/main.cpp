#include "MainWindow.h"
#include <QApplication>
#include <OpenDrive/OpenDrive.h>
#include <OpenDrive/OpenDriveXmlParser.h>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Creates the OpenDrive structure
    OpenDrive *mOpenDrive = new OpenDrive;
    OpenDriveXmlParser *mOpenDriveXmlParser = new OpenDriveXmlParser(mOpenDrive);
    mOpenDriveXmlParser->ReadFile("demomap.xml");
    int roadNum = mOpenDrive->GetRoadCount();
    cout<<"roadNum is :"<<roadNum<<endl;
    MainWindow w;
    w.show();

    return a.exec();
}
