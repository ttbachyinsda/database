//
// Created by jameshuang on 16-12-10.
//

#include "hashjoin.h"

Table *HashJoin::join() {
    assert(this->operand == SQLOperand::EQUAL);

    return resultTable;
}

HashJoin::HashJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float HashJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    return 1e40;
}
