#ifndef RAWGROUP_H
#define RAWGROUP_H

#include <map>
#include <iostream>
#include "../databasehandler/table.h"
#include "../recordhandler/recordfactory.h"
#include "../managementhandler/iteratorfactory.h"
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class RawGroup
{
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
