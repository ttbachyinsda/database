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

