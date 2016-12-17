//
// Created by jameshuang on 16-12-14.
//

#ifndef DATABASE_QUERYOPTIMIZER_H
#define DATABASE_QUERYOPTIMIZER_H

#include <utility>
#include <string>
#include "../databasehandler/table.h"
#include "querycondition.h"
#include "joinstrategies/joinstrategy.h"

class QueryOptimizer {
    int driverTableID;
    int passengerTableID;
    JoinStrategy* joinStrategy;
public:
    QueryOptimizer() { joinStrategy = 0; };
    ~QueryOptimizer() { if (joinStrategy) delete joinStrategy; };

    void generatePlan(const std::vector<ConditionPair>& conditions,
                        const std::vector<Table*>& tables);
    Table* executePlan() { return joinStrategy->join(); }

    std::pair<int, int> getJoinIDPlan()
    { return std::pair<int, int>(driverTableID, passengerTableID); };
};


#endif //DATABASE_QUERYOPTIMIZER_H
