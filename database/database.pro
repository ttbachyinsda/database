#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T16:22:57
#
#-------------------------------------------------

QT       += core gui
QT += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = database
TEMPLATE = app
QMAKE_CXXFLAGS += -Wall -Wextra -Wno-unused
LIBS += -lgmpxx -lgmp -lmpfr


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
    databasehandler/virtualtable.cpp \
    managementhandler/virtualiterator.cpp \
    tester/testvirtual.cpp \
    groupalgorithm/group.cpp \
    tester/testgroup.cpp \
    groupalgorithm/rawgroup.cpp \
    tester/testregex.cpp \
    managementhandler/md5.cpp \
    tester/testmd5.cpp \
    databasehandler/hashflexibletable.cpp \
    tester/testhashflexible.cpp \
    managementhandler/hashflexibleiterator.cpp \
    queryhandler/joinstrategies/hashjoin.cpp \
    queryhandler/joinstrategies/joinstrategy.cpp \
    queryhandler/joinstrategies/nestedloopjoin.cpp \
    queryhandler/joinstrategies/sortmergejoin.cpp \
    queryhandler/intelligentfilter.cpp \
    queryhandler/queryoptimizer.cpp \
    groupalgorithm/grouphandler.cpp \
    databasehandler/bulbfile.cpp \
    tester/testbulbfile.cpp \
    typehandler/databasebulb.cpp \
    typehandler/databasetext.cpp \
    DBIndex/comparealgo.cpp \
    queryhandler/checkhelper.cpp \
    queryhandler/modifyhandler.cpp \
    tester/testaes.cpp \
    aesalgorithm/aes.cpp \
    aesalgorithm/encrypt.cpp \
    DBIndex/bplus_treel.cpp


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
    typehandler/chrono_io.h \
    tester/testdate.h \
    databasehandler/virtualtable.h \
    managementhandler/virtualiterator.h \
    tester/testvirtual.h \
    groupalgorithm/group.h \
    tester/testgroup.h \
    groupalgorithm/rawgroup.h \
    tester/testregex.h \
    managementhandler/md5.h \
    tester/testmd5.h \
    databasehandler/hashflexibletable.h \
    tester/testhashflexible.h \
    managementhandler/hashflexibleiterator.h \
    queryhandler/joinstrategies/hashjoin.h \
    queryhandler/joinstrategies/joinstrategy.h \
    queryhandler/joinstrategies/nestedloopjoin.h \
    queryhandler/joinstrategies/sortmergejoin.h \
    queryhandler/intelligentfilter.h \
    queryhandler/queryoptimizer.h \
    groupalgorithm/grouphandler.h \
    databasehandler/bulbfile.h \
    tester/testbulbfile.h \
    typehandler/databasebulb.h \
    typehandler/databasetext.h \
    DBIndex/comparealgo.h \
    queryhandler/checkhelper.h \
    queryhandler/modifyhandler.h \
    tester/testaes.h \
    aesalgorithm/aes.h \
    aesalgorithm/encrypt.h \
    DBIndex/bplus_treel.h


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
    bin/gmpformingw32.rar
RESOURCES += \
    thjdb.qrc \
    icons/icons.qrc

OBJECTIVE_SOURCES +=
