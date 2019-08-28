#include<iostream>
using namespace std;

void fun1(int x)
{
    //修改的是y在栈中的copy x
    // 在内存中重新开辟了临时空间，将y值给过来
    //增加了程序运行时间，降低了效率
    x +=5;
}

void fun2(int *x)
{
    *x +=5; //修改指针x指向的内存单元值
}

void fun3(int &x)
{
    x += 5;  //修改的是x引用的对象值
}



int main()
{
    int y1 = 0;
    int y2 = 0;
    int y3 = 0;
    fun1(y1);
    fun2(&y2);
    fun3(y3);
    cout<< "y1 after operation  :" << y1 << endl;
    cout<< "y2 after operation  :" << y2 << endl;
    cout<< "y3 after operation  :" << y3 << endl;
    return 0;

}
