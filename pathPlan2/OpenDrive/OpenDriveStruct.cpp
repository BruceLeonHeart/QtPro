#include "OpenDriveStruct.h"



OpenDriveStruct::OpenDriveStruct()
{

}

unsigned int OpenDriveStruct::AddRoadNet( string id, double length, string junction)
{
    unsigned int index = mRoadNetVector.size();
    RoadNet mRoadNet;
    mRoadNet.id = int(id);
    mRoadNet.length = length;
    mRoadNet.junction = int(junction);
    mRoadNetVector.push_back(mRoadNet);
    return index;
};

RoadNet* OpenDriveStruct::GetLastRoadNet()
{
    if (mRoadNetVector.size()>0)
        return &(mRoadNetVector.at(mRoadNetVector.size()-1));
    else
        return NULL;
};
