#include <iostream>
#include <boost/core/ignore_unused.hpp>
//#include <boost/optional.hpp>
#include <string>
#include <thread>
#include <windows.h>

using namespace std;

int test1(int x,int y)
{
    int i = 0;
    int j = 0;
    //    boost::ignore_unused(x,i);// 忽略变量轻易的消除警告信息
    //    boost::ignore_unused(j);
    //    boost::ignore_unused(x,i,j);
    typedef int int_Diy;// 未使用的类型定义
    boost::ignore_unused<int_Diy>();
    boost::ignore_unused<int>(x,i,j);
    return y;
}

// optional
void test2()
{
    //     boost::optional<int> op0;  //一个未初始化的optional对象
    //    boost::optional<int> op0;
    //    boost::optional<int> op1(none);
    //    assert(!op0);
    //    assert(op0 == op1);
    //    assert(op1.value_or(253) == 253);
    //    boost::optional<string> ops("test");  //初始化为字符串test
    //    string str = *ops;     //用解引用操作符获取值
    //    cout <<str.c_str()<<endl;
    //    vector<int> v(10);
    //    boost::optional<vector<int>&> opv(v);  //容纳一个容器的引用
    //    assert(opv);
    //    opv->push_back(5);     //使用箭头操作符操纵容器
    //    assert(opv->size() == 11);
    //    opv = none;
    //    assert(!opv);
}

void funcTest1()
{
    cout << "funcTest1" << endl;
    Sleep(1000);
    cout << "funcTest end" << endl;
}

void test3()
{
    std::thread t(funcTest1);
    t.join();
    cout << "Test3" << endl;
}

void test4()
{
    int n1 = 500;
    int n2 = 600;
    std::thread t([&](int addNum){
        n1 += addNum;
        n2 += addNum;
    },n1);
    t.join();
    cout << n1 << " : " << n2 << endl;
}

int main()
{
    system("chcp 65001");// 设置编码输出为中文
//       int x =  test1(3,4);
//        cout << "test1 : " << x <<endl;
//        test2();
//        test3();
//        cout << "test3 "<<endl;
//    test4();

    return 0;
}
