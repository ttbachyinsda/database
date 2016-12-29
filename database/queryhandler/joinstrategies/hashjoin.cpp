//
// Created by jameshuang on 16-12-10.
//

#include "hashjoin.h"

Table *HashJoin::join() {
    assert(this->operand == SQLOperand::EQUAL);
    assert(this->driverTable->gettabletype() == "HashFlexible");

    while (passengerIterator->available()) {
        passengerIterator->getdata(passengerRecord);
        pair<int, int> findResult = driverTable->FastFindPosition(
                    driverIterator->compile(passengerRecord->getAt(passengerTableConditionColumnID),
                                            driverTableConditionColumnID));
        if (findResult.first == 0 && findResult.second == 0) continue;
        driverIterator->access(findResult.first, findResult.second);
        driverIterator->getdata(driverRecord);
        addToResultIfMatch(false);
        ++ (*passengerIterator);
    }

    return resultTable;
}

HashJoin::HashJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float HashJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    // Assert: driver must be a hash table.
    if (opCode == SQLOperand::EQUAL) {
        return pSize * 2;
    }
    return 1e40;
}
