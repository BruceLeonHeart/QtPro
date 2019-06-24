#ifndef ASTAR_H
#define ASTAR_H
#include<list>
struct Node
{
   double xFinal;
   double yFinal;
   double gCost;
   double hCost;
   double fCost;
   Node *parent;
   int roadNum;
   int direction;
};


class AStar
{
public:
    AStar();
private:
    Node *isInList(const std::list<Node *> &list, const Node *node) const; //判断开启/关闭列表中是否包含某点
    double calcG(Node *temp_start, Node *point);
    double calcH(Node *point, Node *end);
    double calcF(Node *point);
private:
    std::list<Node *> openList;  //开启列表
    std::list<Node *> closeList; //关闭列表
};

#endif // ASTAR_H
