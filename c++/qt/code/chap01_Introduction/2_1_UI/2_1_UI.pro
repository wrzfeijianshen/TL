#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T11:10:32
#
#-------------------------------------------------
# 表示 加入core和gui模块,用于qt gui 设计类库模块
# 如果是控制台不需要添加 core gui
# 如果需要其他模块则添加,如 QT ++ sql
QT       += core gui

# qt > 4 ,qt主版本大于4时,才加入widgets模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# TARGET 是生成的目标可执行文件的名称,即编译后生成的2_1_UI.exe
TARGET = 2_1_UI
# 表示项目使用的模板是app,一般是应用程序
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
# 源文件
SOURCES += \
        main.cpp \
        Widget.cpp
# 头文件
HEADERS += \
        Widget.h
# 界面文件
FORMS += \
        Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
