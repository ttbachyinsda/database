#ifndef DATABASETYPEOPERATOR_H
#define DATABASETYPEOPERATOR_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <gmpxx.h>
using namespace std;

class DatabaseTypeOperator
{
public:
    static bool gt(string arg1,string arg2,string nowtype);
    static bool gte(string arg1,string arg2,string nowtype);
    static bool lt(string arg1,string arg2,string nowtype);
    static bool lte(string arg1,string arg2,string nowtype);
    static string sum(string arg1,string arg2,string nowtype);
    static string ave(string arg1,string arg2,string nowtype);
};

#endif // DATABASETYPEOPERATOR_H
