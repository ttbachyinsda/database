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
        mainwindow.cpp \
    databasehandler/database.cpp \
    databasehandler/table.cpp \
    typehandler/databaseint.cpp \
    typehandler/databasechar.cpp \
    tester/testtype.cpp \
    databasehandler/fixedsizetable.cpp \
    managementhandler/uic.cpp \
    tester/testtable.cpp \
    tester/testdatabase.cpp \
    typehandler/databasetype.cpp \
    layer/databasemanager.cpp \
    recordhandler/fixedsizerecord.cpp \
    recordhandler/record.cpp \
    managementhandler/iterator.cpp \
    managementhandler/fixedsizediterator.cpp \
    tester/testiterator.cpp \
    recordhandler/recordfactory.cpp \
    managementhandler/iteratorfactory.cpp \
    tester/testsql.cpp \
    sqlengine/sqlparser.cpp \
    sqlengine/sqllexer.cpp \
    sqlengine/sqldriver.cpp \
    sqlengine/sqlaction.cpp \
    sqlengine/sqlstruct.cpp

HEADERS  += mainwindow.h \
    pagefilesystem/BufPageManager.h \
    pagefilesystem/FileManager.h \
    pagefilesystem/pagedef.h \
    databasehandler/database.h \
    databasehandler/table.h \
    typehandler/databaseint.h \
    typehandler/databasechar.h \
    tester/testtype.h \
    databasehandler/fixedsizetable.h \
    pagefilesystem/MyLinkList.h \
    pagefilesystem/MyHashMap.h \
    pagefilesystem/MyBitMap.h \
    pagefilesystem/FindReplace.h \
    pagefilesystem/FileTable.h \
    managementhandler/uic.h \
    tester/testtable.h \
    tester/testdatabase.h \
    typehandler/databasetype.h \
    layer/databasemanager.h \
    recordhandler/fixedsizerecord.h \
    recordhandler/record.h \
    managementhandler/iterator.h \
    managementhandler/fixedsizediterator.h \
    tester/testiterator.h \
    recordhandler/recordfactory.h \
    managementhandler/iteratorfactory.h \
    tester/testsql.h \
    sqlengine/stack.hh \
    sqlengine/sqlparser.hpp \
    sqlengine/sqllexer.h \
    sqlengine/sqldriver.h \
    sqlengine/position.hh \
    sqlengine/location.hh \
    sqlengine/sqlaction.h \
    sqlengine/sqlstruct.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md
