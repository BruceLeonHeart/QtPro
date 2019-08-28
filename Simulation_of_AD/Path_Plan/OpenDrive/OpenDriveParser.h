#ifndef OPENDRIVEPARSER_H
#define OPENDRIVEPARSER_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "../TinyXML/tinyxml.h"
#include "OpenDriveStruct.h"

#include <iostream>
#include <fstream>
using std::ofstream;

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::set;
//单点
struct PointData{
    double x;
    double y;
};






class OpenDriveParser
{
public:
    OpenDriveStruct* mOpenDriveStruct;
    vector<vector<PointData> > lines; //地图线序列（参考线+Lane）
    vector<vector<PointData> > geoLines; //参考线序列
    vector<vector<PointData>>  laneLines; //Lane序列

public:
    OpenDriveParser();
    ~OpenDriveParser();
public:
    bool ReadFile(string fileName);

    //追加路网信息
    void appendMessages();
    bool ReadHeader (TiXmlElement *node);
    bool ReadRoad (TiXmlElement *node);
    bool ReadRoadLinks (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadRoadLink (RoadNet* mRoadNet, TiXmlElement *node, short int type);
    bool ReadRoadType (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadPlanView(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadGeometryBlock (RoadNet* mRoadNet, TiXmlElement *&node, short int blockType);
    bool ReadElevationProfile (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLateralProfile (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLanes (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneSections (RoadNet* mRoadNet, TiXmlElement *node,int idx);
    bool ReadLane (RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node,double s_start, short int laneType);
    bool ReadLaneWidth(RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node,double s_start);
    bool ReadLaneRoadMark(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneMaterial(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneVisibility(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneSpeed(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneAccess(RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadLaneHeight(RoadNet* mRoadNet, TiXmlElement *node);
//        //--------------

    bool ReadObjects (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadSignals (RoadNet* mRoadNet, TiXmlElement *node);
    bool ReadSurface (RoadNet* mRoadNet, TiXmlElement *node);
//        //--------------
    bool ReadController (TiXmlElement *node);
//        //--------------

    bool ReadJunction (TiXmlElement *node);
    bool ReadJunctionConnection (TiXmlElement *node);
    bool ReadJunctionConnectionLaneLink (RoadNet* mRoadNet,TiXmlElement *node,int connectingRoad);
//        //--------------

    bool ReadJunctionPriority (TiXmlElement *node);
    bool ReadJunctionController (TiXmlElement *node);
        //--------------
    //获取地图点集
    void getMapDataSet();
    // 获取参考线点集序列并生成文件--hgz需求 added 2019-7-22
    void getGeoDataSet();
    //获取Lane序列点集
    void getLaneDataSet();

};

#endif // OPENDRIVEPARSER_H
