//
// Created by jameshuang on 16-12-10.
//

#include "nestedloopjoin.h"

Table *NestedLoopJoin::join() {

    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];
    bool canUseIndex = (passengerIndex != NULL) && (operand == SQLOperand::EQUAL ||
                                                    operand == SQLOperand::GREATER ||
                                                    operand == SQLOperand::GREATER_EQUAL ||
                                                    operand == SQLOperand::LESS ||
                                                    operand == SQLOperand::LESS_EQUAL);

    while (driverIterator->available()) {
        driverIterator->getdata(driverRecord);
        if (canUseIndex) {
            switch (operand) {
                case SQLOperand::EQUAL:
                    passengerIndex->search();
            }

            passengerIndex->search_range()
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

