TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QT +=core opengl
SOURCES += \
    main.cpp

LIBS+=-lopengl32 -lglu32

win32: LIBS += -L$$PWD/../../../glut/ -lglut32

INCLUDEPATH += $$PWD/../../../glut
DEPENDPATH += $$PWD/../../../glut
