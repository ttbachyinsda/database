//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_HASHJOIN_H
#define DATABASE_HASHJOIN_H


#include "joinstrategy.h"
#define HASHJOIN_BUCKET_SIZE 100007

class HashJoin : public JoinStrategy {
    // The strategy takes effects when driver table is a hash flexible table.
    // Driver Table: Small -> Distribute in bucket.
    // Passenger Table: Big -> to be traversed and hashed into bucket.
public:
    HashJoin(const vector<ConditionPair> &cond);
    static float estimateCost(int dSize, int pSize,
                              int dIndex, int pIndex, SQLOperand opCode);
    virtual Table *join();
    std::string getType() { return "HASH"; }
};


#endif //DATABASE_HASHJOIN_H
