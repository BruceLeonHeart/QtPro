#ifndef MATHUTILS_H
#define MATHUTILS_H
#include<math.h>

//https://blog.csdn.net/qdlovecsj/article/details/10075847
//左矩形法
double integral(double hdg,double curvStart,double c,
                double down,double up,long int N,int flag);


//两点间欧氏距离
double getPointsDis(double x1,double y1,double x2,double y2);

//求解三次多项式值
double getOffsetByS(double delta_s,double offset[]);

//linspace function
void linSpace(double x1,double x2,int n,double *y);

//sign
int sign(double x1);

/*计算点与直线的交点信息
 * v:距离
 * x:横坐标
 * y:纵坐标
 **/
void getCrossMsg(double x_start,double y_start,double hdg,double Point_x,double Point_y,double* result);


//令矢量的起点为A，终点为B，判断的点为C，
//如果S（A，B，C）为正数，则C在矢量AB的左侧；
//如果S（A，B，C）为负数，则C在矢量AB的右侧；
//如果S（A，B，C）为0，则C在直线AB上
int sideJudge(double x1,double y1,double x2,double y2,double x3,double y3);



#endif // MATHUTILS_H
