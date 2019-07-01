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

//欧氏距离
double getPointsDis(double x1,double y1,double x2,double y2){
    double delta_x = abs(x1-x2);
    double delta_y = abs(y1-y2);
    return sqrt(delta_x * delta_x + delta_y + delta_y);
}

//求Offset
double getOffsetByS(double delta_s,double offset[]){

    return offset[0] + offset[1] * delta_s   + offset[2] * pow(delta_s,2) + offset[3] * pow(delta_s,3);
}

void linSpace(double x1,double x2,int n,double *y)
{
    double d = (x2-x1)/(n-1);
    for (int i = 0 ; i<n;i++) {
        y[i] = x1 +i *d;
    }
}

int sign(double x1)
{
    if (x1 > 0.0)
        return 1;
    else if (x1 < 0.0)
        return -1;
    else
        return 0;

}
