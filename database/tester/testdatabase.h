#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include "../databasehandler/database.h"

class testdatabase {
public:
    testdatabase();
    void begintest();
    void trytoInitializeTable(Table* temp);
};

#endif // TESTDATABASE_H
