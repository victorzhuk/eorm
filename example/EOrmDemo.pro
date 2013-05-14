QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EOrmDemo

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    test.h

FORMS    += mainwindow.ui

LIBS += -L../src/ -leorm

INCLUDEPATH += ../src
DEPENDPATH += ../src
