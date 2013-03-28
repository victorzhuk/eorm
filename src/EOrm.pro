VERSION = 0.9.1

QT       += sql

QT       -= gui

TARGET = eorm

TEMPLATE = lib

DEFINES += EORM_LIBRARY

SOURCES += \
    eormactiverecord.cpp \
    eormfind.cpp \
    eormmodel.cpp \
    eorm.cpp \
    eormexception.cpp

HEADERS += \
    eormactiverecord.h \
    eormfind.h \
    eormmodel.h \
    eorm.h \
    eormexception.h
