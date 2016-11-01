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
#include "databasehandler/table.h"
#include "queryhandler/querycondition.h"
#include "recordhandler/recordfactory.h"
#include "managementhandler/iteratorfactory.h"

class QueryExecuter
{
    SQLDriver* driver;
    std::vector<Table*> tables;
    std::vector<Record*> records;

    // Save the current state
    std::vector<Iterator*> iterators;

    std::vector<SelectorPair> selectors;
    std::vector<QueryCondition> conditions;

    char** tempLinkedRowData;

    void clearUp();
    bool getTableColumnIndex(int& tid, int& cid, SQLSelector* s, std::map<std::string, int>& dict,
                             std::map<std::string, int>::iterator& dictIter);
    bool typeComparable(char a, char b);

    // Recursion Entrance:
    void traverseTable(int tid, SQLResult* result);
    // Recursion Finish:
    void addToResultIfMatch(SQLResult* result);

public:
    bool setQuery(SQLTableGroup* tgrp, SQLSelectorGroup* sgrp, SQLConditionGroup* cgrp);
    bool executeQuery();

    QueryExecuter(SQLDriver* d);
    ~QueryExecuter();
};

#endif // QUERYEXECUTER_H
