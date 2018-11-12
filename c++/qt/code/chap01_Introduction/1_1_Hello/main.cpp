#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
#include <QDebug>
// qt 5.7增加了3d,qt quick controls. qt charts
#if 0
//  MinGW : Minimalist GNU for Windows,是windows平台上使用的gun工具集导入库的集合
// UWP模块: win10中的Universal Windows Platform的简称
// qt charts是二维图表模块,用于绘制柱状图,饼图,曲线图等常用二维图表
// qt data Visualization 是三维数据图表模块,用于数据的三维显示.
// qt Scritp是脚本模块.
// tools:
// -->1.qt creator 4.3.1用于qt程序开发的ide
// -->2.mingw5.3.0 是mingw编译工具链
// -->3.Strawberry Perl是一个Perl语言工具

// qt creator创建多个项目:
// -->1.qt widgets Application,支持桌面平台的有图形用户界面的应用程序.gui设计基于c++语言,采用qt提供的一套c++类库
// -->2.Qt Console Application, 控制台应用程序,无gui界面
// -->3.Qt Quick Application,界面基于qml语言
// -->4.Qt Canvas 3D Application,创建qt Canvas 3d qml项目.支持3d画布

// forms是项目内所有界面文件.ui

#endif
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
