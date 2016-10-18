#ifndef TESTITERATOR_H
#define TESTITERATOR_H

#include "databasehandler/database.h"
#include "databasehandler/fixedsizetable.h"
#include <QTime>
#include "recordhandler/recordfactory.h"
#include "managementhandler/iteratorfactory.h"
class testiterator
{
public:
    testiterator();
    string RandomString();
    string InttoString(int num);
    void begintest();
};

#endif // TESTITERATOR_H
