#include "OpenDriveParser.h"

OpenDriveParser::OpenDriveParser()
{
}

OpenDriveParser::~OpenDriveParser()
{
}

void OpenDriveParser::appendMessages()
{
    //获取路网对象
    vector<RoadNet>* mRoadNetVector = &mOpenDriveStruct.mRoadNetVector;
    for (unsigned long i = 0; i< mRoadNetVector->size();i++) {
            RoadNet* crtRoadNet = &mRoadNetVector->at(i);
            crtRoadNet->start_x = crtRoadNet->Geos.at(0).x;
            crtRoadNet->start_y = crtRoadNet->Geos.at(0).y;
            double data[3] ={0.0};
            mOpenDriveStruct.GetXYHdgByS(i,crtRoadNet->length,data);
            crtRoadNet->end_x = data[0];
            crtRoadNet->end_y = data[1];
    }
}


bool OpenDriveParser::ReadFile(string fileName)
{
    //Read and load File
        TiXmlDocument doc( fileName );
        bool loadOkay = doc.LoadFile();
        if (loadOkay)
        {
            TiXmlElement *rootNode=doc.FirstChildElement();
            //read header
            int checker=TIXML_SUCCESS;
            TiXmlElement *node=rootNode->FirstChildElement("header");
            ReadHeader(node);

            //read roads
            node=rootNode->FirstChildElement("road");
            while (node!=0)
            {

                ReadRoad(node);
                node=node->NextSiblingElement("road");

            }

            //read controllers
            node=rootNode->FirstChildElement("controller");
            while (node!=0)
            {
                ReadController(node);
                node=node->NextSiblingElement("controller");
            }

            //read junctions
            node=rootNode->FirstChildElement("junction");
            while (node!=0)
            {
                ReadJunction(node);
                node=node->NextSiblingElement("junction");
            }

            appendMessages();
            return true;
        }

        //failed to read the file
        cout<<"Could not read file: "<<fileName<<endl;
        return false;
};

bool OpenDriveParser::ReadHeader (TiXmlElement *node)
{
    //Read the Header
        unsigned short int revMajor;
        unsigned short int revMinor;
        string name;
        float version;
        string date;
        double north;
        double south;
        double east;
        double west;

        int checker=TIXML_SUCCESS;
        checker+=node->QueryValueAttribute<unsigned short int>("revMajor",&revMajor);
        checker+=node->QueryValueAttribute<unsigned short int>("revMinor",&revMinor);
        checker+=node->QueryStringAttribute("name",&name);
        checker+=node->QueryFloatAttribute("version",&version);
        checker+=node->QueryStringAttribute("date",&date);
        checker+=node->QueryDoubleAttribute("north",&north);
        checker+=node->QueryDoubleAttribute("south",&south);
        checker+=node->QueryDoubleAttribute("east",&east);
        checker+=node->QueryDoubleAttribute("west",&west);

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Header attributes"<<endl;
            return false;
        }

        //cout<<"version is :" <<version <<endl;

        return true;

};

bool OpenDriveParser::ReadRoad (TiXmlElement *node)
{
    //Read road attributes
    string name;
    double length;
    int id;
    int junction;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryStringAttribute("name",&name);
    checker+=node->QueryDoubleAttribute("length",&length);
    checker+=node->QueryIntAttribute("id",&id);
    checker+=node->QueryIntAttribute("junction",&junction);

    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Road attributes"<<endl;
        return false;
    }
    mOpenDriveStruct.AddRoadNet(id,length,junction);
    RoadNet* lastRoadNet = mOpenDriveStruct.GetLastRoadNet();
     cout<<"it's ok5"<<endl;
    TiXmlElement* subNode;
    //Get links
    subNode=node->FirstChildElement("link");
    if (subNode)
    {
        ReadRoadLinks (lastRoadNet,subNode);
    }

    //Proceed to road Type
    subNode=node->FirstChildElement("type");
    while (subNode)
    {
        ReadRoadType(lastRoadNet, subNode);
        subNode=subNode->NextSiblingElement("type");
    }

    //Proceed to planView
    subNode=node->FirstChildElement("planView");
    ReadPlanView(lastRoadNet, subNode);

    //Proceed to LateralProfile
    subNode=node->FirstChildElement("lateralProfile");
    if (subNode)
    {
        ReadLateralProfile(lastRoadNet, subNode);
    }
    //Proceed to Lanes
    subNode=node->FirstChildElement("lanes");
    ReadLanes(lastRoadNet, subNode);


    //Proceed to Objects
    subNode=node->FirstChildElement("objects");
    if (subNode)
    {
        ReadObjects(lastRoadNet, subNode);
    }

    //Proceed to Signals
    subNode=node->FirstChildElement("signals");
    if (subNode)
    {
        ReadSignals(lastRoadNet, subNode);
    }

    //Proceed to Surface
    subNode=node->FirstChildElement("surface");
    if (subNode)
    {
        ReadSurface(lastRoadNet, subNode);
    }

    return true;
};

bool OpenDriveParser::ReadRoadLinks (RoadNet* mRoadNet, TiXmlElement *node)
{
    TiXmlElement* subNode;
    subNode=node->FirstChildElement("predecessor");
    if (subNode)
    {
        ReadRoadLink(mRoadNet, subNode,0);
    }

    subNode=node->FirstChildElement("successor");
    if (subNode)
    {
        ReadRoadLink(mRoadNet, subNode,1);
    }

    subNode=node->FirstChildElement("neighbor");
    if (subNode)
    {
        ReadRoadLink(mRoadNet, subNode,2);
    }

    subNode=node->NextSiblingElement("neighbor");
    if (subNode)
    {
        ReadRoadLink(mRoadNet, subNode,2);
    }
    return true;
};

bool OpenDriveParser::ReadRoadLink (RoadNet* mRoadNet, TiXmlElement *node, short int type)
{
    //all three types (neighbor, successor or predecessor) have the same number and same types of members,
    //but in case this changes in future, load it separately
    if (type == 0)
    {
        string elementType;
        int elementId;
        string contactPoint="NA";

        int checker=TIXML_SUCCESS;
        checker+=node->QueryStringAttribute("elementType",&elementType);
        checker+=node->QueryIntAttribute("elementId",&elementId);
        if (elementType.compare("road")==0)//道路的情形
        {
            checker+=node->QueryStringAttribute("contactPoint",&contactPoint);
            mRoadNet->left_successor_road_id.push_back(elementId);
            if (contactPoint == "start")
                mRoadNet->left_successor_road_direction.push_back(-1);
            else
                mRoadNet->left_successor_road_direction.push_back(1);
        }

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Predecessor attributes"<<endl;
            return false;
        }
        return true;

    }
    else if (type == 1)
    {
        string elementType;
        int elementId;
        string contactPoint="NA";

        int checker=TIXML_SUCCESS;
        checker+=node->QueryStringAttribute("elementType",&elementType);
        checker+=node->QueryIntAttribute("elementId",&elementId);
        if (elementType.compare("road")==0)
        {
            checker+=node->QueryStringAttribute("contactPoint",&contactPoint);
            mRoadNet->right_successor_road_id.push_back(elementId);
            if (contactPoint == "start")
                mRoadNet->right_successor_road_direction.push_back(-1);
            else
                mRoadNet->right_successor_road_direction.push_back(1);
        }

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Successor attributes"<<endl;
            return false;
        }
        return true;
    }

    else if (type == 2)
    {
        string side;
        string elementId;
        string direction;

        int checker=TIXML_SUCCESS;
        checker+=node->QueryStringAttribute("side",&side);
        checker+=node->QueryStringAttribute("elementId",&elementId);
        checker+=node->QueryStringAttribute("direction",&direction);

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Neighbor attributes"<<endl;
            return false;
        }
        return true;
    }

    return false;
};

bool OpenDriveParser::ReadRoadType (RoadNet* mRoadNet, TiXmlElement *node)
{
    double s;
    string type;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("s",&s);
    checker+=node->QueryStringAttribute("type",&type);

    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Road Type attributes"<<endl;
        return false;
    }
    return true;
};

bool OpenDriveParser::ReadPlanView(RoadNet* mRoadNet, TiXmlElement *node)
{
    //Get geometry
    TiXmlElement* subNode;
    TiXmlElement* subNodeType;
    subNode=node->FirstChildElement("geometry");

    while (subNode)
    {
        subNodeType=subNode->FirstChildElement();
        if (subNodeType->ValueStr().compare("line")==0)
        {
            ReadGeometryBlock(mRoadNet, subNode,0);		//load a straight block
        }
        else if (subNodeType->ValueStr().compare("spiral")==0)
        {
            ReadGeometryBlock(mRoadNet, subNode,1);		//load a turn block
        }
        else if (subNodeType->ValueStr().compare("arc")==0)
        {
            ReadGeometryBlock(mRoadNet, subNode,2);		//load a arc block
        }

        subNode=subNode->NextSiblingElement("geometry");

    }
    return true;
};

bool OpenDriveParser::ReadGeometryBlock (RoadNet* mRoadNet, TiXmlElement *&node, short int blockType)
{
    double s, x, y, hdg, length;
    //read the geometry node
    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("s",&s);
    checker+=node->QueryDoubleAttribute("x",&x);
    checker+=node->QueryDoubleAttribute("y",&y);
    checker+=node->QueryDoubleAttribute("hdg",&hdg);
    checker+=node->QueryDoubleAttribute("length",&length);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Geometry attributes"<<endl;
        return false;
    }
//    double s;
//    double x;
//    double y;
//    double hdg;
//    double length;
//    string lineType;
//    double curvature;
//    double curvStart;
//    double curvEnd;
    GeoObj mGeoObj = {};
    mGeoObj.s = s;
    mGeoObj.x = x;
    mGeoObj.y = y;
    mGeoObj.hdg = hdg;
    mGeoObj.length = length;
    TiXmlElement *subNode=node->FirstChildElement();

    //read the type nodes
    switch ( blockType )
    {
    case 0:		//line
        mGeoObj.lineType = "line";
        break;
    case 1:		//spiral
        checker=TIXML_SUCCESS;
        double curvatureStart, curvatureEnd;
        checker+=subNode->QueryDoubleAttribute("curvStart",&curvatureStart);
        checker+=subNode->QueryDoubleAttribute("curvEnd",&curvatureEnd);
        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing spiral attributes"<<endl;
            return false;
        }
        mGeoObj.lineType = "spiral";
        mGeoObj.curvStart = curvatureStart;
        mGeoObj.curvEnd = curvatureEnd;
        break;
    case 2:		//arc
        checker=TIXML_SUCCESS;
        double curvature;
        checker+=subNode->QueryDoubleAttribute("curvature",&curvature);
        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing arc attributes"<<endl;
            return false;
        }
        mGeoObj.lineType = "arc";
        mGeoObj.curvature = curvature;
        break;
    }
    mRoadNet->Geos.push_back(mGeoObj);
    return true;
};

bool OpenDriveParser::ReadElevationProfile (RoadNet* mRoadNet, TiXmlElement *node)
{
    TiXmlElement* subNode;
    subNode=node->FirstChildElement("elevation");
    double s, a, b, c, d;
    while (subNode)
    {
        int checker=TIXML_SUCCESS;
        checker+=subNode->QueryDoubleAttribute("s",&s);
        checker+=subNode->QueryDoubleAttribute("a",&a);
        checker+=subNode->QueryDoubleAttribute("b",&b);
        checker+=subNode->QueryDoubleAttribute("c",&c);
        checker+=subNode->QueryDoubleAttribute("d",&d);

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Elevation attributes"<<endl;
            return false;
        }
        subNode=subNode->NextSiblingElement("elevation");
    }
    return true;
};

bool OpenDriveParser::ReadLateralProfile (RoadNet* mRoadNet, TiXmlElement *node)
{
    TiXmlElement* subNode;
    subNode=node->FirstChildElement("superelevation");
    double s, a, b, c, d;
    while (subNode)
    {
        int checker=TIXML_SUCCESS;
        checker+=subNode->QueryDoubleAttribute("s",&s);
        checker+=subNode->QueryDoubleAttribute("a",&a);
        checker+=subNode->QueryDoubleAttribute("b",&b);
        checker+=subNode->QueryDoubleAttribute("c",&c);
        checker+=subNode->QueryDoubleAttribute("d",&d);

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Superelevation attributes"<<endl;
            return false;
        }

        subNode=subNode->NextSiblingElement("superelevation");
    }

    subNode=node->FirstChildElement("crossfall");
    string side;
    while (subNode)
    {
        int checker=TIXML_SUCCESS;
        checker+=subNode->QueryStringAttribute("side",&side);
        checker+=subNode->QueryDoubleAttribute("s",&s);
        checker+=subNode->QueryDoubleAttribute("a",&a);
        checker+=subNode->QueryDoubleAttribute("b",&b);
        checker+=subNode->QueryDoubleAttribute("c",&c);
        checker+=subNode->QueryDoubleAttribute("d",&d);

        if (checker!=TIXML_SUCCESS)
        {
            cout<<"Error parsing Crossfall attributes"<<endl;
            return false;
        }

        subNode=subNode->NextSiblingElement("crossfall");
    }

    return true;
};

bool OpenDriveParser::ReadLanes (RoadNet* mRoadNet, TiXmlElement *node)
{
    int idx = 0;
    TiXmlElement *subNode = node->FirstChildElement("laneSection");
    while (subNode)
    {
        idx ++;
        ReadLaneSections(mRoadNet, subNode,idx);
        subNode=subNode->NextSiblingElement("laneSection");
    }

    return true;
};

bool OpenDriveParser::ReadLaneSections (RoadNet* mRoadNet, TiXmlElement *node,int idx)
{
    offsetObj mOffsetobj;
    int checker=TIXML_SUCCESS;
    double s;
    checker+=node->QueryDoubleAttribute("s",&s);
    mOffsetobj.idx = idx;
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Section attributes"<<endl;
        return false;
    }

    TiXmlElement *subNode=node->FirstChildElement("left");
    if (subNode)
    {
        subNode=subNode->FirstChildElement("lane");
        while(subNode)
        {
            ReadLane(mRoadNet,&mOffsetobj,subNode,s,1);
            subNode=subNode->NextSiblingElement("lane");
        }

    }
    subNode=node->FirstChildElement("center");
    if (subNode)
    {
        subNode=subNode->FirstChildElement("lane");
        while(subNode)
        {
            ReadLane(mRoadNet,&mOffsetobj,subNode,s,0);
            subNode=subNode->NextSiblingElement("lane");
        }
    }

    subNode=node->FirstChildElement("right");
    if (subNode)
    {
        subNode=subNode->FirstChildElement("lane");
        while(subNode)
        {
            ReadLane(mRoadNet,&mOffsetobj,subNode,s,-1);
            subNode=subNode->NextSiblingElement("lane");
        }
    }
    return true;
};

bool OpenDriveParser::ReadLane (RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node,double s_start, short int laneType)
{
    //Read Lane attributes
    short int side=laneType;//作为保留，暂未使用
    int id;
    string type;
    string level;
    bool boolLevel;
    int predecessor;
    int successor;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryIntAttribute("id",&id);
    checker+=node->QueryStringAttribute("type",&type);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane attributes"<<endl;
        return false;
    }
    //in case "level" is missing, apply default value
    checker=node->QueryStringAttribute("level",&level);
    if (checker!=TIXML_SUCCESS)
    {	level="false"; }

    //convert level to bool

    if (level.compare("false")==0 || level.compare("0")==0)
        boolLevel=false;
    else
        boolLevel=true;

    mOffsetObj->id = id;
    mOffsetObj->type = type;

    //Read Link parameters and add them to the lane if available
    TiXmlElement *subNode=node->FirstChildElement("link");
    TiXmlElement *subSubNode;
    if (subNode)
        subSubNode=subNode->FirstChildElement("predecessor");
            if (subSubNode)
            {
                checker=subSubNode->QueryIntAttribute("id",&predecessor);

            }
    if (subNode)
        subSubNode=subNode->FirstChildElement("successor");
            if (subSubNode)
            {
                checker=subSubNode->QueryIntAttribute("id",&successor);
            }

    //Proceed to the Road width
    subNode=node->FirstChildElement("width");
    while (subNode)
    {
        ReadLaneWidth(mRoadNet,mOffsetObj, subNode,s_start);
        subNode=subNode->NextSiblingElement("width");
    }

    //Proceed to the Road Mark
    subNode=node->FirstChildElement("roadMark");
    while (subNode)
    {
        ReadLaneRoadMark(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("roadMark");
    }

    //Proceed to the Lane Material
    subNode=node->FirstChildElement("material");
    while (subNode)
    {
        ReadLaneMaterial(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("material");
    }

    //Proceed to the Lane Visibility
    subNode=node->FirstChildElement("visibility");
    while (subNode)
    {
        ReadLaneVisibility(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("visibility");
    }

    //Proceed to the Lane speed
    subNode=node->FirstChildElement("speed");
    while (subNode)
    {
        ReadLaneSpeed(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("speed");
    }

    //Proceed to the Lane access
    subNode=node->FirstChildElement("access");
    while (subNode)
    {
        ReadLaneAccess(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("access");
    }

    //Proceed to the Lane height
    subNode=node->FirstChildElement("height");
    while (subNode)
    {
        ReadLaneHeight(mRoadNet, subNode);
        subNode=subNode->NextSiblingElement("height");
    }

    return true;
};

bool OpenDriveParser::ReadLaneWidth(RoadNet* mRoadNet,offsetObj* mOffsetObj, TiXmlElement *node,double s_start)
{
    double sOffset, a, b, c, d;
    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryDoubleAttribute("a",&a);
    checker+=node->QueryDoubleAttribute("b",&b);
    checker+=node->QueryDoubleAttribute("c",&c);
    checker+=node->QueryDoubleAttribute("d",&d);
    double offset[4] = {a,b,c,d};
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }
    {
        mOffsetObj->s = s_start + sOffset;
        mOffsetObj->offset[0] = a;
        mOffsetObj->offset[1] = b;
        mOffsetObj->offset[2] = c;
        mOffsetObj->offset[3] = d;
        mRoadNet->Offsets.push_back(*mOffsetObj);
    }
    return true;
};

bool OpenDriveParser::ReadLaneRoadMark(RoadNet* mRoadNet, TiXmlElement *node)
{

    double sOffset;
    string type;
    string weight;
    string color;
    double width;
    string laneChange;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryStringAttribute("type",&type);
    checker+=node->QueryStringAttribute("weight",&weight);
    checker+=node->QueryStringAttribute("color",&color);

    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }

    checker+=node->QueryDoubleAttribute("width",&width);
    if (checker!=TIXML_SUCCESS)
    {	width=0;	}

    checker=node->QueryStringAttribute("laneChange",&laneChange);
    if (checker!=TIXML_SUCCESS)
    {	laneChange = "both"; }

    return true;
};

bool OpenDriveParser::ReadLaneMaterial(RoadNet* mRoadNet, TiXmlElement *node)
{
    double sOffset;
    string surface;
    double friction;
    double roughness;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryStringAttribute("surface",&surface);
    checker+=node->QueryDoubleAttribute("friction",&friction);
    checker+=node->QueryDoubleAttribute("roughness",&roughness);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }

    return true;
}

bool OpenDriveParser::ReadLaneVisibility(RoadNet* mRoadNet, TiXmlElement *node)
{
    double sOffset;
    double forward;
    double back;
    double left;
    double right;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryDoubleAttribute("forward",&forward);
    checker+=node->QueryDoubleAttribute("back",&back);
    checker+=node->QueryDoubleAttribute("left",&left);
    checker+=node->QueryDoubleAttribute("right",&right);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }

    return true;
}

bool OpenDriveParser::ReadLaneSpeed(RoadNet* mRoadNet, TiXmlElement *node)
{
    double sOffset;
    double max;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryDoubleAttribute("max",&max);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }
    return true;
}

bool OpenDriveParser::ReadLaneAccess(RoadNet* mRoadNet, TiXmlElement *node)
{
    double sOffset;
    string restriction;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryStringAttribute("restriction",&restriction);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }

    return true;
}

bool OpenDriveParser::ReadLaneHeight(RoadNet* mRoadNet, TiXmlElement *node)
{
    double sOffset;
    double inner;
    double outer;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
    checker+=node->QueryDoubleAttribute("inner",&inner);
    checker+=node->QueryDoubleAttribute("outer",&outer);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Lane Weight attributes"<<endl;
        return false;
    }

    return true;
}

////--------------
bool OpenDriveParser::ReadObjects (RoadNet* mRoadNet, TiXmlElement *node)
{
    return true;
}

bool OpenDriveParser::ReadSignals (RoadNet* mRoadNet, TiXmlElement *node)
{
    return true;
}

bool OpenDriveParser::ReadSurface (RoadNet* mRoadNet, TiXmlElement *node)
{
    return true;
}

bool OpenDriveParser::ReadController (TiXmlElement *node)
{	return true;	}

////--------------

bool OpenDriveParser::ReadJunction (TiXmlElement *node)
{
    string name;
    string id;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryStringAttribute("name",&name);
    checker+=node->QueryStringAttribute("id",&id);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Junction attributes"<<endl;
        return false;
    }


    //Read connection parameters and add them to the lane if available
    TiXmlElement *subNode=node->FirstChildElement("connection");

    while (subNode)
    {
        ReadJunctionConnection(subNode);
        subNode=subNode->NextSiblingElement("connection");
    }


    //Read connection parameters and add them to the lane if available
    subNode=node->FirstChildElement("priority");

    while (subNode)
    {
        ReadJunctionPriority(subNode);
        subNode=subNode->NextSiblingElement("priority");
    }



    //Read connection parameters and add them to the lane if available
    subNode=node->FirstChildElement("controller");

    while (subNode)
    {
        ReadJunctionController(subNode);
        subNode=subNode->NextSiblingElement("controller");
    }


    return true;
};

bool OpenDriveParser::ReadJunctionConnection (TiXmlElement *node)
{
    int id;
    int incomingRoad;
    int connectingRoad;
    string contactPoint;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryIntAttribute("id",&id);
    checker+=node->QueryIntAttribute("incomingRoad",&incomingRoad);
    checker+=node->QueryIntAttribute("connectingRoad",&connectingRoad);
    checker+=node->QueryStringAttribute("contactPoint",&contactPoint);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Junction Connection attributes"<<endl;
        return false;
    }
    RoadNet* mRoadNet = mOpenDriveStruct.FindRoadNetById(incomingRoad);
    TiXmlElement *subNode=node->FirstChildElement("laneLink");

    while (subNode)
    {
        ReadJunctionConnectionLaneLink(mRoadNet, subNode, connectingRoad);
        subNode=subNode->NextSiblingElement("laneLink");
    }

    return true;
}

bool OpenDriveParser::ReadJunctionConnectionLaneLink (RoadNet* mRoadNet,TiXmlElement *node,int connectingRoad)
{
    int from;
    int to;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryIntAttribute("from",&from);
    checker+=node->QueryIntAttribute("to",&to);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Junction Lane Link attributes"<<endl;
        return false;
    }
    cout<<mRoadNet->id<<endl;
    if (from>0)
    {
        mRoadNet->left_successor_road_id.push_back(connectingRoad);
        mRoadNet->left_successor_road_direction.push_back(to);
    }
    else
    {
        mRoadNet->right_successor_road_id.push_back(connectingRoad);
        mRoadNet->right_successor_road_direction.push_back(to);
    }

    return true;
}

bool OpenDriveParser::ReadJunctionPriority (TiXmlElement *node)
{
    string high;
    string low;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryStringAttribute("high",&high);
    checker+=node->QueryStringAttribute("low",&low);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Junction Priority attributes"<<endl;
        return false;
    }

    return true;
}

bool OpenDriveParser::ReadJunctionController (TiXmlElement *node)
{
    string id;
    string type;

    int checker=TIXML_SUCCESS;
    checker+=node->QueryStringAttribute("id",&id);
    checker+=node->QueryStringAttribute("type",&type);
    if (checker!=TIXML_SUCCESS)
    {
        cout<<"Error parsing Junction Controller attributes"<<endl;
        return false;
    }
    return true;
}
