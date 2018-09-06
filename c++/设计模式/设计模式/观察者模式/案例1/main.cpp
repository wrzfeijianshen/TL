#include <iostream>
#include <string>
#include <list>

using namespace std;

// 抽象的观察者(监听者) -->学生
class  Listenner
{
public:
	// 老师来了，我该怎么办
	virtual void onTeacherComming() = 0;
	// 干坏事
	virtual void doBadthing() = 0;

};

// 抽象的被观察者，(通知者，拥有观察者，目标)
class Notifier
{
public:
	// 添加观察者的方法
	virtual void addListenner(Listenner *listenner) = 0;
	// 删除观察者的方法
	virtual void delListenner(Listenner *listenner) = 0;
	// 通知观察者的方法
	virtual void notify() = 0;
};

// 具体的观察者
class Student : public Listenner
{
public:
	Student(string name, string badthing)
	{
		this->name = name;
		this->badthing = badthing;
	}

	// 老师来了，
	virtual void onTeacherComming()
	{
		cout << "学生 " << name << "发现班长来信了 停止" << badthing << " 改为写作业" << endl;
	}
	virtual void doBadthing()
	{
		cout << "学生 " << name << " 正在" << badthing << endl;
	}
private:
	string name;
	string badthing;
};

// 具体的通知者(班长)
class Monitor : public Notifier
{
public:
	// 添加观察者的方法
	virtual void addListenner(Listenner *listenner)
	{
		this->l_list.push_back(listenner);
	}
	// 删除观察者的方法
	virtual void delListenner(Listenner *listenner)
	{

		this->l_list.remove(listenner);

	}
	// 通知观察者的方法,广播信息，让每个学生都各自重写自己的onTeacherComming
	virtual void notify()
	{
		for (list<Listenner*>::iterator it = l_list.begin(); it !=  l_list.end(); it++)
		{
			(*it)->onTeacherComming();
		}
	}
private:
	list<Listenner*> l_list;
};


int main()
{
	Listenner * s1 = new Student("张三", "唱歌");
	Listenner * s2 = new Student("李四", "打扑克");
	Listenner * s3 = new Student("王五", "划拳");

	Notifier * bossHLD = new Monitor(); // boss 黑老大

	// 将所有学生列表告知通知者，好让通知者进行通知
	bossHLD->addListenner(s1);
	bossHLD->addListenner(s2);
	bossHLD->addListenner(s3);

	cout << "教室乱哄哄，老师没有来" << endl;
	s1->doBadthing();
	s2->doBadthing();
	s3->doBadthing();
	cout  << endl;

	cout << "班长发现老师来了，通知大家" << endl;
	bossHLD->notify();
	getchar();
	return 0;
}