#include "AStar.h"
#include<math.h>
#include <stdlib.h>
AStar::AStar()
{

}


Node *AStar::isInList(const std::list<Node *> &list, const Node *point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for (Node * p : list)
    if (p->xFinal == point->xFinal&&p->yFinal == point->yFinal){
        return p;
    }
    return NULL;
}


double AStar::calcG(Node *temp_start, Node *point)
{
    double extraG = abs(point->xFinal - temp_start->xFinal) + abs(point->yFinal - temp_start->yFinal);
    double parentG = point->parent == NULL ? 0 : point->parent->gCost; //如果是初始节点，则其父节点是空
    return parentG + extraG;

}

double AStar::calcH(Node *point, Node *end)
{
    //用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法，没深入研究^_^
    double delta_x = (double)(end->xFinal - point->xFinal);
    double delta_y = (double)(end->yFinal - point->yFinal);
    return sqrt(delta_x*delta_x + delta_y*delta_y);

}

double AStar::calcF(Node *point)
{
    return point->gCost + point->hCost;
};
