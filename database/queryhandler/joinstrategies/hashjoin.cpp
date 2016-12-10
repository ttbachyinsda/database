//
// Created by jameshuang on 16-12-10.
//

#include "hashjoin.h"

Table *HashJoin::join() {
    assert(this->operand == SQLOperand::EQUAL);

    return resultTable;
}
