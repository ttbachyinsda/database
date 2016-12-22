#ifndef RAWGROUP_H
#define RAWGROUP_H

#include "../databasehandler/table.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <map>
using namespace std;

class RawGroup {
public:
    RawGroup();
    void clear();
    void add(string input);
    string getmax();
    string getmin();
    string getsum();
    string getaverage();
    int getnum();

private:
    mpq_class maxn;
    mpq_class minn;
    mpq_class sumn;
    int num;
};

#endif // RAWGROUP_H
