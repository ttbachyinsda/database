#ifndef TESTHASHFLEXIBLE_H
#define TESTHASHFLEXIBLE_H

#include "../databasehandler/database.h"
#include "../databasehandler/fixedsizetable.h"
#include "../databasehandler/flexibletable.h"
#include "../databasehandler/hashflexibletable.h"
#include "../groupalgorithm/group.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include <QTime>
class testhashflexible {
public:
    testhashflexible();
    string RandomString();
    string InttoString(int num);
    string signedlongtostring(long long num);
    string doubletostring(double num);
    void testindex(Table* onetable, string input);
    void begintest();
};

#endif // TESTHASHFLEXIBLE_H
