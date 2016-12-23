//
// Created by jameshuang on 16-12-23.
//

#ifndef DATABASE_MODIFYHANDLER_H
#define DATABASE_MODIFYHANDLER_H


#include "../sqlengine/sqldriver.h"

class ModifyHandler {
    struct SetPair {
        int colID;
        SQLValue value;
    };

    SQLDriver* driver;
    Table* myTable;
    std::vector<ConditionPair> conditions;
    std::vector<SetPair> sets;
public:
    ModifyHandler(SQLDriver* d) { driver = d; }
    bool prepareTable(Table* table, SQLConditionGroup* cgrp);
    bool prepareSetClause(SQLSetGroup* sgrp);
    void executeDeleteQuery();
    void executeUpdateQuery();
};


#endif //DATABASE_MODIFYHANDLER_H
