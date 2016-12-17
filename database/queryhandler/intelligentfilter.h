//
// Created by jameshuang on 16-12-14.
//

#ifndef DATABASE_INTELLIGENTFILTER_H
#define DATABASE_INTELLIGENTFILTER_H


#include "../databasehandler/virtualtable.h"
#include "querycondition.h"

class IntelligentFilter {
public:
    static VirtualTable* apply(Table* target, const std::vector<ConditionPair>& conditions);
};


#endif //DATABASE_INTELLIGENTFILTER_H
