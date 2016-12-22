#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T16:07:43
#
#-------------------------------------------------

QT       -= core gui

TARGET = _thjdb
TEMPLATE = lib

QMAKE_CXXFLAGS += -fpic
LIBS += -lgmpxx -lgmp -L /usr/lib/python2.7

INCLUDEPATH += /usr/include/python2.7


SOURCES += \
    ../database/layer/databasemanager.cpp \
    ../database/layer/pythonif_wrap.cxx \
    ../database/databasehandler/database.cpp \
    ../database/databasehandler/fixedsizetable.cpp \
    ../database/databasehandler/flexibletable.cpp \
    ../database/databasehandler/table.cpp \
    ../database/databasehandler/virtualtable.cpp \
    ../database/DBIndex/bplus_tree.cpp \
    ../database/DBIndex/db_index.cpp \
    ../database/groupalgorithm/group.cpp \
    ../database/groupalgorithm/rawgroup.cpp \
    ../database/managementhandler/fixedsizediterator.cpp \
    ../database/managementhandler/flexibleiterator.cpp \
    ../database/managementhandler/iterator.cpp \
    ../database/managementhandler/iteratorfactory.cpp \
    ../database/managementhandler/uic.cpp \
    ../database/managementhandler/virtualiterator.cpp \
    ../database/queryhandler/querycondition.cpp \
    ../database/queryhandler/queryexecuter.cpp \
    ../database/recordhandler/fixedsizerecord.cpp \
    ../database/recordhandler/flexiblerecord.cpp \
    ../database/recordhandler/record.cpp \
    ../database/recordhandler/recordfactory.cpp \
    ../database/sqlengine/sqlaction.cpp \
    ../database/sqlengine/sqldriver.cpp \
    ../database/sqlengine/sqllexer.cpp \
    ../database/sqlengine/sqlparser.cpp \
    ../database/sqlengine/sqlstruct.cpp \
    ../database/typehandler/databasechar.cpp \
    ../database/typehandler/databasedate.cpp \
    ../database/typehandler/databaseint.cpp \
    ../database/typehandler/databaselint.cpp \
    ../database/typehandler/databasereal.cpp \
    ../database/typehandler/databasetype.cpp \
    ../database/typehandler/databasevarchar.cpp \
    ../database/typehandler/databasebulb.cpp \
    ../database/typehandler/databasetext.cpp \
    ../database/managementhandler/hashflexibleiterator.cpp \
    ../database/managementhandler/md5.cpp \
    ../database/databasehandler/bulbfile.cpp \
    ../database/databasehandler/hashflexibletable.cpp \
    ../database/DBIndex/comparealgo.cpp \
    ../database/tester/testflexible.cpp

HEADERS += \
    ../database/tester/testflexible.h \
    ../database/layer/databasemanager.h \
    ../database/layer/json.hpp \
    ../database/layer/pythonif.h \
    ../database/layer/pythonif.i \
    ../database/databasehandler/database.h \
    ../database/databasehandler/fixedsizetable.h \
    ../database/databasehandler/flexibletable.h \
    ../database/databasehandler/table.h \
    ../database/databasehandler/virtualtable.h \
    ../database/DBIndex/bplus_node.h \
    ../database/DBIndex/bplus_tree.h \
    ../database/DBIndex/db_index.h \
    ../database/DBIndex/predefined.h \
    ../database/groupalgorithm/group.h \
    ../database/groupalgorithm/rawgroup.h \
    ../database/managementhandler/fixedsizediterator.h \
    ../database/managementhandler/flexibleiterator.h \
    ../database/managementhandler/iterator.h \
    ../database/managementhandler/iteratorfactory.h \
    ../database/managementhandler/uic.h \
    ../database/managementhandler/virtualiterator.h \
    ../database/pagefilesystem/BufPageManager.h \
    ../database/pagefilesystem/FileManager.h \
    ../database/pagefilesystem/FileTable.h \
    ../database/pagefilesystem/FindReplace.h \
    ../database/pagefilesystem/MyBitMap.h \
    ../database/pagefilesystem/MyHashMap.h \
    ../database/pagefilesystem/MyLinkList.h \
    ../database/pagefilesystem/pagedef.h \
    ../database/queryhandler/querycondition.h \
    ../database/queryhandler/queryexecuter.h \
    ../database/recordhandler/fixedsizerecord.h \
    ../database/recordhandler/flexiblerecord.h \
    ../database/recordhandler/record.h \
    ../database/recordhandler/recordfactory.h \
    ../database/sqlengine/location.hh \
    ../database/sqlengine/position.hh \
    ../database/sqlengine/sqlaction.h \
    ../database/sqlengine/sqldriver.h \
    ../database/sqlengine/sqllexer.h \
    ../database/sqlengine/sqlparser.hpp \
    ../database/sqlengine/sqlstruct.h \
    ../database/sqlengine/stack.hh \
    ../database/typehandler/chrono_io.h \
    ../database/typehandler/databasechar.h \
    ../database/typehandler/databasedate.h \
    ../database/typehandler/databaseint.h \
    ../database/typehandler/databaselint.h \
    ../database/typehandler/databasereal.h \
    ../database/typehandler/databasetype.h \
    ../database/typehandler/databasevarchar.h \
    ../database/typehandler/date.h \
    ../database/typehandler/databasebulb.h \
    ../database/typehandler/databasetext.h \
    ../database/managementhandler/hashflexibleiterator.h \
    ../database/managementhandler/md5.h \
    ../database/databasehandler/bulbfile.h \
    ../database/databasehandler/hashflexibletable.h \
    ../database/DBIndex/comparealgo.h

unix{
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
