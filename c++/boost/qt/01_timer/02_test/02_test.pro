TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH+=$$PWD/PWD/../../../boost_1_68_0

INCLUDEPATH+= $$PWD/../../boost_1_68_0/include/boost-1_68/
LIBS += -L$$PWD/../../boost_1_68_0/lib -lboost_system-mgw53-mt-d-x32-1_68 -lboost_filesystem-mgw53-mt-d-x32-1_68

SOURCES += \
        main.cpp
