TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    indexer.cpp \
    searcher.cpp \
    clustererx.cpp

INCLUDEPATH += /home/jaydeep/Documents/xapian/xapian-core/install/include/xapian-1.1/

LIBS += -L/home/jaydeep/Documents/xapian/xapian-core/install/lib -lxapian-1.1

HEADERS += \
    indexer.h \
    searcher.h \
    clustererx.h
