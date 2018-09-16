TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += core opengl gui

LIBS += -lopengl32 \
     -lglu32

SOURCES += \
        main.cpp

win32: LIBS += -L$$PWD/../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/lib/ -lfreeglut

INCLUDEPATH += $$PWD/../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/include
DEPENDPATH += $$PWD/../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/include
LIBS += -L$$PWD/../Third_Party/freeglut_MinGW_3.0.0_1/freeglut/bin/ -lfreeglut
