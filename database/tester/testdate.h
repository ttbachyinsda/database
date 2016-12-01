#ifndef TESTDATE_H
#define TESTDATE_H

#include "../typehandler/date.h"
#include "../typehandler/tz.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "../typehandler/chrono_io.h"
#include "../typehandler/databasedate.h"
#include "../managementhandler/uic.h"
using namespace date;
using namespace std::chrono;
class testdate
{
public:
    testdate();
    void beginpretest();
    void begintest();
};

#endif // TESTDATE_H
