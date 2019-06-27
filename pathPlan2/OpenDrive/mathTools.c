#include "mathTools.h"
//左矩形法求定积分
double integral(double hdg,double curvStart,double c,
                double down,double up,long int N,int flag){
    double h,s;
    int i;
    //计算步长
    h = (up-down)/N;

    double y;
    if (flag == 0)//余弦
        y = cos(hdg);
    else
        y = sin(hdg);

    s = y*h;

    double temp_y;
    for (i =1;i<N;i++)
    {
        if (flag == 0)//余弦
            temp_y = cos( hdg + curvStart*(down + i*h) + c/2.0*(down + i*h)*(down + i*h));
        else
            temp_y = sin( hdg + curvStart*(down + i*h) + c/2.0*(down + i*h)*(down + i*h));

        s = s + temp_y*h;
    }
    return s;

}


double getPointsDis(double x1,double y1,double x2,double y2){
    double delta_x = abs(x1-x2);
    double delta_y = abs(y1-y2);
    return sqrt(delta_x * delta_x + delta_y + delta_y);
}
