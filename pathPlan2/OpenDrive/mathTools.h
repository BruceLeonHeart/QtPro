#ifndef MATHTOOLS_H
#define MATHTOOLS_H
#include<math.h>

//https://blog.csdn.net/qdlovecsj/article/details/10075847
//左矩形法
double integral(double hdg,double curvStart,double c,
                double down,double up,long int N,int flag);


//两点间欧氏距离
double getPointsDis(double x1,double y1,double x2,double y2);


#endif // MATHTOOLS_H
