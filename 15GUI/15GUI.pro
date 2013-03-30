#-------------------------------------------------
#
# Project created by QtCreator 2013-03-27T23:16:23
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = 15GUI
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    Node3.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    Operators.h \
    Node3.h \
    graph.h \
    GUIMove.h

FORMS    += mainwindow.ui
