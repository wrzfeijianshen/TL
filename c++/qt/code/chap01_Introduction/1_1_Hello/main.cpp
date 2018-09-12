#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
#include <QDebug>
int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    //system("chcp 65001");
    qDebug()<<"hello world!中文sss";
    printf("%s\n","中文歌n");
    cout << "中文aaaa";
    MainWindow w;
    w.show();

    return a.exec();
}
