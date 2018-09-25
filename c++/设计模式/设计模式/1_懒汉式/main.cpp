#include <iostream>
using namespace std;

//饿汉式
class Chairman_lazy
{
private:
	Chairman_lazy(){}
public:
	// 栈区
	static Chairman_lazy* GetInstance()
	{
		static Chairman_lazy s_singleton;
		return &s_singleton;
	}
};

class Chairman_lazy1
{
private:
	Chairman_lazy1(){}
public:
	static Chairman_lazy1* GetInstance()
	{
		return s_singleton;
	}
private:
	static Chairman_lazy1* s_singleton;
};

//初始化
Chairman_lazy1* Chairman_lazy1::s_singleton = new Chairman_lazy1;

//懒汉式
class Chairman_lazy2
{
private:
	Chairman_lazy2(){}
public:
	// 堆区
	static Chairman_lazy2* GetInstance()
	{
		if (s_singleton == NULL)
		{
			s_singleton = new Chairman_lazy2;
		}
		return s_singleton;
	}
private:
	static Chairman_lazy2 * s_singleton;
};

Chairman_lazy2* Chairman_lazy2::s_singleton = NULL;

void test1()
{
	Chairman_lazy* lazy1 = Chairman_lazy::GetInstance();
	Chairman_lazy* lazy2 = Chairman_lazy::GetInstance();

	cout << "lazy1 : " << (int*)lazy1 << endl;
	cout << "lazy2 : " << (int*)lazy2 << endl;
	if (lazy1 == lazy2)
	{
		cout << "指向同一个对象!" << endl;
	}
	else
	{
		cout << "指向不是同一个对象!" << endl;
	}
}

void test2()
{
	Chairman_lazy2* lazy1 = Chairman_lazy2::GetInstance();
	Chairman_lazy2* lazy2 = Chairman_lazy2::GetInstance();
	cout << "lazy1 : " << (int*)lazy1 << endl;
	cout << "lazy2 : " << (int*)lazy2 << endl;
	if (lazy1 == lazy2)
	{
		cout << "指向同一个对象!" << endl;
	}
	else
	{
		cout << "指向不是同一个对象!" << endl;
	}
}

void test3()
{
	Chairman_lazy1* lazy1 = Chairman_lazy1::GetInstance();
	Chairman_lazy1* lazy2 = Chairman_lazy1::GetInstance();
	cout << "lazy1 : " << (int*)lazy1 << endl;
	cout << "lazy2 : " << (int*)lazy2 << endl;
	if (lazy1 == lazy2)
	{
		cout << "指向同一个对象!" << endl;
	}
	else
	{
		cout << "指向不是同一个对象!" << endl;
	}
}

int main()
{
	//test1();
	//test2();
	test3();

	getchar();
	return 0;
}