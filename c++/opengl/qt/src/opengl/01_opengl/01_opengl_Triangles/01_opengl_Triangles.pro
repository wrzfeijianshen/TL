TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += core opengl

SOURCES += \
        main.cpp

#win32: LIBS += -L$$PWD/../../glut/ -lglut32

#INCLUDEPATH += $$PWD/../../glut
#DEPENDPATH += $$PWD/../../glut
win32: LIBS += -L$$PWD/../../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/lib -lfreeglut
DEPENDPATH += $$PWD/../../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/bin

INCLUDEPATH += $$PWD/../../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/include

INCLUDEPATH += $$PWD/../../src/examples/include
INCLUDEPATH += $$PWD/../../src/examples/lib/glfw/include
