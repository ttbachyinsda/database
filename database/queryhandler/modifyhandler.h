//
// Created by jameshuang on 16-12-23.
//

#ifndef DATABASE_MODIFYHANDLER_H
#define DATABASE_MODIFYHANDLER_H


#include "../sqlengine/sqldriver.h"

class ModifyHandler {

    struct SetForeignPair {
        int foreignColID;
        Iterator* valueCompiler;
        db_index* valueSearcher;
    };

    struct SetPair {
        int colID;
        SQLValue value;
        std::vector<SetForeignPair> foreignPairs;
    };

    SQLDriver* driver;
    Table* myTable;
    Iterator* myTableIterator;
    Record* myTableRecord;

    std::vector<ConditionPair> conditions;
    std::vector<SetPair> sets;

    int indexedCol;
    int indexedConditionID;

    bool checkConditions();
    bool modifyRecordContent();

public:
    ModifyHandler(SQLDriver* d) {
        driver = d;
        myTableIterator = 0;
        myTableRecord = 0;
        indexedCol = -1;
        indexedConditionID = -1;
    }
    bool prepareTable(Table* table, SQLConditionGroup* cgrp);
    bool prepareSetClause(SQLSetGroup* sgrp);
    void executeDeleteQuery();
    void executeUpdateQuery();
    ~ModifyHandler() {
        if (myTableIterator) delete myTableIterator;
        if (myTableRecord) delete myTableRecord;
        for (const SetPair& sp : sets) {
            for (const SetForeignPair& fp : sp.foreignPairs) {
                delete fp.valueCompiler;
            }
        }
    }
};


#endif //DATABASE_MODIFYHANDLER_H
