#include "queryexecuter.h"
#include "../sqlengine/sqlstruct.h"
#include "../sqlengine/sqldriver.h"
#include "../typehandler/databaseint.h"
#include "intelligentfilter.h"
#include "queryoptimizer.h"

#include <iostream>
using namespace std;

void QueryExecutor::clearUp()
{
    tables.clear();
    selectors.clear();
    conditions.clear();
}

bool QueryExecutor::getTableColumnIndex(int &tid, int &cid, SQLSelector *s,
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
    cid = tables[tid]->getColumnIndexByName(s->tableName);
    if (cid == -1) {
        driver->addErrorMessage("No such column (" + s->tableName + ") in table " + s->databaseName);
        return false;
    }
    return true;
}

bool QueryExecutor::setQuery(SQLTableGroup *tgrp, SQLSelectorGroup *sgrp, SQLConditionGroup *cgrp)
{
    clearUp();

    int tidx = 0;
    std::map<std::string, int> tableDict;
    std::map<std::string, int>::iterator tableDictIterator;

    for (std::string& tbName : *tgrp) {
        tableDict[tbName] = tidx;
        Table* thisTable = driver->getCurrentDatabase()->getTableByName(tbName);
        if (thisTable == 0) {
            driver->addErrorMessage("Table " + tbName + " does not exist in this database.");
            return false;
        }
        tables.push_back(thisTable);
        ++ tidx;
    }

    if (sgrp->allMatched) {
        // Add all selectors
        for (int i = 0; i < tidx; ++ i) {
            int columnsInTable = tables[i]->getcolumncount();
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
            if (s->groupMethod != SQLGroupMethod::BLANK) {
                driver->addErrorMessage("Group clause cannot be applied to where clause.");
                return false;
            }
            selectors.push_back(pair);
        }
    }

    if (cgrp == 0) return true;
    for (SQLCondition* c : *cgrp) {
        ConditionPair thisCondition;
        if (!getTableColumnIndex(thisCondition.left.tableIndex, thisCondition.left.columnIndex,
                                 &(c->lValue), tableDict, tableDictIterator))
            return false;

        char lValueType = tables[thisCondition.left.tableIndex]->
                getcolumns()[thisCondition.left.columnIndex]->getType()[6];

        if (c->type == SQLCondition::VALUE) {
            thisCondition.rightIsValue = true;
            thisCondition.rightValue = c->rValue;
            if (c->operand == SQLOperand::LIKE) {
                thisCondition.rightValue.content = QueryCondition::convertRegex(
                        thisCondition.rightValue.content);
            }
            if (!QueryCondition::typeComparable(c->rValue.type, lValueType)) {
                driver->addErrorMessage("Invalid Comparison between " +
                                        c->lValue.tableName + " and " + c->rValue.content);
                return false;
            }
        } else {
            thisCondition.rightIsValue = false;
            if (c->operand == SQLOperand::LIKE) {
                driver->addErrorMessage("Like conditions cannot match a column in table.");
                return false;
            }
            if (!getTableColumnIndex(thisCondition.right.tableIndex, thisCondition.right.columnIndex,
                                     &(c->rValueColumn), tableDict, tableDictIterator))
                return false;
            if (!QueryCondition::typeComparable(lValueType,
                                tables[thisCondition.right.tableIndex]->
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

bool QueryExecutor::executeQuery()
{
    // ASSERT: All types are fit.
    /*
     * Algorithm Description:
     *
     * 1. Apply all inner / numeric filters.
     * 2. Arrange all tables into a vector.
     * 3. Repeat until vector's size == 1:
     *      - Calculate any 2 tables' condition count.
     *          and give the joint of them a unique score.
     *      - Select 2 tables maximizing the score and join them
     *      - Update condition parameters
     * 4. Output them to SQLResult.
     */

    std::vector<ConditionPair> currentConditions;
    std::vector<Table*> operatingTables;
    std::vector<SelectorPair> operatingSelectors;

    for (SelectorPair& pair : selectors) {
        operatingSelectors.push_back(pair);
    }

    for (ConditionPair& c : conditions) {
        currentConditions.push_back(c);
    }

    for (unsigned tid = 0; tid < tables.size(); ++ tid) {
        operatingTables.push_back(tables[tid]);
        std::vector<ConditionPair> thisTableInnerConditions;
        std::vector<ConditionPair>::iterator cIter = currentConditions.begin();
        while (cIter != currentConditions.end()) {
            if (cIter->left.tableIndex == tid &&
                (cIter->rightIsValue || (!cIter->rightIsValue && cIter->right.tableIndex == tid))) {
                thisTableInnerConditions.push_back(*cIter);
                cIter = currentConditions.erase(cIter);
            } else ++ cIter;
        }
        if (thisTableInnerConditions.size() != 0) {
            // Directly discard old one because this is maintained in database manager.
            operatingTables[tid] = IntelligentFilter::apply(tables[tid], thisTableInnerConditions);
        }
    }

    QueryOptimizer* optimizer = new QueryOptimizer();

    for (unsigned reduceID = 1; reduceID < tables.size(); ++ reduceID) {
        if (currentConditions.size() == 0) {
            driver->addErrorMessage("Join Error: conditions not fully connected.");
            for (Table* tbl : operatingTables) {
                if (tbl->gettabletype() == "Virtual") delete tbl;
            }
            return false;
        }
        // notice: following codes are based on transformed index.
        optimizer->generatePlan(currentConditions, operatingTables);
        unsigned int mergedID1 = (unsigned int) optimizer->getJoinIDPlan().first,
                mergedID2 = (unsigned int) optimizer->getJoinIDPlan().second;

        Table* jointTable = optimizer->executePlan();
        // Heuristic merged operatingTables[mergedID1] and operatingTables[mergedID2] into mergedID1
        // The mergedID1 is at front.
        // Return new table and selected 2 IDs. But the old table is not deleted.

        int mergedID1ColumnCount = operatingTables[mergedID1]->getcolumncount();

        if (operatingTables[mergedID1]->gettabletype() == "Virtual")
            delete operatingTables[mergedID1];
        if (operatingTables[mergedID2]->gettabletype() == "Virtual")
            delete operatingTables[mergedID2];

        operatingTables[mergedID1] = jointTable;

        std::vector<ConditionPair>::iterator iter = currentConditions.begin();
        while (iter != currentConditions.end()) {
            if (iter->left.tableIndex == mergedID2) {
                iter->left.tableIndex = mergedID1;
                iter->left.columnIndex += mergedID1ColumnCount;
            }
            if (iter->right.tableIndex == mergedID2) {
                iter->right.tableIndex = mergedID1;
                iter->right.columnIndex += mergedID1ColumnCount;
            }
            if (iter->right.tableIndex == iter->left.tableIndex) {
                iter = currentConditions.erase(iter);
            } else {
                iter->left.tableIndex = indexMap(iter->left.tableIndex, mergedID2);
                iter->right.tableIndex = indexMap(iter->right.tableIndex, mergedID2);
                iter++;
            }
        }

        for (SelectorPair& pair : operatingSelectors) {
            if (pair.tableIndex == mergedID2) {
                pair.tableIndex = mergedID1;
                pair.columnIndex += mergedID1ColumnCount;
            }
            pair.tableIndex = indexMap(pair.tableIndex, mergedID2);
        }

        std::vector<Table*>::const_iterator tableIter = operatingTables.begin();
        while (mergedID2 --) ++ tableIter;
        operatingTables.erase(tableIter);
    }

    delete optimizer;

    SQLResult* currentResult = new SQLResult((int) selectors.size());
    bool titled = (tables.size() > 1);
    for (SelectorPair& pair : selectors) {
        std::string dispName = tables[pair.tableIndex]->getcolumnname(pair.columnIndex);
        if (titled) {
            dispName = tables[pair.tableIndex]->getname() + "." + dispName;
        }
        currentResult->addTitleField(dispName);
    }

    Table* resultTable = operatingTables[0];
    Iterator* resultTableIterator = IteratorFactory::getiterator(resultTable);
    Record* resultTableRecord = RecordFactory::getrecord(resultTable);

    vector<char> dispTypes;
    for (unsigned t = 0; t < operatingSelectors.size(); ++ t)
        dispTypes.push_back(resultTableRecord->
                            getcolumns()[operatingSelectors[t].columnIndex]->getType()[6]);

    while (resultTableIterator->available()) {
        resultTableIterator->getdata(resultTableRecord);
        currentResult->addNew();
        for (unsigned t = 0; t < operatingSelectors.size(); ++ t) {
            string data = resultTableRecord->getAt(operatingSelectors[t].columnIndex);
            bool resIsNull = resultTableRecord->getIsNull(operatingSelectors[t].columnIndex);
            data = UIC::getUserOutput(dispTypes[t], data, resIsNull);
            currentResult->setData(t, data);
        }
        ++ (*resultTableIterator);
    }

    delete resultTableIterator;
    delete resultTableRecord;
    if (resultTable->gettabletype() == "Virtual")
        delete resultTable;

    driver->setResult(currentResult);

    // No need to clear results.
    return true;
}

QueryExecutor::QueryExecutor(SQLDriver *d)
{
    driver = d;
}

QueryExecutor::~QueryExecutor()
{
    clearUp(); // needed.
}
