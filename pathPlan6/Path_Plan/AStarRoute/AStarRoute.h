#ifndef ASTARROUTE_H
#define ASTARROUTE_H
#include "../OpenDrive/OpenDriveStruct.h"
//sort方法
#include <algorithm>
using std::sort;
using std::reverse;
#include<vector>
extern "C"{
#include "../Utils/mathUtils.h"
}
#include<assert.h>

#include <iostream>
#include <fstream>
using std::ofstream;
struct Point{
    double v;
    double x;
    double y;
    int RoadNum;
    int direction;
    double hdg;
    double x_s;
    double y_s;
    double x_e;
    double y_e;
    double s_inGeo;
    double offset;
    double x_offset;
    double y_offset;
    double x_s_offset;
    double y_s_offset;
    double x_e_offset;
    double y_e_offset;
    int GeoIdx;
    double s_start;
    double s_end;
};

struct PathNode
{
    int id;
    int direction;

};

struct Node{
    int preId;
    int preDirection;
    int id;
    int direction;
    double gCost;
    double hCost;
    double fCost;
    double x;
    double y;
};

//全局规划接口基本点格式
struct waypointnode
{
    double lat;
    double lng;
    int type;
    bool b_left;
    bool b_right;
    bool b_left_rightlane;
    bool b_right_leftlane;
    double speed_limit;
    double lane_width;
    int road_id;
    int junction_Id;
    int geometryblock_id;
    int geometry_id;
    int laneSection_id;
    int lane_left_id;
    int lane_right_id;

};


class AStarRoute
{
public:
    AStarRoute();
    Point startPoint;//起始点
    Point endPoint;//终止点
    OpenDriveStruct* mOpenDriveStruct;
    vector<Node> openList;//开启列表
    vector<Node> closedList;//关闭列表
    vector<PathNode> mPath;//寻径结果
    vector<double> path_x;
    vector<double> path_y;
    vector<waypointnode> Globalpath;

public://点投影相关
    Point pointBelong(vector<RoadNet>* mRoadNetVector,double xp,double yp);
    static bool comparisonPoint(Point A,Point B);
public://算法相关
    //获取GCost
    double getGCost(Node* current,PathNode* neighbor,vector<RoadNet>* mRoadNetVector);
    //获取HCost
    double getHCost(Point* endPoint,PathNode* neighbor,vector<RoadNet>* mRoadNetVector);
    //获取FCost
    double getFCost(Node* node);
    //从OpenList中获取当前点
    Node  getCrtFromOpenList(vector<Node>* openList);
    static bool comparison(Node a,Node b);
    void AStarMain(Point* start,Point* end,vector<RoadNet>* mRoadNetVector);
    //根据ID从路网中获取对应的RoadNet
    RoadNet* getRoadNetById(int id,vector<RoadNet>* mRoadNetVector);
    //判断某个Road-direction是否处于List中
    bool isInList(int RoadNum,int direction,vector<Node>* List);
    //获取路网中的邻居
    void getNeighborSetFromRoadNet(int id,int direction,vector<RoadNet>* mRoadNetVector,vector<PathNode>* NeighborSet);
    //回溯矩阵获得路径
    void reconstruction(Node current,vector<PathNode>* mPath);
    //获取前继节点
    Node getPreNode(int id,int direction,vector<Node>* closedList);
    //更新OpenList
    void updateOpenList();
    //获取原始OpenList中指定id与direction对应的信息
    Node* getOriginMsg(int id,int direction,vector<Node>* openList);
public://点集相关
    //获取算法得到的路径
    void getDataSet(vector<PathNode>* mPath,Point* start,Point* end,vector<RoadNet>* mRoadNetVector);
    //指定路段获取点集
    void getDatapathCommon(int id,int direction,double start_s,double end_s,vector<RoadNet>* mRoadNetVector,vector<waypointnode>* path);
    //笛卡尔转换为GPS坐标系
    void CoorTransGPS(double* point);
    //点序列写入到文件
    void getDataFile();
};

#endif // ASTARROUTE_H
