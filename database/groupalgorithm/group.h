#ifndef GROUP_H
#define GROUP_H

#include <map>
#include <iostream>
#include "../databasehandler/table.h"
#include "../recordhandler/recordfactory.h"
#include "../managementhandler/iteratorfactory.h"
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class Group
{
public:
    Group();
    bool add(int x,int y);
    string getmax(Table* onetable,int columnnum);
    string getmin(Table* onetable,int columnnum);
    string getsum(Table* onetable,int columnnum);
    string getaverage(Table* onetable,int columnnum);
private:
    map<pair<int,int>,int> data;
};

#endif // GROUP_H
