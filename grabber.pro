#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T22:47:16
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = grabber
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    xmlconfiguration.cpp \
    ytrequestmanager.cpp \
    ytexplorator.cpp \
    ytmovie.cpp \
    ytmovieslist.cpp \
    applicationcontroller.cpp \
    ytdownloader.cpp

OTHER_FILES += \
    config.xml

HEADERS += \
    xmlconfiguration.h \
    ytrequestmanager.h \
    ytexplorator.h \
    ytmovie.h \
    ytmovieslist.h \
    applicationcontroller.h \
    ytdownloader.h
