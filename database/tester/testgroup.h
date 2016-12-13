#ifndef TESTGROUP_H
#define TESTGROUP_H

#include "../databasehandler/database.h"
#include "../databasehandler/fixedsizetable.h"
#include "../databasehandler/flexibletable.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include "../groupalgorithm/group.h"
#include <QTime>
class testgroup
{
public:
    testgroup();
    string RandomString();
    string InttoString(int num);
    string signedlongtostring(long long num);
    string doubletostring(double num);
    void begintest();
    void testindex(Table *onetable, string input);
};

#endif // TESTGROUP_H
