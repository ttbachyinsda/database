#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include "../layer/databasemanager.h"

class testdatabase {
public:
    testdatabase();
    void begintest();
    void trytoInitializeTable(Table* temp);
};

#endif // TESTDATABASE_H
