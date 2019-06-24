#ifndef OPENDRIVEPARSER_H
#define OPENDRIVEPARSER_H
#include <vector>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QMultiMap>
#include <QXmlStreamAttribute>
using std::vector;

struct RoadNet{ //声明路网结构
int id;
double length[20];
double left_min_time;
double right_min_time;
double start_x;
double start_y;
double end_x;
double end_y;
vector<int> left_successor_road_id;
vector<int> left_successor_road_lane;
vector<int> right_successor_road_id;
vector<int> right_successor_road_lane;
};

class OpenDriveParser
{
public:
    OpenDriveParser();
    ~OpenDriveParser();
    bool xmlStreamReaderFile(const QString fileName);
    bool parseOpenDrive (QXmlStreamReader *reader);
    bool parseHeader (QXmlStreamReader *reader);
    bool parseRoad (QXmlStreamReader *reader);
    bool parseJunction (QXmlStreamReader *reader);
};

#endif // OPENDRIVEPARSER_H
