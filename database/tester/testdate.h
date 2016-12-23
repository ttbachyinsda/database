#ifndef TESTDATE_H
#define TESTDATE_H

#include "../managementhandler/uic.h"
#include "../typehandler/chrono_io.h"
#include "../typehandler/databasedate.h"
#include "../typehandler/date.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace date;
using namespace std::chrono;
class testdate {
public:
    testdate();
    void beginpretest();
    void begintest();
};

#endif // TESTDATE_H
