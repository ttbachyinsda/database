#include "queryexecuter.h"
#include "../sqlengine/sqlstruct.h"
#include "../sqlengine/sqldriver.h"
#include "../typehandler/databaseint.h"

#include <iostream>
using namespace std;

void QueryExecuter::clearUp()
{
    tables.clear();
    for (Record* r : records) { delete r; }
    records.clear();
    for (Iterator* i : iterators) { delete i; }
    iterators.clear();

    selectors.clear();
    conditions.clear();
}

bool QueryExecuter::getTableColumnIndex(int &tid, int &cid, SQLSelector *s,
                                        std::map<string, int> &dict,
                                        std::map<string, int>::iterator &dictIter)
{
    // Decide Table ID
    if (s->hasPrefix()) {
        dictIter = dict.find(s->databaseName);
        if (dictIter == dict.end()) {
            driver->addErrorMessage("Selectors not in previous targets.");
            return false;
        } else {
            tid = dictIter->second;
        }
    } else {
        if (tables.size() == 1) tid = 0;
        else {
            driver->addErrorMessage("No specifier before column name " + s->tableName);
            return false;
        }
    }
    // Decide Column ID
//    cid = -1;
//    for (int j = 0; j < records[tid]->getcolumncount(); ++ j) {
//        if (s->tableName == tables[tid]->getcolumnname(j)) {
//            cid = j;
//            break;
//        }
//    }
    cid = tables[tid]->getColumnIndexByName(s->tableName);
    if (cid == -1) {
        driver->addErrorMessage("No such column (" + s->tableName + ") in table " + s->databaseName);
        return false;
    }
    return true;
}

bool QueryExecuter::typeComparable(char a, char b)
{
    if ((a == 'V' && b == 'C') || (a == 'C' && b == 'V') ||
            (a == 'I' && b == 'I'))
        return true;
    return false;
}

void QueryExecuter::traverseTable(int tid, SQLResult *result)
{
    if (tid == tables.size()) {
        addToResultIfMatch(result);
        return;
    }
    Iterator* currentIterator = iterators.at(tid);
    while (currentIterator->available()) {
        traverseTable(tid + 1, result);
        ++ (*currentIterator);
    }
}

void QueryExecuter::addToResultIfMatch(SQLResult *result)
{
    // retrieve all data in this combination
    for (int i = 0; i < tables.size(); ++ i) {
        // TODO: Simplify following code using new interface.
        int dummy;
        iterators[i]->getdata(tempLinkedRowData[i], dummy);
        records[i]->Input(tempLinkedRowData[i]);
    }
    for (QueryCondition& con : conditions) {

        bool bresult;
        if (con.rightIsValue)
            bresult = con.compare(records[con.left.tableIndex]->getAt(con.left.columnIndex),
                    records[con.left.tableIndex]->getcolumns()[con.left.columnIndex]->getisNull(),
                     con.rightValue.content, con.rightValue.type == SQLValue::NUL);
        else
            bresult = con.compare(records[con.left.tableIndex]->getAt(con.left.columnIndex),
                    records[con.left.tableIndex]->getcolumns()[con.left.columnIndex]->getisNull(),
                                 records[con.right.tableIndex]->getAt(con.right.columnIndex),
                    records[con.right.tableIndex]->getcolumns()[con.right.columnIndex]->getisNull());
        if (!bresult) return;
    }
    // Condition Match: Add to result.
    result->addNew();
    int did = 0;
    for (SelectorPair& s : selectors) {
        result->setData(did, records[s.tableIndex]->getAt(s.columnIndex));
        ++ did;
    }
}

bool QueryExecuter::setQuery(SQLTableGroup *tgrp, SQLSelectorGroup *sgrp, SQLConditionGroup *cgrp)
{
    clearUp();

    int tidx = 0;
    std::map<std::string, int> tableDict;
    std::map<std::string, int>::iterator tableDictIterator;

    for (std::string& tbName : *tgrp) {
        tableDict[tbName] = tidx;
        Table* thisTable = driver->getCurrentDatabase()->getTableByName(tbName);
        tables.push_back(thisTable);
        records.push_back(RecordFactory::getrecord(thisTable));
        iterators.push_back(IteratorFactory::getiterator(thisTable));
        ++ tidx;
    }

    if (sgrp->allMatched) {
        // Add all selectors
        for (int i = 0; i < tidx; ++ i) {
            int columnsInTable = records[i]->getcolumncount();
            for (int j = 0; j < columnsInTable; ++ j) {
                SelectorPair pair;
                pair.tableIndex = i;
                pair.columnIndex = j;
                selectors.push_back(pair);
            }
        }
    } else {
        for (SQLSelector* s : sgrp->selectors) {
            SelectorPair pair;
            if (!getTableColumnIndex(pair.tableIndex, pair.columnIndex,
                                     s, tableDict, tableDictIterator))
                return false;
            selectors.push_back(pair);
        }
    }

    for (SQLCondition* c : *cgrp) {
        QueryCondition thisCondition;
        if (!getTableColumnIndex(thisCondition.left.tableIndex, thisCondition.left.columnIndex,
                                 &(c->lValue), tableDict, tableDictIterator))
            return false;

        thisCondition.lValueType = records[thisCondition.left.tableIndex]-> \
                getcolumns()[thisCondition.left.columnIndex]->getType()[6];

        if (c->type == SQLCondition::VALUE) {
            thisCondition.rightIsValue = true;
            thisCondition.rightValue = c->rValue;
            if (!c->rValue.typeFitChar(thisCondition.lValueType)) {
                driver->addErrorMessage("Invalid Comparison between " +
                                        c->lValue.tableName + " and " + c->rValue.content);
                return false;
            }
        } else {
            thisCondition.rightIsValue = false;
            if (!getTableColumnIndex(thisCondition.right.tableIndex, thisCondition.right.columnIndex,
                                     &(c->rValueColumn), tableDict, tableDictIterator))
                return false;
            if (!typeComparable(thisCondition.lValueType,
                                records[thisCondition.right.tableIndex]-> \
                                getcolumns()[thisCondition.right.columnIndex]->getType()[6])) {
                driver->addErrorMessage("Invalid Comparison between " +
                                        c->lValue.tableName + " and " + c->rValueColumn.tableName);
                return false;
            }
        }
        thisCondition.operand = c->operand;
        conditions.push_back(thisCondition);
    }
    return true;
}

bool QueryExecuter::executeQuery()
{
    // ASSERT: All types are fit.
    // TODO: rearrange query sequence.

    // ASSERT: Below - NO EXCEPTION SHOULD HAPPEN (PTR_DELETE)
    SQLResult* currentResult = new SQLResult(selectors.size());
    bool titled = (tables.size() > 1);
    for (SelectorPair& pair : selectors) {
        std::string dispName = tables[pair.tableIndex]->getcolumnname(pair.columnIndex);
        if (titled) {
            dispName = tables[pair.tableIndex]->getname() + "." + dispName;
        }
        currentResult->addTitleField(dispName);
    }
    tempLinkedRowData = new char*[tables.size()];
    for (int i = 0; i < tables.size(); ++ i)
        tempLinkedRowData[i] = new char[iterators[i]->getcurrentsize()];

    traverseTable(0, currentResult);

    driver->setResult(currentResult);

    for (int i = 0; i < tables.size(); ++ i)
        delete[] tempLinkedRowData[i];
    delete[] tempLinkedRowData;

    // No need to clear results.
    return true;
}

QueryExecuter::QueryExecuter(SQLDriver *d)
{
    driver = d;
    tempLinkedRowData = 0;
}

QueryExecuter::~QueryExecuter()
{
    clearUp(); // needed.
}
