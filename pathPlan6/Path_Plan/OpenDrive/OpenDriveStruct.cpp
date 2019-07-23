#include "OpenDriveStruct.h"



OpenDriveStruct::OpenDriveStruct()
{

}

unsigned int OpenDriveStruct::AddRoadNet( int id, double length, int junction)
{
    unsigned int index = mRoadNetVector.size();
    RoadNet mRoadNet ={};
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

unsigned long OpenDriveStruct::GetXYHdgByS(unsigned long RoadIdx,double s,double * data)
{

    vector<GeoObj>* currentGeos = &(mRoadNetVector.at(RoadIdx).Geos);


    unsigned long GeosLength = currentGeos->size();
    unsigned long idx = GeosLength-1;
    for (unsigned long i = 0;i<GeosLength;i++){
        double s_start = currentGeos->at(i).s;
        double s_end = currentGeos->at(i).s + currentGeos->at(i).length;
        if((s>=s_start)&&(s<s_end))
        {
            idx = i;
            break;
        }
    }
    double mlength = s - currentGeos->at(idx).s;
    GeoObj* mGeo = &currentGeos->at(idx);
    if (currentGeos->at(idx).lineType.compare("line") == 0)
    {
        double hdg = mGeo->hdg;
        double dx = mlength*cos(hdg);
        double dy = mlength*sin(hdg);
        double x = dx + mGeo->x;
        double y = dy + mGeo->y;
        data[0] = x;
        data[1] = y;
        data[2] = hdg;
    }
    else if (currentGeos->at(idx).lineType.compare("arc") == 0)
         CoorGetFinalArc(mGeo,mlength,data);
    else if (currentGeos->at(idx).lineType.compare("spiral") == 0)
         CoorGetFinalSpiral(mGeo,mlength,data);
    else {
        data[0] = -999;
        data[1] = -999;
        data[2] = -999;
    }
    return idx;

}

void OpenDriveStruct::CoorGetFinalLine(GeoObj* mGeo,double length,double* data)
{
    double hdg = mGeo->hdg;
    double dx = length*cos(hdg);
    double dy = length*sin(hdg);
    double x = dx + mGeo->x;
    double y = dy + mGeo->y;
    data[0] = x;
    data[1] = y;
    data[2] = hdg;
}

void OpenDriveStruct::CoorGetFinalArc(GeoObj* mGeo,double length,double* data)
{
   double c = 0.0;
   double down = 0.0;
   long N = 100000;
   int xFlag =0,yFlag = 1;
   double dx = integral(mGeo->hdg,mGeo->curvature,c,down,length,N,xFlag);
   double dy = integral(mGeo->hdg,mGeo->curvature,c,down,length,N,yFlag);
   double x = mGeo->x + dx;
   double y = mGeo->y + dy;
   double hdg = mGeo->hdg + mGeo->curvature*length;
   data[0] = x;
   data[1] = y;
   data[2] = hdg;
}

void OpenDriveStruct::CoorGetFinalSpiral(GeoObj* mGeo,double length,double* data)
{
    double c = (mGeo->curvEnd - mGeo->curvStart)/mGeo->length;
    double down = 0.0;
    long N = 100000;
    int xFlag =0,yFlag = 1;
    double dx = integral(mGeo->hdg,mGeo->curvStart,c,down,length,N,xFlag);
    double dy = integral(mGeo->hdg,mGeo->curvStart,c,down,length,N,yFlag);
    double x = mGeo->x + dx;
    double y = mGeo->y + dy;
    double hdg = mGeo->hdg + mGeo->curvature*length;
    data[0] = x;
    data[1] = y;
    data[2] = hdg;
}

double  OpenDriveStruct::GetSOffset(double s,int id,unsigned long RoadIdx)
{
    RoadNet currentRoad = mRoadNetVector.at(RoadIdx);
    vector<GeoObj> currentGeos = currentRoad.Geos;
    double GeoFinal = currentGeos.at(currentGeos.size()-1).s + currentGeos.at(currentGeos.size()-1).length;//最后一段几何的S终值
    vector<offsetObj> mOffset = currentRoad.Offsets;

    vector<Idset> mIdSet;
    Idset tempIdset;
    for (unsigned long i = 0;i<mOffset.size();i++) {
        if (mOffset.at(i).id == id)
        {
            tempIdset.idx = mOffset.at(i).idx;
            tempIdset.s = mOffset.at(i).s;
            tempIdset.id = mOffset.at(i).id;
            tempIdset.type = mOffset.at(i).type;
            memcpy(tempIdset.offset,mOffset.at(i).offset,sizeof(mOffset.at(i).offset));
            mIdSet.push_back(tempIdset);
        }
    }
    unsigned long mIdSetlength = mIdSet.size();
    if (mIdSetlength == 1)
        mIdSet.at(0).s_end = GeoFinal;
    else {
        for (unsigned long j =0;j<mIdSetlength;j++) {
            if(j==mIdSetlength-1)
                mIdSet.at(j).s_end = GeoFinal;
            else
                mIdSet.at(j).s_end = mIdSet.at(j+1).s;
        }
    }

    unsigned long crtId = mIdSetlength-1;
    for (unsigned long m =0;m<mIdSetlength;m++) {
        if (s >= mIdSet.at(m).s && s < mIdSet.at(m).s_end)
            {
                crtId = m;
                break;
            }
    }

    double delta_s = s - mIdSet.at(crtId).s;
    return getOffsetByS(delta_s,mIdSet.at(crtId).offset);
}

RoadNet* OpenDriveStruct::FindRoadNetById(int id)
{
    unsigned long size = mRoadNetVector.size();
    unsigned long k = size-1;
    for(unsigned long i=0;i<size;i++)
    {
            if (mRoadNetVector.at(i).id == id)
            {
                k = i;
                break;
            }
     }
    return &mRoadNetVector.at(k);
}

unsigned long OpenDriveStruct::getLaneSectionIdByS(unsigned long RoadIdx, double s)
{


    RoadNet currentRoad = mRoadNetVector.at(RoadIdx);

    vector<GeoObj> currentGeos = currentRoad.Geos;
    double GeoFinal = currentGeos.at(currentGeos.size()-1).s + currentGeos.at(currentGeos.size()-1).length;//最后一段几何的S终值

    vector<offsetObj> mOffset = currentRoad.Offsets;

    unsigned long mOffsetSize = mOffset.size();
    unsigned long idx = 999;
    for (unsigned long i = 0;i<mOffsetSize;i++) {
        if(i<mOffsetSize-1)
        {
            if(s>= mOffset.at(i).s && s< mOffset.at(i+1).s)
            {
                idx = i;
                break;
            }
        }
        else {
            if(s>= mOffset.at(i).s && s<= GeoFinal)
            {
                idx = i;
                break;
            }
        }


    }

    return mOffset.at(idx).idx;



}
