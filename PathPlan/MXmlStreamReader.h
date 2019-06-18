#ifndef MXMLSTREAMREADER_H
#define MXMLSTREAMREADER_H
#include<QXmlStreamReader>
#include<vector>
#include<list>

struct RoadNet{
    int id;
    double length;
    double start_x;
    double start_y;
    double end_x;
    double end_y;
    std::vector<int> left_successor_road_id;
    std::vector<int> left_successor_road_lane;
    std::vector<int> right_successor_road_id;
    std::vector<int> right_successor_road_lane;
};
class MXmlStreamReader
{
public:
    MXmlStreamReader();
    bool readFile(const QString &fileName);

private:
    void readHeaderElement();
    void readRoadElement();
    void readJunctionlement();


    QTreeWidget *treeWidget;
    QXmlStreamReader reader;
    std::list<RoadNet> mRoadNetList;

};

#endif // MXMLSTREAMREADER_H
