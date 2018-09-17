TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
# MinGW可以注释掉下面一行，但为了保持统一就不删除了
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads

QT += opengl

LIBS += -lopengl32 \
-lglu32

SOURCES += \
        main.cpp \

