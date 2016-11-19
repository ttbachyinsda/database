rm -rf *.o
swig -c++ -python ../database/layer/pythonif.i
cp ../database/layer/thjdb.py thjdb.py
c++ -fpic -c --std=c++11 ../database/layer/pythonif_wrap.cxx -I/usr/include/python2.7
c++ -fpic -c --std=c++11 ../database/databasehandler/database.cpp
c++ -fpic -c --std=c++11 ../database/databasehandler/fixedsizetable.cpp
c++ -fpic -c --std=c++11 ../database/databasehandler/flexibletable.cpp
c++ -fpic -c --std=c++11 ../database/databasehandler/table.cpp
c++ -fpic -c --std=c++11 ../database/DBIndex/bplus_tree.cpp
c++ -fpic -c --std=c++11 ../database/DBIndex/db_index.cpp
c++ -fpic -c --std=c++11 ../database/layer/databasemanager.cpp
c++ -fpic -c --std=c++11 ../database/managementhandler/fixedsizediterator.cpp
c++ -fpic -c --std=c++11 ../database/managementhandler/flexibleiterator.cpp
c++ -fpic -c --std=c++11 ../database/managementhandler/iterator.cpp
c++ -fpic -c --std=c++11 ../database/managementhandler/iteratorfactory.cpp
c++ -fpic -c --std=c++11 ../database/managementhandler/uic.cpp

c++ -fpic -c --std=c++11 ../database/queryhandler/querycondition.cpp
c++ -fpic -c --std=c++11 ../database/queryhandler/queryexecuter.cpp

c++ -fpic -c --std=c++11 ../database/recordhandler/fixedsizerecord.cpp
c++ -fpic -c --std=c++11 ../database/recordhandler/flexiblerecord.cpp
c++ -fpic -c --std=c++11 ../database/recordhandler/record.cpp
c++ -fpic -c --std=c++11 ../database/recordhandler/recordfactory.cpp

c++ -fpic -c --std=c++11 ../database/sqlengine/sqlaction.cpp
c++ -fpic -c --std=c++11 ../database/sqlengine/sqldriver.cpp
c++ -fpic -c --std=c++11 ../database/sqlengine/sqllexer.cpp
c++ -fpic -c --std=c++11 ../database/sqlengine/sqlparser.cpp
c++ -fpic -c --std=c++11 ../database/sqlengine/sqlstruct.cpp

c++ -fpic -c --std=c++11 ../database/tester/testdatabase.cpp
c++ -fpic -c --std=c++11 ../database/tester/testflexible.cpp
c++ -fpic -c --std=c++11 ../database/tester/testiterator.cpp

c++ -fpic -c --std=c++11 ../database/tester/testtype.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databasechar.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databaseint.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databasetype.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databasevarchar.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databaselint.cpp
c++ -fpic -c --std=c++11 ../database/typehandler/databasereal.cpp

c++ -shared *.o -o _thjdb.so
