//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_NESTEDLOOPJOIN_H
#define DATABASE_NESTEDLOOPJOIN_H


#include "joinstrategy.h"

class NestedLoopJoin : public JoinStrategy {
    // Driver Table:
    //   - Not use index.
    //   - Outer iteration
    //   - Small
    // Passenger Table:
    //   - Indexed (utilized when <, <=, =, >=, >)
    //   - Big
public:
    NestedLoopJoin(const vector<ConditionPair> &cond);

    virtual Table *join();

    virtual string getType() { return "NST"; }

    static float estimateCost(int dSize, int pSize,
                              int dIndex, int pIndex, SQLOperand opCode);
};


#endif //DATABASE_NESTEDLOOPJOIN_H
