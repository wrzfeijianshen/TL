#include <iostream>
#include <boost/smart_ptr.hpp>

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

int main()
{
    system("chcp 65001");// 设置编码输出为中文
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
    return 0;
}
