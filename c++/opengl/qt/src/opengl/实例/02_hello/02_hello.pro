#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T17:34:40
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled5
TEMPLATE = app
LIBS += -lopengl32 \
    -lglu32 \
 #   -lglut \


SOURCES += main.cpp\
        widget.cpp \
    openglwidget.cpp

HEADERS  += widget.h \
    openglwidget.h

FORMS    += widget.ui
