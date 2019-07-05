#include <iostream>
#include <fstream>
#include<vector>
#include "Student.h"
using namespace std;
#include<stdlib.h>

void setValue(double* y){
    y[0] =0.0;
    y[1] =0.1;
}

void CreatTxt(char* pathName, unsigned char* rBuffer,int length)//创建txt文件
{
 //char* path = "C:\\1.txt"; // 你要创建文件的路径
 ofstream fout(pathName);
 if (fout) { // 如果创建成功
  for (int i = 0; i < length; i++)
  {
   fout <<"写入的内容"<< endl; // 使用与cout同样的方式进行写入


  }

  fout.close();  // 执行完操作后关闭文件句柄
 }
}


int main()
{
    vector<int> a(15);
    a[3] = 7;
    for (int i = 0; i < a.size(); i++)
    {
     cout <<a.at(i)<< endl; // 使用与cout同样的方式进行写入


    }
//    Student st1;
//    Student* st2;
//    st2 = new Student;
//    st2->h = 1.7;
//    Student* st3;
//    st3 =st2;
//    st3->h = 1.8;

//    st1.show();
//    st2->show();
//    st3->show();
//    FILE *fp;
//    char path[64] = "/home/pz1_ad_04/桌面/2.txt";
//    fp = fopen(path,"w");
//    vector<int> x;
//    vector<int> y;
//    for (int i =0;i<8;i++) {
//        x.push_back(i);
//        y.push_back(2*i);
//    }
//     ofstream fout(path);
//     for (int i = 0; i <x.size(); i++)
//     {
//      fout <<x.at(i)<<","<<y.at(i)<< endl; // 使用与cout同样的方式进行写入


//     }


    system("pause");
    return 0;
}

