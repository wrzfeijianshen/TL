#include <iostream>
#include <vector>
#include <boost/progress.hpp>
#include <fstream>
#include <windows.h>

using namespace std;

void case1()
{
    vector<string> v(100);
    ofstream fs("./test.txt");
    // 声明对象，基数是v的大小
    boost::progress_display pd(v.size());

    // 开始遍历向量，处理字符串，写入文件
    for(auto& x :v)
    {
        fs << x << endl;
        ++pd;
        Sleep(100);
    }
}

void case2()
{
    // 精简之后
    boost::progress_display pd(100);
    for(int i= 0 ; i < 100 ;i++)
    {
        ++pd;
        Sleep(100);
    }
}

void case3()
{
    // 不建议
    boost::progress_display pd(100,cout,"%%%","+++","???");
    for(int i= 0 ; i < 100 ;i++)
    {
        ++pd;
        Sleep(100);
    }
}

void case4()
{
    boost::progress_display pd(100);
    for(int i= 0 ; i < 100 ;i++)
    {
        ++pd;
        Sleep(100);
        if(i%10 == 0 && i!=30 && i!=40)
        {
            cout << "_整数 : " << i << endl;
        }
    }
}

int main()
{
    system("chcp 65001");// 设置编码输出为中文
//    case1();
//    case2();
//    case3();
    case4();
    return 0;
}
