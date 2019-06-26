#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
using std::endl;
using std::cout;
#include<string>
using std::string;

class Student
{
private:
    string name;
    int age;
public:
    Student();
    void show();
};

#endif // STUDENT_H
