#include "OpenDriveStruct.h"



OpenDriveStruct::OpenDriveStruct()
{

}

unsigned int OpenDriveStruct::AddRoadNet( int id, double length, int junction)
{
    unsigned int index = mRoadNetVector.size();
    RoadNet mRoadNet;
    mRoadNet.id = id;
    mRoadNet.length = length;
    mRoadNet.junction = junction;
    mRoadNetVector.push_back(mRoadNet);
    cout<<"push OK!"<<endl;
    return index;
};

RoadNet* OpenDriveStruct::GetLastRoadNet()
{
    if (mRoadNetVector.size()>0)
        return &(mRoadNetVector.at(mRoadNetVector.size()-1));
    else
        return NULL;
};
