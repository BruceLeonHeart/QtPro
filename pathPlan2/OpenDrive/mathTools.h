#ifndef MATHTOOLS_H
#define MATHTOOLS_H
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

#endif // MATHTOOLS_H
