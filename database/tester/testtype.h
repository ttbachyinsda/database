#ifndef TESTTYPE_H
#define TESTTYPE_H
#include "typehandler/databasechar.h"
#include "typehandler/databaseint.h"
#include "typehandler/databasetype.h"
#include <QTime>
#include "managementhandler/uic.h"

class testtype {
public:
    testtype();
    void begintest(bool timetest);
    void begintestchar();
    void beginteststring();
    void beginjingxitest();
};

#endif // TESTTYPE_H
