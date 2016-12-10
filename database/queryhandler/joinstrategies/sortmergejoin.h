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
    virtual Table *join();

    virtual string getType() { return "MRG"; }
};


#endif //DATABASE_SORTMERGEJOIN_H
