//
// Created by jameshuang on 16-12-10.
//

#include "nestedloopjoin.h"
#include "../../databasehandler/ramtable.h"
#include "../../managementhandler/iterator.h"
#include "../../managementhandler/iteratorfactory.h"
#include "../../recordhandler/recordfactory.h"

Table *NestedLoopJoin::join() {

    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];

    while (driverIterator->available()) {
        driverIterator->getdata(driverRecord);
        if (passengerIndex != NULL) {
            // passenger table has index. use index to do this.
//            passengerIndex->search_range();
            /*
             * passengerIterator->access();
             * passengerIterator->getdata(passengerRecord);
             * addToResultIfMatch();
             */
        } else {
            // without index. traverse.
            passengerIterator->getbegin();
            while (passengerIterator->available()) {
                passengerIterator->getdata(passengerRecord);
                addToResultIfMatch();
            }
        }
        ++ (*driverIterator);
    }

    return resultTable;
}

