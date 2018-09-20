TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
# MinGW可以注释掉下面一行，但为了保持统一就不删除了
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
QT +=core gui opengl

#win32:QMAKE_LFLAGS += -shared

#LIBS += -lopengl32 \
#        -lglu32
LIBS+=-lopengl32 -lglu32
SOURCES += \
        main.cpp \
    win32_window.c

INCLUDEPATH += $$PWD/../../Third_Party_Package/


win32: LIBS += -L$$PWD/../../Third_Party_Package/glfw_3.2.1/lib-mingw/ -lglfw3 -lglfw3dll

INCLUDEPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1/include
DEPENDPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1/lib-mingw
INCLUDEPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1_src/include
INCLUDEPATH += $$PWD/../../Third_Party_Package/glfw_3.2.1_src/src
