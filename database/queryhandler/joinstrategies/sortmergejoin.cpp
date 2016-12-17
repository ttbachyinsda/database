//
// Created by jameshuang on 16-12-10.
//

#include "sortmergejoin.h"

Table *SortMergeJoin::join() {
    db_index* driverIndex = driverTable->getindexes()[driverTableConditionColumnID];
    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];

    assert(driverIndex != NULL && passengerIndex != NULL);

    // db_index -> getNext() ???

    return resultTable;
}

SortMergeJoin::SortMergeJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float SortMergeJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    return 1e40;
}

