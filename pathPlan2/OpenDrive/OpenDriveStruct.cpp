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
}

RoadNet* OpenDriveStruct::GetLastRoadNet()
{
    if (mRoadNetVector.size()>0)
        return &(mRoadNetVector.at(mRoadNetVector.size()-1));
    else
        return NULL;
}

double* OpenDriveStruct::GetXYHdgByS(vector<RoadNet>* mRoadNetVector,int RoadIdx,double s)
{
    RoadNet currentRoad = mRoadNetVector->at(RoadIdx);
    vector<GeoObj> currentGeos = currentRoad.Geos;
    int GeosLength = currentGeos.size();
    int idx = GeosLength;
    for (int i = 0;i<GeosLength;i++){
        double s_start = currentGeos.at(i).s;
        double s_end = currentGeos.at(i).s + currentGeos.at(i).length;
        if((s>=s_start)&&(s<s_end))
        {
            idx = i;
            break;
        }
    }
    double mlength = s - currentGeos.at(idx).s;
    double* res = NULL;
    if (currentGeos.at(idx).lineType.compare("line") == 0)
        res = CoorGetFinalLine(&(currentGeos.at(idx)),mlength);
    else if (currentGeos.at(idx).lineType.compare("arc") == 0)
        res = CoorGetFinalArc(&(currentGeos.at(idx)),mlength);
    else if (currentGeos.at(idx).lineType.compare("spiral") == 0)
        res = CoorGetFinalSpiral(&(currentGeos.at(idx)),mlength);

    return res;

}

double* OpenDriveStruct::CoorGetFinalLine(GeoObj* mGeo,double length)
{
    double hdg = mGeo->hdg;
    double dx = length*cos(hdg);
    double dy = length*sin(hdg);
    double x = dx + mGeo->x;
    double y = dy + mGeo->y;
    double res[3] = {x,y,hdg};
    return res;
}

double* OpenDriveStruct::CoorGetFinalArc(GeoObj* mGeo,double length)
{
   double c = 0.0;
   double x = mGeo->x + integral(mGeo->hdg,mGeo->curvature,c,0.0,length,10000,0);
   double y = mGeo->y + integral(mGeo->hdg,mGeo->curvature,c,0.0,length,10000,1);
   double hdg = mGeo->hdg + mGeo->curvature*length;
   double res[3] = {x,y,hdg};
   return res;
}

double* OpenDriveStruct::CoorGetFinalSpiral(GeoObj* mGeo,double length)
{
    double c = (mGeo->curvEnd - mGeo->curvStart)/mGeo->length;
    double x = mGeo->x + integral(mGeo->hdg,mGeo->curvStart,c,0.0,length,10000,0);
    double y = mGeo->y + integral(mGeo->hdg,mGeo->curvStart,c,0.0,length,10000,1);
    double hdg = mGeo->hdg + mGeo->curvature*length;
    double res[3] = {x,y,hdg};
    return res;
}
