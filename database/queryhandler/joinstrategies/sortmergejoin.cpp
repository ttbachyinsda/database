//
// Created by jameshuang on 16-12-10.
//

#include "sortmergejoin.h"

Table *SortMergeJoin::join() {
    db_index* driverIndex = driverTable->getindexes()[driverTableConditionColumnID];
    db_index* passengerIndex = passengerTable->getindexes()[passengerTableConditionColumnID];

    assert(driverIndex != NULL && passengerIndex != NULL);
    assert(operand == SQLOperand::EQUAL);

    std::vector<std::pair<int, int> > driverSequentialArr;
    std::vector<std::pair<int, int> > passengerSequentialArr;
    driverIndex->search_all(&driverSequentialArr);
    passengerIndex->search_all(&passengerSequentialArr);

    /**
     * Jointly traverse 2 table.
     * --------------------------
     * let the smaller value go first until first equal
     * traverse equal targets and add them to result.
     * if one of the iterator reaches end. Join ends.
     */
    char cmpType = driverTable->getcolumns()[driverTableConditionColumnID]->getType()[6];

    auto driverSeqIter = driverSequentialArr.begin();
    auto passengerSeqIter = passengerSequentialArr.begin();

    while (driverSeqIter != driverSequentialArr.end() &&
            passengerSeqIter != passengerSequentialArr.end()) {
        driverIterator->access(driverSeqIter->first, driverSeqIter->second);
        passengerIterator->access(passengerSeqIter->first, passengerSeqIter->second);
        driverIterator->getdata(driverRecord);
        passengerIterator->getdata(passengerRecord);

        string dVal = driverRecord->getAt(driverTableConditionColumnID);
        bool dNull = driverRecord->getIsNull(driverTableConditionColumnID);

        string pVal = passengerRecord->getAt(passengerTableConditionColumnID);
        bool pNull = passengerRecord->getIsNull(passengerTableConditionColumnID);

        bool cmpEq = QueryCondition::match(SQLOperand::EQUAL, cmpType, dVal, dNull, pVal, pNull);
        bool cmpLt = QueryCondition::match(SQLOperand::LESS, cmpType, dVal, dNull, pVal, pNull);

        if (cmpEq) {
            auto dStart = driverSeqIter;
            auto pStart = passengerSeqIter;

            driverSeqIter ++;
            passengerSeqIter ++;
            while (driverSeqIter != driverSequentialArr.end()) {
                driverIterator->access(driverSeqIter->first, driverSeqIter->second);
                driverIterator->getdata(driverRecord);

                string nVal = driverRecord->getAt(driverTableConditionColumnID);
                bool nNull = driverRecord->getIsNull(driverTableConditionColumnID);

                if (QueryCondition::match(SQLOperand::EQUAL, cmpType, dVal, dNull, nVal, nNull)) {
                    ++ driverSeqIter;
                } else break;

            }

            while (passengerSeqIter != passengerSequentialArr.end()) {
                passengerIterator->access(passengerSeqIter->first, passengerSeqIter->second);
                passengerIterator->getdata(passengerRecord);

                string nVal = passengerRecord->getAt(passengerTableConditionColumnID);
                bool nNull = passengerRecord->getIsNull(passengerTableConditionColumnID);

                if (QueryCondition::match(SQLOperand::EQUAL, cmpType, pVal, pNull, nVal, nNull)) {
                    ++ passengerSeqIter;
                } else break;

            }

            auto dEnd = driverSeqIter;
            auto pEnd = passengerSeqIter;

            // Add to result.
            for (driverSeqIter = dStart; driverSeqIter != dEnd; ++ driverSeqIter) {
                for (passengerSeqIter = pStart; passengerSeqIter != pEnd; ++ passengerSeqIter) {
                    driverIterator->access(driverSeqIter->first, driverSeqIter->second);
                    passengerIterator->access(passengerSeqIter->first, passengerSeqIter->second);
                    driverIterator->getdata(driverRecord);
                    passengerIterator->getdata(passengerRecord);
                    addToResultIfMatch(false);
                }
            }

        } else if (cmpLt) {
            ++ driverSeqIter;
        } else {
            ++ passengerSeqIter;
        }

    }

    return resultTable;
}

SortMergeJoin::SortMergeJoin(const vector<ConditionPair> &cond) : JoinStrategy(cond) {}

float SortMergeJoin::estimateCost(int dSize, int pSize, int dIndex, int pIndex, SQLOperand opCode) {
    if (!dIndex || !pIndex) return 1e40;
    if (opCode == SQLOperand::EQUAL) {
        return dSize + pSize;
    }
    return 1e40;
}

