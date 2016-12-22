//
// Created by jameshuang on 16-12-10.
//

#include "sortmergejoin.h"

Table *SortMergeJoin::join() {
    db_index* driverIndex = driverTable->getindexes()[driverTableConditionColumnID];
    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];

    assert(driverIndex != NULL && passengerIndex != NULL);
    // The following condition is asserted because estimate cost will always generate LESS
    // is better than GREATER.
    assert(operand == SQLOperand::EQUAL || operand == SQLOperand::LESS ||
                   operand == SQLOperand::LESS_EQUAL);

    // db_index -> getNext() ???
    /**
     * Sort Merge Join.
     * Work best if driver <= passenger.
     * Need two arranged sequence. or (more graceful, not necessary on mem: an iterator.)
     *
     * Outer Iteration is driver, find the first place condition is satisfied in passenger seq.
     *
     * PROBLEM: why Not Nested Loop Join?
     */
//     driverIndex->search_all();

    return resultTable;
}

SortMergeJoin::SortMergeJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float SortMergeJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    if (!dIndex || !pIndex) return 1e40;
    if (opCode == SQLOperand::LESS_EQUAL || opCode == SQLOperand::LESS) {
        return dSize * pSize;
    } else if (opCode == SQLOperand::EQUAL) {
        return dSize + pSize;
    }
    return 1e40;
}

