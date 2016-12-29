#ifndef RAWGROUP_H
#define RAWGROUP_H

#include "../databasehandler/table.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include <gmp.h>
#include <gmpxx.h>
#include "mpreal.h"
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
using mpfr::mpreal;
#define MAX_DIGITS 5

class RawGroup {
public:
    RawGroup();
    void clear();
    void add(string input);
    string getmax();
    string getmin();
    string getsum();
    string getaverage();
    string getstr(mpreal num);
    int getnum();

private:
    mpreal maxn;
    mpreal minn;
    mpreal sumn;
    int num;
};

#endif // RAWGROUP_H
