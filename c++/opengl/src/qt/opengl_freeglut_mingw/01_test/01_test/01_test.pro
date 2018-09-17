TEMPLATE = app
#CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lopengl32 \
-lglu32

# MinGW可以注释掉下面一行，但为了保持统一就不删除了
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads

SOURCES += \
        main.cpp

win32: LIBS += -L$$PWD/../../Third_Party_Package/freeglut/lib/ -lfreeglut

INCLUDEPATH += $$PWD/../../Third_Party_Package/freeglut/include
DEPENDPATH += $$PWD/../../Third_Party_Package/freeglut/include

LIBS += -L$$PWD/../../Third_Party_Package/freeglut/bin/ -lfreeglut
