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
win32: LIBS += -L$$PWD/../../freeglut/lib -lfreeglut
DEPENDPATH += $$PWD/../../freeglut/bin

INCLUDEPATH += $$PWD/../../freeglut/include
INCLUDEPATH += $$PWD/../../examples/include
INCLUDEPATH += $$PWD/../../examples/lib/glfw/include
