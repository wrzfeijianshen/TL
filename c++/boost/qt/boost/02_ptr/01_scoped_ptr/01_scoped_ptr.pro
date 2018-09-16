TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DEPENDPATH+=$$PWD/../../../boost_1_68_0
INCLUDEPATH+= $$PWD/../../../boost_1_68_0/include/boost-1_68/
LIBS += -L$$PWD/../../../boost_1_68_0/lib
SOURCES += \
        main.cpp
