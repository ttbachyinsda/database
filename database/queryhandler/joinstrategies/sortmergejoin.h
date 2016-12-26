//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_SORTMERGEJOIN_H
#define DATABASE_SORTMERGEJOIN_H


#include "joinstrategy.h"

class SortMergeJoin : public JoinStrategy {
    // Driver and Passenger are the same.
    // They all have to have index.
public:
    SortMergeJoin(const vector<ConditionPair> &cond);

    virtual Table *join();

    virtual string getType() { return "MRG"; }

    static float estimateCost(int dSize, int pSize,
                              int dIndex, int pIndex, SQLOperand opCode);
};


#endif //DATABASE_SORTMERGEJOIN_H
