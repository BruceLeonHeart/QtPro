#ifndef OPENDRIVEPARSER_H
#define OPENDRIVEPARSER_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../TinyXML/tinyxml.h"
#include "OpenDriveStruct.h"
using std::vector;
using std::string;
using std::cout;
using std::endl;



class OpenDriveParser
{
private:
    OpenDriveStruct* mOpenDriveStruct;
public:
    OpenDriveParser();
    ~OpenDriveParser();
public:
    bool ReadFile(string fileName);


    /**
     * The following methods are used to read the data from the XML file and fill in the the OpenDrive structure
     * Methods follow the hierarchical structure and are called automatically when ReadFile is executed
     */
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
        bool ReadLane (RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node, short int laneType);

        bool ReadLaneWidth(RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node);
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

//        bool ReadJunction (TiXmlElement *node);
//        bool ReadJunctionConnection (Junction* junction, TiXmlElement *node);
//        bool ReadJunctionConnectionLaneLink (JunctionConnection* junctionConnection, TiXmlElement *node);
//        //--------------

//        bool ReadJunctionPriority (Junction* junction, TiXmlElement *node);
//        bool ReadJunctionController (Junction* junction, TiXmlElement *node);
        //--------------

};

#endif // OPENDRIVEPARSER_H
