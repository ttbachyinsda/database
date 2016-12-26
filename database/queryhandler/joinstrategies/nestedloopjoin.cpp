//
// Created by jameshuang on 16-12-10.
//

#include "nestedloopjoin.h"

Table *NestedLoopJoin::join() {

    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];
    bool canUseIndex = (passengerIndex != NULL) && QueryCondition::indexOperatable(this->operand);

    while (driverIterator->available()) {
        driverIterator->getdata(driverRecord);
        if (canUseIndex) {
            string driverMainValue = driverRecord->getAt(driverTableConditionColumnID);
            vector< pair<int,int> > searchIndexRes;
            passengerIndex->findAll(QueryCondition::getInverseOperand(this->operand),
                                    passengerIterator->compile(driverMainValue, passengerTableConditionColumnID),
                                    &searchIndexRes);
            for (const pair<int, int>& p : searchIndexRes) {
                passengerIterator->access(p.first, p.second);
                passengerIterator->getdata(passengerRecord);

                // Main condition is sure to be satisfied.
                addToResultIfMatch(false);
            }
        } else {
            // without index. traverse.
            passengerIterator->getbegin();
            while (passengerIterator->available()) {
                passengerIterator->getdata(passengerRecord);
                addToResultIfMatch(true);
                ++ (*passengerIterator);
            }
        }
        ++ (*driverIterator);
    }

    return resultTable;
}

NestedLoopJoin::NestedLoopJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float NestedLoopJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    if (!pIndex || !QueryCondition::indexOperatable(opCode)) return dSize * pSize;
    else return (float) (dSize * log(pSize));
}

