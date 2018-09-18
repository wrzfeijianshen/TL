TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
# MinGW可以注释掉下面一行，但为了保持统一就不删除了
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads

#QT += opengl
win32:QMAKE_LFLAGS += -shared

LIBS += -lopengl32 \
        -lglu32

SOURCES += \
        main.cpp \
    glad.c

INCLUDEPATH += $$PWD/../../Third_Party_Package/



win32: LIBS += -L$$PWD/../../Third_Party_Package/glfw_3.2.1/lib-vc2015/ -lglfw3

INCLUDEPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1/include
DEPENDPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1/lib-mingw-w64
