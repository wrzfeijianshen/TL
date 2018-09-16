TEMPLATE = subdirs
DEFINES += BOOST_THREAD_USE_LIB

DEPENDPATH+=$$PWD/../boost_1_68_0
INCLUDEPATH+= $$PWD/../boost_1_68_0/include/boost-1_68/
LIBS += -L$$PWD/../boost_1_68_0/lib

SUBDIRS += \
    01_time \
    02_ptr
