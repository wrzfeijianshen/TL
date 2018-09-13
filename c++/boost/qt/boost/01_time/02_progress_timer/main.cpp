#include <iostream>
#include <boost/progress.hpp>
#include <windows.h>
#include <sstream>

using namespace std;

int main()
{
    system("chcp 65001");// 设置编码输出为中文

    boost::progress_timer t;// 生命一个progress_timer对象

    Sleep(1000);
    cout << "Hello World!" << endl;// 任意计算、处理工作

    cout << t.elapsed() << endl;// 输出流逝的时间
    {
        // 第1个计时开始
        boost::progress_timer t1;
        Sleep(2000);
    }
    {
        // 第2个计时开始
        boost::progress_timer t2;
        Sleep(3000);
    }

    stringstream ss;// 一个字符串流对象
    {
        // 第3个计时开始
        boost::progress_timer t3(ss);
        Sleep(2000);
    }
    cout << ss.str();

    return 0;
}
