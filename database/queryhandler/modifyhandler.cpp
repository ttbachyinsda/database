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
    // Check whether the origin value can be changed.
    return true;
}

// Modify myTableRecord according to set clauses.
bool ModifyHandler::modifyRecordContent()
{
    for (const SetPair& sp : sets) {
        string originValue = myTableRecord->getAt(sp.colID);
        for (const SetForeignPair& fp : sp.foreignPairs) {
            vector<pair<int, int> > outerRefResult;
            fp.valueSearcher->findAll(SQLOperand::EQUAL,
                                      fp.valueCompiler->compile(originValue, fp.foreignColID),
                                      &outerRefResult);
            if (outerRefResult.size() != 0) {
                driver->addWarningMessage("Value " + originValue +
                    " in this table cannot be updated because there are foreign keys linked to it.");
                return false;
            }
        }
        myTableRecord->setAt(sp.colID, sp.value.content,
                             sp.value.type == SQLValue::LiteralType::NUL);
    }
    myTableRecord->update();
    return true;
}

bool ModifyHandler::checkReferenceForCurrentRecord()
{
    if (!needDelCheck) return true;
    for (unsigned int cid = 0; cid < myTable->getcolumncount(); ++ cid) {
        if (delChecks[cid].size() == 0) continue;
        string originValue = myTableRecord->getAt(cid);
        for (const SetForeignPair& sfp : delChecks[cid]) {
            vector<pair<int, int> > outerRefResult;
            sfp.valueSearcher->findAll(SQLOperand::EQUAL,
                                      sfp.valueCompiler->compile(originValue, sfp.foreignColID),
                                      &outerRefResult);
            if (outerRefResult.size() != 0) {
                driver->addWarningMessage("Value " + originValue +
                    " in this table cannot be deleted because there are foreign keys linked to it.");
                return false;
            }
        }
    }
    return true;
}

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
        pair<string, int> foreignTableGrp = myTable->getforeignkeys()->at(setColumnID);
        if (foreignTableGrp.first != "") {
            if (s->value.type == SQLValue::LiteralType::NUL)
                continue;

            Table* foreignTable = driver->getCurrentDatabase()->getTableByName(foreignTableGrp.first);
            db_index* foreignIndex = foreignTable->getindexes()[foreignTableGrp.second];
            if (foreignIndex == 0) {
                driver->addErrorMessage("Corrupted Table. Refuse to update.");
                return false;
            }
            Iterator* compiler = IteratorFactory::getiterator(foreignTable);
            vector<pair<int, int>> forSeaRes;
            foreignIndex->findAll(SQLOperand::EQUAL, compiler->compile(s->value.content,
                                                                       foreignTableGrp.second),
                                  &forSeaRes);
            delete compiler;
            if (forSeaRes.size() == 0) {
                driver->addErrorMessage("Set value target is not in table " + foreignTable->getname());
                return false;
            }
        }
        vector<pair<string, int> > linkedColGrp = myTable->getlinkedcolumn()->at(setColumnID);
        for (const pair<string, int>& p : linkedColGrp) {
            SetForeignPair fPair;
            Table* outerLinkTable = driver->getCurrentDatabase()->getTableByName(p.first);
            // May not exist
            fPair.valueSearcher = outerLinkTable->getindexes()[p.second];
            fPair.valueCompiler = IteratorFactory::getiterator(outerLinkTable);
            fPair.foreignColID = p.second;
            thisPair.foreignPairs.push_back(fPair);
        }
    }
    return true;
}

void ModifyHandler::executeDeleteQuery() {
    // Prepare delete check table.
    delChecks.clear();
    needDelCheck = false;
    for (unsigned int cid = 0; cid < myTable->getcolumncount(); ++ cid) {
        vector<SetForeignPair> currentPairs;
        for (const pair<string, int>& cp : myTable->getlinkedcolumn()->at(cid)) {
            SetForeignPair thisPair;
            Table* outerTable = driver->getCurrentDatabase()->getTableByName(cp.first);
            thisPair.valueSearcher = outerTable->getindexes()[cp.second];
            thisPair.valueCompiler = IteratorFactory::getiterator(outerTable);
            thisPair.foreignColID = cp.second;
            needDelCheck = true;
            currentPairs.push_back(thisPair);
        }
        delChecks.push_back(currentPairs);
    }

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
            if (checkConditions() && checkReferenceForCurrentRecord()) {
                // Check the deleted data is linked to.
                myTableIterator->deletedata();
            }
        }
    } else {
        while (myTableIterator->available()) {
            myTableIterator->getdata(myTableRecord);
            if (checkConditions() && checkReferenceForCurrentRecord())
                myTableIterator->deletedata();
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
                myTableIterator->deletedata();
                if (modifyRecordContent()) {
                    int dum;
                    myTable->FastAllInsert(dum, dum, myTableRecord);
                }
            }
        }
    } else {
        while (myTableIterator->available()) {
            myTableIterator->getdata(myTableRecord);
            if (checkConditions()) {
                myTableIterator->deletedata();
                if (modifyRecordContent()) {
                    int dum;
                    myTable->FastAllInsert(dum, dum, myTableRecord);
                }
            }
            ++ (*myTableIterator);
        }
    }
}
