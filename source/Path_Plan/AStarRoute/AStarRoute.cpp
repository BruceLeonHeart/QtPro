#include "AStarRoute.h"

AStarRoute::AStarRoute()
{
     string fileName = "/home/pz1_ad_04/qtcreater/source/RealMap2.xml";
   // string fileName = "/home/pz1_ad_04/qtcreater/source/demomap.xml";
    mOpenDriveParser.ReadFile(fileName);
}

double AStarRoute::getGCost(Node* current,PathNode* neighbor){
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    unsigned long mRoadNetLength = mRoadNetVector.size();
    double neighborLength= 0.0;
    for (unsigned long i = 0; i < mRoadNetLength; i++) {
        if(mRoadNetVector.at(i).id == neighbor->id)
        {
            neighborLength = mRoadNetVector.at(i).length;
            break;
        }
    }
    return current->gCost + neighborLength;
}

double AStarRoute::getHCost(Point* endPoint,PathNode* neighbor)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    double endx = 0.0;
    double endy = 0.0;
    RoadNet* currentRoadNet = NULL;
    unsigned long mRoadNetLength = mRoadNetVector.size();
    for (unsigned long i = 0; i < mRoadNetLength; i++) {
        if(mRoadNetVector.at(i).id == neighbor->id)
        {
            currentRoadNet = &mRoadNetVector.at(i);
            break;
        }
    }

    if(neighbor->direction == -1)
    {
        endx = currentRoadNet->end_x;
        endy = currentRoadNet->end_y;
    }
    if(neighbor->direction == 1)
    {
        endx = currentRoadNet->start_x;
        endy = currentRoadNet->start_y;
    }
    return getPointsDis(endx,endy,endPoint->x,endPoint->y);

}

double AStarRoute::getFCost(Node* node)
{
    return node->gCost + node->hCost;
}

void AStarRoute::AStarMain(Point* start,Point* end)
{
    //如果终点落在起点与第一个要去的点中间，则直接返回
    //包含两种情况：roadNum与GeoNum一致
    //roadNum与GeoNum不一致
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    if (start->RoadNum == end->RoadNum && start->direction == end->direction)
    {
        PathNode mPathNode;
        if (start->direction == -1  && start->s_inGeo <=  end->s_inGeo)//右侧
        {
           mPathNode.id = start->RoadNum;
           mPathNode.direction = start->direction;
           mPath.push_back(mPathNode);
           return;
        }

        if (start->direction == 1  && start->s_inGeo >  end->s_inGeo)//左侧
        {
           mPathNode.id = start->RoadNum;
           mPathNode.direction = start->direction;
           mPath.push_back(mPathNode);
           return;
        }
    }

    //添加起点进入openList
    Node node ={};
    node.x = start->x_e_offset;
    node.y = start->y_e_offset;
    node.gCost = getPointsDis(start->x_e_offset,start->y_e_offset,start->x_offset,start->y_offset);
    node.hCost = getPointsDis(start->x_e_offset,start->y_e_offset,end->x_offset,end->y_offset);
    node.fCost = getFCost(&node);
    node.id = start->RoadNum;
    node.direction = start->direction;
    node.preId = -1;
    node.preDirection =-1;
    openList.push_back(node);

    while (openList.size()>0) {
        Node currentNode = getCrtFromOpenList(&openList);

        //如果current　road/direction　与终点一致，则回溯路径，结束遍历
        if(currentNode.id == end->RoadNum && currentNode.direction == end->direction){
            PathNode final ={};
            final.id = currentNode.id;
            final.direction = currentNode.direction;
            mPath.push_back(final);
            reconstruction(currentNode,&mPath);
            return;

        }

        //将current添加到ClosedList中
        closedList.push_back(currentNode);
        openList.erase(openList.begin());
        //遍历邻居
        vector<PathNode> NeighborSet;
        getNeighborSetFromRoadNet(currentNode.id,currentNode.direction,&NeighborSet);

        for (unsigned long i = 0; i< NeighborSet.size();i++) {
            int neighborId = NeighborSet.at(i).id;
            int neighborDirec = NeighborSet.at(i).direction;

            if (neighborId == end->RoadNum && neighborDirec == end->direction)
            {
                PathNode tmp;
                tmp.id = end->RoadNum;
                tmp.direction = end->direction;
                mPath.push_back(tmp);
                tmp.id = currentNode.id;
                tmp.direction = currentNode.direction;
                mPath.push_back(tmp);
                reconstruction(currentNode,&mPath);
                return;
            }

            if(isInList(neighborId,neighborDirec,&closedList))
                continue;

            double tempGCost = getGCost(&currentNode,&NeighborSet.at(i));

            if(!isInList(neighborId,neighborDirec,&openList)){
                Node temp ={};
                temp.id = neighborId;
                temp.direction = neighborDirec;
                RoadNet* NeighRoad = getRoadNetById(neighborId);
                temp.x = NeighRoad->end_x;
                temp.y = NeighRoad->end_y;
                temp.gCost = getGCost(&currentNode,&NeighborSet.at(i));
                temp.hCost = getHCost(end,&NeighborSet.at(i));
                temp.fCost = getFCost(&temp);
                temp.preId = currentNode.id;
                temp.preDirection = currentNode.direction;
                openList.push_back(temp);
            }
            else {
                Node* origin = getOriginMsg(neighborId,neighborDirec,&openList);;
                if(tempGCost >= origin->gCost)
                    continue;
                else {
                    origin->gCost = tempGCost;
                    origin->fCost = getFCost(origin);
                }
            }
        }
    }
}

Node AStarRoute::getCrtFromOpenList(vector<Node>* openList){
    sort(openList->begin(),openList->end(),comparison);
    return openList->at(0);

}

bool AStarRoute::comparison(Node a, Node b)
{
    return a.fCost < b.fCost;
}

bool AStarRoute::isInList(int RoadNum, int direction, vector<Node> *List)
{
    bool flag = false;
    for (unsigned long i = 0;i< List->size();i++) {
        if(List->at(i).id == RoadNum && List->at(i).direction == direction)
        {
            flag = true;
            break;
        }

    }
    return  flag;

}

void AStarRoute::getNeighborSetFromRoadNet(int id, int direction,vector<PathNode>* NeighborSet)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    RoadNet* crtRoad = NULL;
    for (unsigned long i = 0;i<mRoadNetVector.size();i++) {
        if(id == mRoadNetVector.at(i).id)
        {
            crtRoad = &mRoadNetVector.at(i);
            break;
        }

    }
    vector<int> roadSet;
    vector<int> directionSet;
    assert(direction != 0);
    if(direction == -1)
    {
        roadSet = crtRoad->right_successor_road_id;
        directionSet = crtRoad->right_successor_road_direction;
    }

    if(direction == 1)
    {
        roadSet = crtRoad->left_successor_road_id;
        directionSet = crtRoad->left_successor_road_direction;
    }

    unsigned long roadSetSize = roadSet.size();
    unsigned long directionSetSize = directionSet.size();
    assert( roadSetSize == directionSetSize);
    unsigned long size = roadSet.size();
    PathNode tmp;
    for(unsigned long j = 0;j<size;j++)
    {
        if (fabs(directionSet.at(j)) == 1) //只考虑路网中正负1的道路
        {
            tmp.id = roadSet.at(j);
            tmp.direction = directionSet.at(j);
            NeighborSet->push_back(tmp);
        }
    }
}

void AStarRoute::reconstruction(Node current,vector<PathNode>* mPath)
{
    PathNode tmp;
    while(!(current.preId == -1 && current.preDirection == -1)){
        tmp.id = current.preId;
        tmp.direction = current.preDirection;

        mPath->push_back(tmp);
        current = getPreNode(current.preId,current.preDirection,&closedList);

    }
}

RoadNet* AStarRoute::getRoadNetById(int  id)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    RoadNet* res = NULL;
    for (unsigned long i =0;i<mRoadNetVector.size();i++) {
        if (id == mRoadNetVector.at(i).id)
        {
            res = &mRoadNetVector.at(i);
            break;
        }
    }
    return res;
}

Node* AStarRoute::getOriginMsg(int id, int direction, vector<Node> *openList)
{
    Node* choose;
    for (unsigned long i = 0; i<openList->size();i++) {
        if(openList->at(i).id == id && openList->at(i).direction ==direction)
        {
            choose = &openList->at(i);
        }
    }
    return choose;
}

void AStarRoute::getDataSet(vector<PathNode> *mPath, Point *start, Point *end,vector<double>* xSet,vector<double>* ySet)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    unsigned long mPathLength = mPath->size();
    double start_s = 0.0;
    double end_s = 0.0;
    //
    if(mPathLength == 1)
    {
     start_s = start->s_inGeo;
     end_s = end->s_inGeo;
     getDatapathCommon(mPath->at(0).id,mPath->at(0).direction,start_s,end_s,xSet,ySet);
     return;
    }

    for (unsigned long i =0;i<mPathLength;i++) {
        int direction = sign(mPath->at(i).direction);
        RoadNet* crtRoad = getRoadNetById(mPath->at(i).id);
        vector<GeoObj> Geos = crtRoad->Geos;
        double RoadGeoEnd = Geos.at(Geos.size()-1).s + Geos.at(Geos.size()-1).length;
        vector<double> xTmp;
        vector<double> yTmp;
        //起始段
        if(i == mPathLength -1)
        {
             start_s = start->s_inGeo;
             if(direction == -1)
                 end_s = RoadGeoEnd;
             else
                 end_s = 0;
             getDatapathCommon(mPath->at(i).id,mPath->at(i).direction,start_s,end_s,&xTmp,&yTmp);
             xSet->insert(xSet->begin(),xTmp.begin(),xTmp.end());
             ySet->insert(ySet->begin(),yTmp.begin(),yTmp.end());
        }

        //终止段
        else if(i == 0)
        {
            end_s = end->s_inGeo;
            if(direction == -1)
                start_s = 0;
            else
                start_s = RoadGeoEnd;
            getDatapathCommon(mPath->at(i).id,mPath->at(i).direction,start_s,end_s,&xTmp,&yTmp);
            xSet->insert(xSet->end(),xTmp.begin(),xTmp.end());
            ySet->insert(ySet->end(),yTmp.begin(),yTmp.end());
        }
        else {
            if(direction == -1)
            {
                start_s = 0;
                end_s = RoadGeoEnd;
            }

            else
            {
                start_s = RoadGeoEnd;
                end_s = 0;
            }
            getDatapathCommon(mPath->at(i).id,mPath->at(i).direction,start_s,end_s,&xTmp,&yTmp);
            xSet->insert(xSet->begin(),xTmp.begin(),xTmp.end());
            ySet->insert(ySet->begin(),yTmp.begin(),yTmp.end());
        }

    }

}

void AStarRoute::getDatapathCommon(int id, int direction, double start_s, double end_s,vector<double>* xSet,vector<double>* ySet)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    double delta_s = 1.0;
    int N = floor(fabs((end_s - start_s) / delta_s));
    double sValueSet[N];
    for (int i = 0; i<N; i++) {
        sValueSet[i] = start_s + i*(-direction)*delta_s;
        double data[3];

        unsigned long size = mRoadNetVector.size();
        unsigned long k = size;

        for(unsigned long j=0;j<size;j++)
        {
                if (mRoadNetVector.at(j).id == id)
                {
                    k = j;
                    break;
                }
         }

        mOpenDriveParser.mOpenDriveStruct.GetXYHdgByS(k,sValueSet[i],data);
        //取offset一半作为轨迹点
        double x = data[0];
        double y = data[1];
        double hdg = data[2];
//        double offset = mOpenDriveStruct->GetSOffset(sValueSet[i],direction,mRoadNetVector,id);
//         x = x + offset*cos(hdg + sign(direction)*M_PI/2)/2;
//         y = y + offset*sin(hdg + sign(direction)*M_PI/2)/2;
        xSet->push_back(x);
        ySet->push_back(y);
    }
}

Point AStarRoute::pointBelong(double xp, double yp)
{
    vector<RoadNet> mRoadNetVector = mOpenDriveParser.mOpenDriveStruct.mRoadNetVector;
    vector<Point> disList;
    unsigned long size = mRoadNetVector.size();
    for (unsigned long i = 0; i<size;i++) {
        if(mRoadNetVector.at(i).junction == -1)
        {
            for(unsigned long j =0;j<mRoadNetVector.at(i).Geos.size();j++)
            {
                GeoObj tmp = mRoadNetVector.at(i).Geos.at(j);
                if(tmp.lineType.compare("line") == 0)
                {
                    double Geo_s = tmp.s;
                    double Geo_s_end = tmp.s + tmp.length;
                    double Geo_x_start = tmp.x;
                    double Geo_y_start = tmp.y;
                    double Geo_x_end = tmp.x + tmp.length*cos(tmp.hdg);
                    double Geo_y_end = tmp.y + tmp.length*sin(tmp.hdg);
                    double data [3];
                    getCrossMsg(Geo_x_start,Geo_y_start,tmp.hdg,xp,yp,data);
                    double v = data[0];
                    double x = data[1];
                    double y = data[2];

                    bool flag1= (x<=fmax(Geo_x_start,Geo_x_end))&&(x>=fmin(Geo_x_start,Geo_x_end));
                    bool flag2= (y<=fmax(Geo_y_start,Geo_y_end))&&(y>=fmin(Geo_y_start,Geo_y_end));

                    if(!(flag1&&flag2))
                        continue;

                    double s_inGeo = Geo_s + getPointsDis(x,y,Geo_x_start,Geo_y_start);
                    int direction = sideJudge(Geo_x_start,Geo_y_start,Geo_x_end,Geo_y_end,xp,yp);
                    double offset = mOpenDriveParser.mOpenDriveStruct.GetSOffset(s_inGeo,direction,i);
                    //计算参考线的交点关于offset的偏移
                    double hdg = tmp.hdg;
                    double x_offset = x + offset * cos(hdg  + direction*M_PI/2); //偏移后
                    double y_offset = y + offset * sin(hdg  + direction*M_PI/2); //偏移后
                    double x_s_offset,x_e_offset,y_s_offset,y_e_offset;
                    //同向偏移
                    if (direction == -1)
                    {
                         x_s_offset = Geo_x_start + offset * cos(hdg + direction*M_PI/2); //偏移后
                         y_s_offset = Geo_y_start + offset * sin(hdg + direction*M_PI/2); //偏移后
                         x_e_offset = Geo_x_end + offset * cos(hdg + direction*M_PI/2); //偏移后
                         y_e_offset = Geo_y_end + offset * sin(hdg + direction*M_PI/2); //偏移后
                    }


                    //反向偏移
                    if (direction == 1)
                    {
                         x_s_offset = Geo_x_end + offset * cos(hdg + direction*M_PI/2); //偏移后
                         y_s_offset = Geo_y_end + offset * sin(hdg + direction*M_PI/2); //偏移后
                         x_e_offset = Geo_x_start + offset * cos(hdg + direction*M_PI/2); //偏移后
                         y_e_offset = Geo_y_start + offset * sin(hdg + direction*M_PI/2); //偏移后
                    }

                    Point point;
                    point.v = fabs(v);
                    point.x = x;
                    point.y = y;
                    point.RoadNum = mRoadNetVector.at(i).id ;
                    point.direction = direction;
                    point.hdg = hdg;
                    point.x_s = Geo_x_start;
                    point.y_s = Geo_y_start;
                    point.x_e = Geo_x_end;
                    point.y_e = Geo_y_end;
                    point.s_inGeo = s_inGeo;
                    point.offset = offset;
                    point.x_offset = x_offset;
                    point.y_offset = y_offset;
                    point.x_s_offset = x_s_offset;
                    point.y_s_offset = y_s_offset;
                    point.x_e_offset = x_e_offset;
                    point.y_e_offset = y_e_offset;
                    point.GeoIdx = j;
                    point.s_start = Geo_s;
                    point.s_end = Geo_s_end;
                    disList.push_back(point);
                }
            }
        }
    }
    sort(disList.begin(),disList.end(),comparisonPoint);
    return disList.at(0);
}

bool AStarRoute::comparisonPoint(Point A,Point B)
{
    return A.v < B.v;
}

Node AStarRoute::getPreNode(int id, int direction, vector<Node> *closedList)
{
    Node choose;
    for (unsigned long i = 0; i<closedList->size();i++) {
        if(closedList->at(i).id == id && closedList->at(i).direction ==direction)
        {
            choose = closedList->at(i);
        }
    }
    return choose;
}
