TEMPLATE = app
#CONFIG += console
CONFIG +=  c++11
CONFIG -= app_bundle
CONFIG -= qt

QT += core opengl
LIBS += -lopengl32 \
     -lglu32

SOURCES += \
        main.cpp

win32: LIBS += -L$$PWD/../glut/ -lglut32

INCLUDEPATH += $$PWD/../glut
DEPENDPATH += $$PWD/../glut
