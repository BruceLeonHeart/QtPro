#include<iostream>
#include<cassert>
#include<string.h>
using namespace std;


//权位与小节
//中文数字的0
//1.以10000为小节，小节结尾即使是0，也不用零
//2.小节内两个非零数字之间要使用0
//3.当小节千位为0，前一小节无其他数字，不用零，否则用零

const int CHN_NUM_CNT = 10;
const char *chnNumChar [CHN_NUM_CNT]= { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
const char *chnUnitChar [] = {"","十","百","千"};
const char *chnUnitSection[] = {"","万","亿","万亿"};

typedef struct
{
    int num;
    const char* chnNum;
} TEST_DATA;

TEST_DATA testPair[] =
{
    {0, "零"},
    {1, "一"},
    {2, "二"},
    {3, "三"},
    {4, "四"},
    {5, "五"},
    {6, "六"},
    {7, "七"},
    {8, "八"},
    {9, "九"},
    {10, "一十"},
    {11, "一十一"},
    {110, "一百一十"},
    {111, "一百一十一"},
    {100, "一百"},
    {102, "一百零二"},
    {1020, "一千零二十"},
    {1001, "一千零一"},
    {1015, "一千零一十五"},
    {1000, "一千"},
    {10000, "一万"},
    {20010, "二万零一十"},
    {20001, "二万零一"},
    {100000, "一十万"},
    {1000000, "一百万"},
    {10000000, "一千万"},
    {100000000, "一亿"},
    {1000000000, "一十亿"},
    {1000001000, "一十亿一千"},
    {1000000100, "一十亿零一百"},
    {200010, "二十万零一十"},
    {2000105, "二百万零一百零五"},
    {20001007, "二千万一千零七"},
    {2000100190, "二十亿零一十万零一百九十"},
    {1040010000, "一十亿四千零一万"},
    {200012301, "二亿零一万二千三百零一"},
    {2005010010, "二十亿零五百零一万零一十"}
 //   {4009060200, "四十亿零九百零六万零二百"},
 //   {4294967295, "四十二亿九千四百九十六万七千二百九十五"}
};

void sec2chn(unsigned int section,std::string& str)
{

    str.clear();
    int unitPos = 0;
    string tmp;
    bool zero = true;
    while(section > 0)
    {
        int v = section%10;
        if(v==0)
        {

            if((section ==0) ||!zero)
            {
                zero = true;
                str.insert(0,chnNumChar[v]);
            }
        }
        else
        {
            zero = false;

            tmp.insert(0,chnUnitChar[unitPos]);
            tmp.insert(0,chnNumChar[v]);
            str.insert(0,tmp);
        }

        unitPos++;
        section = section/10;
    }
}


void num2chn(unsigned int num,std::string& chnStr)
{
    //定义节权游标
    chnStr.clear();
    int secPos = 0;
    string tmp;
    bool needZero = false;

    while(num>0)
    {
        //对10000取余
        unsigned int section = num%10000;
        if(needZero)
        {
            chnStr.insert(0,chnNumChar[0]);
        }
        sec2chn(section,tmp);
        //是否需要节权位
        tmp += (section!=0) ? chnUnitSection[secPos]:chnUnitSection[0];
        chnStr.insert(0,tmp);
        //千位是0则需要在下一个section前补零
        needZero = (section <1000) && (section >0);
        num = num/10000;
        secPos ++;
    }
}



void testNum2Chn()
{
    std::string chnNum;
    for (int i = 0 ; i< sizeof (testPair)/sizeof (testPair[0]);i++) {
        num2chn(testPair[i].num,chnNum);
        assert(strcmp(chnNum.c_str(),testPair[i].chnNum) == 0);
    }
}

int main()
{
    testNum2Chn();
//    std::string str;
//    num2chn(19864,str);
//    cout<<str<<endl;

}
