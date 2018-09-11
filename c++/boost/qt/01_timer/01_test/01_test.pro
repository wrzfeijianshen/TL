#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T00:25:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 01_test
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
DEFINES += BOOST_THREAD_USE_LIB

DEPENDPATH+=$$PWD/PWD/../../../boost_1_68_0

INCLUDEPATH+= $$PWD/../../boost_1_68_0/include/boost-1_68/
LIBS += -L$$PWD/../../boost_1_68_0/lib -lboost_system-mgw53-mt-d-x32-1_68 -lboost_filesystem-mgw53-mt-d-x32-1_68
SOURCES += \
        main.cpp


