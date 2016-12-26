//
// Created by jameshuang on 16-12-10.
//

#include "hashjoin.h"

Table *HashJoin::join() {
    assert(this->operand == SQLOperand::EQUAL);
    assert(this->driverTable->gettabletype() == "HashFlexible");

    while (passengerIterator->available()) {
        passengerIterator->getdata(passengerRecord);
//        driverTable->FastFind(driverRecord);
        addToResultIfMatch(false);
        ++ (*passengerIterator);
    }


    return resultTable;
}

HashJoin::HashJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float HashJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    // Assert: driver must be a hash table.
    if (opCode == SQLOperand::EQUAL) {
        return pSize + dSize / 1024;
    }
    return 1e40;
}
