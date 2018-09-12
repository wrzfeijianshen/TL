QT       += core gui
greaterThan(QT_MAJOR_VERSION,4) : QT += widgets
TARGET = 1_1Hello
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
#CONFIG +=console
FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

SOURCES += \
    mainwindow.cpp \
    main.cpp
