TEMPLATE = app
#CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
#备用
#QT +=core opengl
#LIBS += -lopengl32 \
#-lglu32

#win32: LIBS += -L$$PWD/../../Third_Party_Package/GL/ -lglut32

#INCLUDEPATH += $$PWD/../../Third_Party_Package/GL
#DEPENDPATH += $$PWD/../../Third_Party_Package/GL
