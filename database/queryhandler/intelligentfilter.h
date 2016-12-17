//
// Created by jameshuang on 16-12-14.
//

#ifndef DATABASE_INTELLIGENTFILTER_H
#define DATABASE_INTELLIGENTFILTER_H


#include "../databasehandler/virtualtable.h"
#include "querycondition.h"

class IntelligentFilter {
    // defined in a single table (different from join strategies.)
    static void addToResultIfMatch(Record* record, Table* resultTable, Record* resultRecord,
                                   const std::vector<ConditionPair>& conds);
public:
    static Table* apply(Table* target, const std::vector<ConditionPair>& conditions);
};


#endif //DATABASE_INTELLIGENTFILTER_H
