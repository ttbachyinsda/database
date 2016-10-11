#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T16:22:57
#
#-------------------------------------------------

QT       += core gui
QT += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    pagefilesystem/BufPageManager.h \
    pagefilesystem/FileManager.h \
    pagefilesystem/pagedef.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md
