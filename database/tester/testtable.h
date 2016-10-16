#ifndef TESTTABLE_H
#define TESTTABLE_H

#include "databasehandler/database.h"
#include "databasehandler/fixedsizetable.h"
#include <QTime>
class testtable
{
public:
    testtable();
    string RandomString();
    string InttoString(int num);
    void begintest();
};

#endif // TESTTABLE_H
