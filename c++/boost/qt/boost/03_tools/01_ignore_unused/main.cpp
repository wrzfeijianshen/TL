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

void output(int i)
{
    cout << i << endl;
}

void test5()
{
#if 0
    for(uint8_t i = 0; i < 4; i++)
    {
        thread t(output,i);
        t.detach();
    }
#endif
#if 0
    for(int i = 0;i < 4;i++)
    {
        thread t( [i]{
            cout << i << endl;
        });
        t.detach();
    }
#endif
}

class Task
{
public:
    void operator()(int i)
    {
        cout << i << endl;
    }
};

void test6()
{
#if 0
    for(int i = 0;i < 4; i++)
    {
        Task task;
        thread t(task,i);
        t.detach();
    }
#endif
    // detach方式，启动的线程自主在后台运行，当前的代码继续往下执行，不等待新线程结束
    // join方式，等待启动的线程完成，才会继续往下执行。假如前面的代码使用这种方式，其输出就会0,1,2,3，因为每次都是前一个线程输出完成了才会进行下一个循环，启动下一个新线程。
    for(int i = 0;i < 4; i++)
    {
        Task task;
        thread t(task,i);
        t.join();
    }
}
class _tagNode
{
public:
    int a;
    int b;
public:
    void do_some_work(int a);
};

void funcTest7(_tagNode &node)
{
    node.a = 10;
    node.b = 20;
}

void test7()
{
//    _tagNode node;
//    thread t(funcTest7,node);
//    t.join();
//    cout << node.a << endl;
//    cout << node.b << endl;
}
void funcTest8(int id,int b,int c)
{
    cout << "id ： "<< id << " " << "c" << endl;
}
void test8()
{
    cout << "test8 start" <<endl;

    int id = 0;
    int b = 0;
    int c = 0;
    thread t(funcTest8,id,b,c);
    int aa = static_cast<int>(t.get_id());
    std::thread::id t = t1.get_id();

    std::ostringstream oss;
        oss << std::this_thread::get_id();
        std::string stid = oss.str();
        unsigned long long tid = std::stoull(stid);

    cout << t.get_id() << endl;
    t.join();
    cout << "test8 end" <<endl;
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
    //    test5();
    //    test6();
//    test7();
    test8();

    getchar();
    return 0;
}
