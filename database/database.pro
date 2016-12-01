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

LIBS += -lcurl
QMAKE_CXXFLAGS += --std=c++14

DEFINES += QPM_INIT\\(E\\)=\"E.addImportPath(QStringLiteral(\\\"qrc:/\\\"));\"

include(../material/material.pri)
SOURCES += main.cpp\
        mainwindow.cpp \
    databasehandler/database.cpp \
    databasehandler/table.cpp \
    typehandler/databaseint.cpp \
    typehandler/databasechar.cpp \
    tester/testtype.cpp \
    databasehandler/fixedsizetable.cpp \
    managementhandler/uic.cpp \
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
    sqlengine/sqlstruct.cpp \
    queryhandler/querycondition.cpp \
    queryhandler/queryexecuter.cpp \
    databasehandler/flexibletable.cpp \
    recordhandler/flexiblerecord.cpp \
    managementhandler/flexibleiterator.cpp \
    tester/testflexible.cpp \
    typehandler/databasevarchar.cpp \
    DBIndex/bplus_tree.cpp \
    DBIndex/db_index.cpp \
    layer/qmlif.cpp \
    typehandler/databasereal.cpp \
    typehandler/databaselint.cpp \
    typehandler/databasedate.cpp \
    tester/testdate.cpp \
    typehandler/tz.cpp \


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
    sqlengine/sqlstruct.h \
    queryhandler/querycondition.h \
    queryhandler/queryexecuter.h \
    databasehandler/flexibletable.h \
    recordhandler/flexiblerecord.h \
    managementhandler/flexibleiterator.h \
    tester/testflexible.h \
    typehandler/databasevarchar.h \
    DBIndex/bplus_node.h \
    DBIndex/bplus_tree.h \
    DBIndex/db_index.h \
    DBIndex/predefined.h \
    sqlengine/sqllexer.l \
    sqlengine/sqlparser.yy \
    typehandler/databasereal.h \
    typehandler/databaselint.h \
    layer/json.hpp \
    layer/pythonif.h \
    layer/qmlif.h \
    typehandler/date.h \
    typehandler/databasedate.h \
    typehandler/tz.h \
    typehandler/chrono_io.h \
    tester/testdate.h \
    typehandler/tz_private.h \
    typehandler/ios.h \

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.md \
    layer/pythonif_wrap.cxx \
    layer/pythonif.i \
    bin/data/m4sugar/foreach.m4 \
    bin/data/m4sugar/m4sugar.m4 \
    bin/data/bison.m4 \
    bin/data/c++-skel.m4 \
    bin/data/c++.m4 \
    bin/data/c-like.m4 \
    bin/data/c-skel.m4 \
    bin/data/c.m4 \
    bin/data/java-skel.m4 \
    bin/data/java.m4 \
    bin/win_bison.exe \
    bin/win_flex.exe \
    bin/custom_build_rules/win_bison_only/win_bison_custom_build.xml \
    bin/custom_build_rules/win_flex_only/win_flex_custom_build.xml \
    bin/custom_build_rules/win_flex_bison_custom_build.xml \
    bin/data/xslt/bison.xsl \
    bin/data/xslt/xml2dot.xsl \
    bin/data/xslt/xml2text.xsl \
    bin/data/xslt/xml2xhtml.xsl \
    bin/custom_build_rules/win_bison_only/win_bison_custom_build.props \
    bin/custom_build_rules/win_bison_only/win_bison_custom_build.targets \
    bin/custom_build_rules/win_flex_only/win_flex_custom_build.props \
    bin/custom_build_rules/win_flex_only/win_flex_custom_build.targets \
    bin/custom_build_rules/how_to_use.txt \
    bin/custom_build_rules/win_flex_bison_custom_build.props \
    bin/custom_build_rules/win_flex_bison_custom_build.targets \
    sqlengine/sqlparser.output \
    bin/data/lalr1.java \
    bin/data/local.mk \
    bin/data/README \
    bin/win_bison \
    bin/win_flex \
    tzdata/checklinks.awk \
    tzdata/checktab.awk \
    tzdata/leapseconds.awk \
    tzdata/zoneinfo2tdf.pl \
    tzdata/yearistype.sh \
    tzdata/africa \
    tzdata/antarctica \
    tzdata/asia \
    tzdata/australasia \
    tzdata/backward \
    tzdata/backzone \
    tzdata/CONTRIBUTING \
    tzdata/etcetera \
    tzdata/europe \
    tzdata/factory \
    tzdata/iso3166.tab \
    tzdata/leap-seconds.list \
    tzdata/leapseconds \
    tzdata/LICENSE \
    tzdata/NEWS \
    tzdata/northamerica \
    tzdata/pacificnew \
    tzdata/southamerica \
    tzdata/systemv \
    tzdata/Theory \
    tzdata/version \
    tzdata/zone.tab \
    tzdata/zone1970.tab \
    tzdata/README
RESOURCES += \
    thjdb.qrc \
    icons/icons.qrc

OBJECTIVE_SOURCES +=
