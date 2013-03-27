#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T08:31:49
#
#-------------------------------------------------

QT       += core

QT       -= gui
QMAKE_CXXFLAGS += -std=c++0x
TARGET = SISE3
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    graph.cpp \
    Node3.cpp

HEADERS += \
    graph.h \
    Operators.h \
    Node3.h
