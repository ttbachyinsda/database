//
// Created by jameshuang on 16-12-23.
//

#include "modifyhandler.h"
#include <iostream>

// Check whether current myTableRecord match conditions
bool ModifyHandler::checkConditions()
{
    for (unsigned int i = 0; i < conditions.size(); ++ i) {
        if (i == indexedConditionID) continue;

        const ConditionPair& c = conditions[i];
        char cmpType = myTableRecord->getcolumns()[c.left.columnIndex]->getType()[6];

        std::string cmpValue = myTableRecord->getAt(c.left.columnIndex);
        bool cmpValueIsNull = myTableRecord->getIsNull(c.left.columnIndex);

        bool matchResult = QueryCondition::match(c.operand, cmpType, cmpValue, cmpValueIsNull,
                                                 c.rightValue.content,
                                                 (c.rightValue.type == SQLValue::LiteralType::NUL));
        if (!matchResult) return false;
    }
    return true;
}

// Modify myTableRecord according to set clauses.
void ModifyHandler::modifyRecordContent()
{
    for (const SetPair& sp : sets) {
        myTableRecord->setAt(sp.colID, sp.value.content,
                             sp.value.type == SQLValue::LiteralType::NUL);
    }
    myTableRecord->update();
}

bool ModifyHandler::prepareTable(Table *table, SQLConditionGroup *cgrp) {
    // TODO: Check If there is/are a foreign key(s) linked to this table.
    // If not both delete and update query cannot be executed.
    //

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

    myTableIterator = IteratorFactory::getiterator(myTable);
    myTableRecord = RecordFactory::getrecord(myTable);

    // Determine best filter plan. - select numerical columns which has a value.
    // Use the first one index operatable
    for (unsigned int i = 0; i < conditions.size(); ++ i) {
        if (QueryCondition::indexOperatable(conditions[i].operand) &&
                myTable->getindexes()[conditions[i].left.columnIndex] != NULL) {
            indexedCol = conditions[i].left.columnIndex;
            indexedConditionID = i;
            std::cout << "modifyhandler.cpp: Using index." << std::endl;
            break;
        }
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
        // Check whether this key is a foreign key (ie. key is cid, check main table.)
    }
    return true;
}

void ModifyHandler::executeDeleteQuery() {
    if (indexedCol != -1) {
        // should use index.
        db_index* bTreeIndex = myTable->getindexes()[indexedCol];
        vector< pair<int,int> > searchIndexRes;
        string targetContent = myTableIterator->compile(conditions[indexedConditionID].rightValue.content,
                                                        indexedCol);
        bTreeIndex->findAll(conditions[indexedConditionID].operand, targetContent, &searchIndexRes);

        for (const pair<int, int>& p : searchIndexRes) {
            myTableIterator->access(p.first, p.second);
            myTableIterator->getdata(myTableRecord);
            if (checkConditions()) {
                // Check the deleted data is linked to.
                myTableIterator->deletedata();
            }
        }
    } else {
        while (myTableIterator->available()) {
            myTableIterator->getdata(myTableRecord);
            if (checkConditions()) myTableIterator->deletedata();
            ++ (*myTableIterator);
        }
    }
}

void ModifyHandler::executeUpdateQuery() {
    if (indexedCol != -1) {
        // should use index.
        db_index* bTreeIndex = myTable->getindexes()[indexedCol];
        vector< pair<int,int> > searchIndexRes;
        string targetContent = myTableIterator->compile(conditions[indexedConditionID].rightValue.content,
                                                        indexedCol);
        bTreeIndex->findAll(conditions[indexedConditionID].operand, targetContent, &searchIndexRes);

        for (const pair<int, int>& p : searchIndexRes) {
            myTableIterator->access(p.first, p.second);
            myTableIterator->getdata(myTableRecord);
            if (checkConditions()) {
                // Check the deleted data is linked to.
                myTableIterator->deletedata();
                modifyRecordContent();
                int dum;
                myTable->FastAllInsert(dum, dum, myTableRecord);
            }
        }
    } else {
        while (myTableIterator->available()) {
            myTableIterator->getdata(myTableRecord);
            if (checkConditions()) {
                myTableIterator->deletedata();
                modifyRecordContent();
                int dum;
                myTable->FastAllInsert(dum, dum, myTableRecord);
            }
            ++ (*myTableIterator);
        }
    }
}
