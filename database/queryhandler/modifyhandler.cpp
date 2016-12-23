//
// Created by jameshuang on 16-12-23.
//

#include "modifyhandler.h"

bool ModifyHandler::prepareTable(Table *table, SQLConditionGroup *cgrp) {
    myTable = table;
    /**
     * Support only following conditions:
     *      1. in one table
     *      2. right value is numerical.
     */
    for (SQLCondition* c : *cgrp) {
        ConditionPair thisPair;
        thisPair.operand = c->operand;
        if (c->type != SQLCondition::VALUE) {
            driver->addErrorMessage("Right value in a condition must be literal.");
            return false;
        }
        thisPair.rightIsValue = true;
        thisPair.rightValue = c->rValue;
        if (c->operand == SQLOperand::LIKE) {
            thisPair.rightValue.content = QueryCondition::convertRegex(
                    thisPair.rightValue.content);
        }
        int whereColumnID = myTable->getColumnIndexByName(c->lValue.tableName);
        if (whereColumnID == -1) {
            driver->addErrorMessage("No such column in where clause.");
            return false;
        }
        thisPair.left.tableIndex = 0;
        thisPair.left.columnIndex = whereColumnID;
        // Check type match.
        if (!QueryCondition::typeComparable(c->rValue.type,
                                            myTable->getcolumns()[whereColumnID]->getType()[6])) {
            driver->addErrorMessage("Invalid Comparison between " +
                                    c->lValue.tableName + " and " + c->rValue.content);
            return false;
        }
        conditions.push_back(thisPair);
    }

    return true;
}

bool ModifyHandler::prepareSetClause(SQLSetGroup *sgrp) {
    for (SQLSet* s : *sgrp) {
        // Only use this structure to store set commands.
        SetPair thisPair;
        thisPair.value = s->value;
        int setColumnID = myTable->getColumnIndexByName(s->identifier);
        if (setColumnID == -1) {
            driver->addErrorMessage("No such column in set clause.");
            return false;
        }
        thisPair.colID = setColumnID;
        // Check type match.
        if (!QueryCondition::typeComparable(s->value.type,
                                            myTable->getcolumns()[setColumnID]->getType()[6])) {
            driver->addErrorMessage("Invalid Comparison between " +
                                    s->identifier + " and " + s->value.content);
            return false;
        }
        sets.push_back(thisPair);
    }
    return true;
}

void ModifyHandler::executeDeleteQuery() {
/*    Iterator* currentIterator = IteratorFactory::getiterator(myTable);
    Record* currentRecord = RecordFactory::getrecord(myTable);
    while (currentIterator->available()) {
        currentIterator->getdata(currentRecord);
        if (QueryCondition::match(sqlCondition->operand,
                                  'c',
                                  currentRecord->getAt(whereColumnID),
                                  currentRecord->getIsNull(whereColumnID),
                                  sqlCondition->rValue.content,
                                  sqlCondition->rValue.type == SQLValue::LiteralType::NUL)) {
            currentIterator->deletedata();
        }
        ++ (*currentIterator);
    }*/
}

void ModifyHandler::executeUpdateQuery() {

}
