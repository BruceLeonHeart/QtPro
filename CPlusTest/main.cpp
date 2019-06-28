#include <iostream>
#include "Student.h"
using namespace std;
#include<stdlib.h>

void setValue(double* y){
    y[0] =0.0;
    y[1] =0.1;
}



int main()
{
    Student st1;
    Student* st2;
    double* z;
    setValue(z);
    cout<<*(z+1)<<endl;
    st1.show();
    st2->show();
    system("pause");
    return 0;
}

