#ifndef OPENDRIVESTRUCT_H
#define OPENDRIVESTRUCT_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::endl;
struct Header{

};


//道路几何
struct GeoObj{
    double s;
    double x;
    double y;
    double hdg;
    double length;
    string lineType;
    double curvature;
    double curvStart;
    double curvEnd;
};

//车道偏移几何
struct offsetObj{
    int idx;
    double s;
    int id;
    string type;
    double offset[4];
};


//声明路网结构
struct RoadNet{
    int id;
    double length;
    int junction;
    double left_min_time;
    double right_min_time;
    double start_x;
    double start_y;
    double end_x;
    double end_y;
    vector<int> left_successor_road_id;
    vector<int> left_successor_road_direction;
    vector<int> right_successor_road_id;
    vector<int> right_successor_road_direction;
    vector<GeoObj> Geos;
    vector<offsetObj> Offsets;

};


class OpenDriveStruct
{
public:
    vector<RoadNet> mRoadNetVector;
    Header mHeader;
public:
    OpenDriveStruct();
    unsigned int AddRoadNet( int id, double length, int junction);
    RoadNet* GetLastRoadNet();
};

#endif // OPENDRIVESTRUCT_H
