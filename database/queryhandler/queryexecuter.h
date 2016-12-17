#ifndef QUERYEXECUTER_H
#define QUERYEXECUTER_H

//class SQLTableGroup;
class SQLSelectorGroup;
//class SQLConditionGroup;
class SQLDriver;
class SQLSelector;
class SQLResult;

#include <vector>
#include <map>
#include "../databasehandler/table.h"
#include "../queryhandler/querycondition.h"
#include "../recordhandler/recordfactory.h"
#include "../managementhandler/iteratorfactory.h"

class QueryExecuter
{
    SQLDriver* driver;
    std::vector<Table*> tables;

    std::vector<SelectorPair> selectors;

    std::vector<ConditionPair> conditions;

    void clearUp();
    bool getTableColumnIndex(int& tid, int& cid, SQLSelector* s, std::map<std::string, int>& dict,
                             std::map<std::string, int>::iterator& dictIter);
    inline int indexMap(int i, int splitPoint) {
        if (i == splitPoint) return -1;
        return (i < splitPoint) ? i : i - 1;
    }

public:
    bool setQuery(SQLTableGroup* tgrp, SQLSelectorGroup* sgrp, SQLConditionGroup* cgrp);
    bool executeQuery();

    QueryExecuter(SQLDriver* d);
    ~QueryExecuter();
};

#endif // QUERYEXECUTER_H
