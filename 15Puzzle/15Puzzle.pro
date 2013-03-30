#-------------------------------------------------
#
# Project created by QtCreator 2013-03-30T15:05:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = 15Puzzle
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    board.cpp \
    solver.cpp

HEADERS += \
    board.h \
    solver.h
