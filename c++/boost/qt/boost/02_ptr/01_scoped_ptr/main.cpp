#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

using namespace std;

class ptr_owned1 final
{
public:
    boost::scoped_ptr<int> m_ptr;
};

class ptr_owned final
{
    boost::scoped_ptr<int> m_ptr;
};

void test()
{
#if 0
    {
        boost::scoped_ptr<string> sp(new string("test"));
        assert(sp);
        assert(sp != nullptr);
        cout << "sp 不为空" << endl;
        cout <<  "*sp : " << *sp <<endl;
        cout << "sp.size() : " << sp->size() << endl;
        *sp = "_中文";
        cout <<  "*sp : " << *sp <<endl;
        cout << "sp.size() : " << sp->size() << endl;
        // UTF-8编码：一个英文字符等于一个字节
        // 一个中文（含繁体）等于三个字节。中文标点占三个字节，英文标点占一个字节
        //        sp = NULL;// err
        //        delete sp;// errr argument given to 'delete', expected pointer
        //        boost::scoped_ptr<string> sp2 = sp;// err 不能做拷贝构造

    }
    {
        ptr_owned p;
    }
#endif

#if 0 ///<-- 作用域指针
    // 一个作用域指针独占一个动态分配的对象。 对应的类名为 boost::scoped_ptr，它的定义在 boost/scoped_ptr.hpp
    //  boost::scoped_ptr是一个比较简单的智能指针，它能保证在离开作用域之后它所管理对象能被自动释放
    boost::scoped_ptr<int> i(new int);

    *i = 1;
    *i.get() = 2;
    i.reset(new int);
    *i = 10;
    cout << *i << endl;

#endif

#if 1
    class A
    {
    public:
        A()
        {
            cout << "A 构造" << endl;
        }
        A(string str)
        {
            m_str = str;
            cout << "A 构造"  << str<< endl;
        }
        ~A()
        {

            cout << "~A 构造"<< m_str << endl;
        }
        string m_str;
    };

    struct B
    {
    public:
        string num;
        SetB(string cout) { num = cout;}
        GetB() {cout << num <<  endl;}
    };

    cout << "start " <<endl;
#if 0
    {
        boost::scoped_ptr<A> aaa(new A);
        //        boost::scoped_ptr<A> aaa1(aaa);// 拷贝构造函数私有 error: within this context
        //boost::scoped_ptr<A> aaa1 = aaa;// =运算符重载私有
        boost::scoped_ptr<B> bbb(new B);
        bbb->SetB("_你好");
        bbb->GetB();

        vector<boost::scoped_ptr<A>> ptr ;
        //        ptr.push_back(aaa);
        // Error: push_back操作内部调用了scoped_ptr的=运算符重载函数
    }

    {
        A *a1 = new A;
        boost::scoped_ptr<A> ptr_a1(a1);
        boost::scoped_ptr<A> ptr_a2(a1);
        // 势必会多次调用delete以释放它们所管理的对象，从而造成程序运行出错
    }


    {
        boost::scoped_ptr<A> ptr_a1(new A("_a1"));
        boost::scoped_ptr<A> ptr_a2(new A("_a2"));
        //  根据栈的特性，应该是后面构造的scoped_ptr对象先销毁（从而销毁了它们所管理的对象），正是因为我们对两个智能指针的控制权进行交换之后，才出现了这种相反的结果。
        ptr_a2.swap(ptr_a1);
    }
    cout << "end" << endl;
#endif
    {
        boost::scoped_ptr<A> ptr_a1(new A("_A1"));
        ptr_a1.reset();
        cout << "_ptr_a1 释放了" << endl;
    }
#endif
}
// define中的三个特殊符号：#，##，#@
#define Tostring(x) #x // #，表示将跟在它之后的参数转换为字符串
#define Conn(x,y) x##y
//#define ToChar(x) #@x

// 返回数组元素的个数
#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( (a[0]) ) )
#define VAR_NAME(type, name)    type type##_##name
#define Name(type,name) type##_##name
#define VAR_NAME1(type, name)   type type##_name##name
#define A(x) T_##x
#define B(x) (#x[0])
#define C(x) #x
void test1()
{
    int n = Conn(12,34);
    if (n == 1234)
        cout << "1234 " << endl;
    cout << Tostring("_赫尔") << endl;
    cout << B(1) << endl;
    VAR_NAME(string , a3) = "AAA9";
    cout << Name(string,a3) << endl;
    Name(string,a3) = "10";
    cout << Name(string,a3) << endl;
//    cout << string_a3 << endl;
//    cout << VAR_NAME(int , ii) << endl;
}

void test2()
{
#if 0
    {
        boost::scoped_array<int> i(new int[2]);
        *i.get() = 1;
        i[1] = 2;
        *i.get() = 3;
        cout << i[0] << " : " << i[1] << endl;
        i.reset(new int [3]);
    }
#endif

#if 0
std::vector<boost::shared_ptr<int>> v;
v.push_back(boost::shared_ptr<int>(new int(10)));
v.push_back(boost::shared_ptr<int>(new int(20)));
 for(auto i : v)
 {
     cout << *i << endl;
 }
#endif
#if 0
 boost::shared_ptr<int> i1(new int(10));
 boost::shared_ptr<int> i2(i1);
    cout << "*i1 : " << *i1 << endl;
    cout << "*i2 : " << *i2 << endl;
    i1.reset(new int(2));
    cout << "*i1 : " << *i1 << endl;


class Book
{
private :
    string m_Name;
public:
    Book(string name):m_Name(name)
    {
        cout << "Book : " <<m_Name << endl;
    }
    ~Book()
    {
        cout << "~Book : " <<m_Name << endl;
    }

};
cout << "=======start===========" << endl;
{
boost::shared_ptr<Book> myBook(new Book("myBook1"));
cout << "myBook count : " << myBook.use_count() << endl;
boost::shared_ptr<Book> myBook1(myBook);
cout << "myBook count : " << myBook.use_count() << endl;
cout << "myBook1 count : " << myBook1.use_count() << endl;
myBook.reset();
cout << "----------------" << endl;
cout << "myBook count : " << myBook.use_count() << endl;
cout << "myBook1 count : " << myBook1.use_count() << endl;
myBook1.reset(new Book("mybook2"));
cout << "----------------" << endl;

cout << "myBook count : " << myBook.use_count() << endl;
cout << "myBook1 count : " << myBook1.use_count() << endl;
myBook1.reset();
cout << "----------------" << endl;

cout << "myBook count : " << myBook.use_count() << endl;
cout << "myBook1 count : " << myBook1.use_count() << endl;

}
cout << "=======end===========" << endl;
#endif
//boost::shared_ptr<int> p1 = new int(1024);// error: conversion from 'int*' to non-scalar type
boost::scoped_ptr<int> p1;
p1.reset(new int(1024));
*p1 = 20;
cout << *p1 << endl;

}
int main()
{
    system("chcp 65001");// 设置编码输出为中文
    //    test();
//    test1();
    test2();
    return 0;
}
