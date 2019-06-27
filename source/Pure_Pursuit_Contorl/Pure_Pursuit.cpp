#include <iostream>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "CAN_Driver/ICANCmd.h"
#include "GPS_Driver/spatial_packets.h"
#include "Pure_Pursuit_Contorl/Pure_Pursuit.h"

#define pi 3.1415926
using namespace std;

int calc_target_index(float* state, int target_num,float k,int Lfc);
float pure_pursuit_control(float* state, int L, int target_index, int target_num,float k,int Lfc);
float A_Control(float* state,float target_speed, float dt);
int Target_route(float* target_x, float* target_y);

const double longitude_orig = 113.171198359442;
const double latitude_orig = 23.384265425953;
const int longitude_step = 101950;
const int latitude_step = 111210;
extern Msg_Send SendMsg;
extern Msg_Rec RecMsg;
extern system_state_packet_t system_state_packet;


vector<double> target_x;
vector<double> target_y;
vector<double> yaw;

void Target_route()
{

    ifstream inFile("11.txt",ios::in);
    string lineStr;
    vector<double> latitude;
    vector<double> longtitude;
    vector<vector<string>> strArray;

    while(getline(inFile,lineStr))
    {
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;

        while(getline(ss,str,','))
            lineArray.push_back(str);

        strArray.push_back(lineArray);
    }


    for (int i=0;i<strArray.size();i++) {
        longtitude.push_back(atof(strArray[i][0].c_str()));
        latitude.push_back(atof(strArray[i][1].c_str()));
    }

    for (int j=0;j<strArray.size();j++) {
        target_x.push_back((longtitude[j] - longitude_orig)*longitude_step);
        target_y.push_back((latitude[j] - latitude_orig)*latitude_step);
    }
}

int Pure_Pursuit_main()
{

    // Parameter needed
    float L = 2.7;

    float x = (system_state_packet.longitude * 180/pi - longitude_orig) * longitude_step; // target_x[0]+10;
    float y = (system_state_packet.latitude * 180/pi - latitude_orig) * latitude_step; //target_y[0]-5;
    float yaw =  system_state_packet.orientation[2]; // 3*pi/2;
    cout << yaw << endl;
    float v = RecMsg.WheelSpeed_F.VehicleSpeed_copy / 3.6;      // m/s
    float state[4] = {x, y, yaw, v};

    float  steering_factor = 19.496382;
    float k = 0.3;
    int Lfc = 6;
    float dt = 0.1;
    float target_speed = 8/3.6;
    float delta;
    int target_index;
    int target_num = target_x.size();


    target_index = calc_target_index(state,target_num,k,Lfc);

    delta = pure_pursuit_control(state,L,target_index,target_num,k,Lfc);
    float Accele = A_Control(state,target_speed,dt);


    float dis = sqrt(pow((state[0] - target_x[target_num-1]),2) + pow((state[1] - target_y[target_num-1]),2));
    if (target_index == target_num-1 && dis < 1)
    {
            Accele = -0.5;
            delta = 0;
    }
    float Target_Angle = delta * steering_factor * 180/pi;
    if (Target_Angle > 540)
        Target_Angle = 540;
    else if (Target_Angle < -540)
            Target_Angle = -540;

    SendMsg.ADAS.ADAS_AcceleratedSpd = Accele;
    SendMsg.PAS2EPS.PAS_TargetSteerAngle = Target_Angle;
    printf("Accele %f delta %f \n",Accele,delta);

    return 0;
}



int calc_target_index(float* state, int target_num,float k,int Lfc)
{
    int min_dis = 10000;
    int index=0;
    float dis;
    float L_calc = 0;
    float Lf = k * state[3] + Lfc;
    float distance = 0;

    for (int i=0; i<(target_num-1); i++)
    {
        dis = sqrt(pow((state[0] - target_x[i]),2) + pow((state[1] - target_y[i]),2));
        if (dis < min_dis)
        {
            min_dis = dis;
            index = i;

        }
    }


    while (Lf >= L_calc && index < (target_num-1))
    {

        distance = sqrt(pow((target_x[index+1] - target_x[index]),2) + pow((target_y[index+1] - target_y[index]),2));
        L_calc = L_calc + distance ;
        index = index + 1;
    }

    return index;
}


float pure_pursuit_control(float* state, int L, int target_index, int target_num,float k,int Lfc)
{
    float tx, ty;
    float alpha;

    int index = target_index;
    if (index < target_num-1)
    {
        tx = target_x[index];
        ty = target_y[index];
    }
    else
    {
        tx = target_x[target_num-1];
        ty = target_y[target_num-1];
        index = target_num-1;
    }

    if (tx >= state[0])
       // change to GPS yaw
        alpha = state[2] - (pi/2 - atan((ty - state[1])/(tx - state[0])));
    else
        alpha = state[2] - (3*pi/2 - atan((ty - state[1])/(tx - state[0])));


    if (state[3] < 0)
        alpha = pi - alpha;

    float Lf = k * state[3] + Lfc;
    float delta = atan(2 * L * sin(alpha) / Lf);

    return delta;
}



float A_Control(float* state,float target_speed, float dt)
{
    float P, I, D;
    float A_P, A_I, A_D;
    P = 0.1;
    I = 0.1;
    D = 0.02;
    A_I = 0.0;

    A_P = P * (target_speed - state[3]);
    A_I += I * (target_speed - state[3]) * dt;
    A_D = D * (target_speed - state[3]) / dt;
    float Accele = A_P + A_I + A_D;
    float Accele_threshold = 0.5;
    if (Accele > Accele_threshold)
        Accele = Accele_threshold;
    else if (Accele < -Accele_threshold)
        Accele = -Accele_threshold;

    return Accele;
}
