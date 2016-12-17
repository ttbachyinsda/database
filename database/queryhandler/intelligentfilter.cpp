//
// Created by jameshuang on 16-12-14.
//

#include "intelligentfilter.h"
#include "../managementhandler/iterator.h"
#include "../DBIndex/db_index.h"
#include "../managementhandler/iteratorfactory.h"
#include "../recordhandler/recordfactory.h"
#include <vector>

Table *IntelligentFilter::apply(Table *target, const std::vector<ConditionPair> &conditions) {
    // assert: All conditions are in the same table / numerical.
    Table* result = new VirtualTable();
    // Copy all columns
    vector<string> clname;
    vector<DataBaseType*> cltype;

    for (int i = 0; i < target->getcolumncount(); ++ i) {
        clname.push_back(target->getcolumnname(i));
        cltype.push_back(UIC::copyType(target->getcolumn(i)));
    }

    result->createTable(clname, cltype);
    result->Initialize();

    // Start Filtering.
    // Determine best filter plan. - select numerical columns which has a value.
    // Use the first one.
    int indexedCol = -1;
    int indexedConditionID = -1;
    for (unsigned int i = 0; i < conditions.size(); ++ i) {
        if (conditions[i].rightIsValue && QueryCondition::indexOperatable(conditions[i].operand) &&
                target->getindexes()[conditions[i].left.columnIndex] != NULL) {
            indexedCol = conditions[i].left.columnIndex;
            indexedConditionID = i;
            break;
        }
    }

    Iterator* targetIterator = IteratorFactory::getiterator(target);
    Record* targetRecord = RecordFactory::getrecord(target);

    Record* resultRecord = RecordFactory::getrecord(result);

    if (indexedCol != -1) {
        db_index* bTreeIndex = target->getindexes()[indexedCol];
        vector< pair<int,int> > searchIndexRes;
        string targetContent = conditions[indexedConditionID].rightValue.content;
        bTreeIndex->findAll(conditions[indexedConditionID].operand, targetContent, &searchIndexRes);

        std::vector<ConditionPair> extractedCondPair;
        for (unsigned int i = 0; i < conditions.size(); ++ i) {
            if (i != indexedConditionID) extractedCondPair.push_back(conditions[i]);
        }

        for (const pair<int, int>& p : searchIndexRes) {
            targetIterator->access(p.first, p.second);
            targetIterator->getdata(targetRecord);
            addToResultIfMatch(targetRecord, result, resultRecord, extractedCondPair);
        }
    } else {
        while (targetIterator->available()) {
            targetIterator->getdata(targetRecord);
            addToResultIfMatch(targetRecord, result, resultRecord, conditions);
            ++ (*targetIterator);
        }
    }

    return result;
}

void IntelligentFilter::addToResultIfMatch(Record *record, Table *resultTable, Record *resultRecord,
                                           const std::vector<ConditionPair> &conds) {
    for (const ConditionPair& c : conds) {
        char cmpType = record->getcolumns()[c.left.columnIndex]->getType()[6];

        std::string driverValue = record->getAt(c.left.columnIndex);
        bool driverValueIsNull = record->getIsNull(c.left.columnIndex);

        std::string passengerValue;
        bool passengerValueIsNull;

        if (c.rightIsValue) {
            passengerValue = c.rightValue.content;
            passengerValueIsNull = (c.rightValue.type == SQLValue::LiteralType::NUL);
        } else {
            passengerValue = record->getAt(c.right.columnIndex);
            passengerValueIsNull = record->getIsNull(c.right.columnIndex);
        }

        bool matchResult = QueryCondition::match(c.operand, cmpType, driverValue, driverValueIsNull,
                                                 passengerValue, passengerValueIsNull);
        if (!matchResult) return;

    }
    // Matched. Add to result.
    for (int i = 0; i < record->getcolumncount(); ++ i) {
        resultRecord->setAt(i, record->getAt(i), record->getIsNull(i));
    }
    resultRecord->update();
    int dum;
    resultTable->FastAllInsert(dum, dum, resultRecord);
}
