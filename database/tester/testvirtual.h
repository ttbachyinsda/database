#ifndef TESTVIRTUAL_H
#define TESTVIRTUAL_H

#include "../databasehandler/database.h"
#include "../databasehandler/fixedsizetable.h"
#include "../databasehandler/flexibletable.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include "../databasehandler/virtualtable.h"
#include <QTime>
class testvirtual
{
public:
    testvirtual();
    string RandomString();
    string InttoString(int num);
    void begintest();
    void testindex(Table *onetable, string input);
};

#endif // TESTVIRTUAL_H
