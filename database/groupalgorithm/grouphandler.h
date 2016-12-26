//
// Created by jameshuang on 16-12-20.
//

#ifndef DATABASE_GROUPHANDLER_H
#define DATABASE_GROUPHANDLER_H


#include "../databasehandler/table.h"
#include "../sqlengine/sqldriver.h"
#include "rawgroup.h"

class GroupHandler {
    typedef std::map<std::string, int> strIntMap;
    typedef std::map<std::vector<int>, std::vector<RawGroup*> > rawGroupMap;

    struct GroupTarget {
        SQLGroupMethod method;
        int columnID;
    };

    Table* myTable;
    std::vector<GroupTarget> groupTargets;
    std::vector<int> referers;
    // > 1000: index in groupTargets, else index in refers.
    std::vector<int> displays;
    SQLDriver* driver;

    bool hasGroupClause;
    SQLResult* executeQueryWithGroup();
    SQLResult* executeQueryWithoutGroup();
    string convertTitle(const string& orig, SQLGroupMethod method);

public:
    bool prepareQuery(Table* table, SQLSelectorGroup *selectorGroup, SQLTableGroup *groupByGroup);
    SQLResult* executeQuery();
    GroupHandler(SQLDriver* d) { driver = d; hasGroupClause = false; }
    ~GroupHandler() {}
};


#endif //DATABASE_GROUPHANDLER_H
