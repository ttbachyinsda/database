//
// Created by jameshuang on 16-10-20.
//

#include "sqlaction.h"
#include "sqldriver.h"
#include "../databasehandler/database.h"
#include "../databasehandler/fixedsizetable.h"
#include "../recordhandler/record.h"
#include "../recordhandler/recordfactory.h"
#include "../groupalgorithm/grouphandler.h"
#include <iostream>
using namespace std;

bool SQLCreateDatabaseAction::execute()
{
    // Judge if exist.
    if (driver->getDatabaseManager()->getDatabaseByName(databaseName) != NULL) {
        driver->addErrorMessage("Database " + databaseName + " already exists.");
        return false;
    }

    Database* newTempDatabase = new Database();

    newTempDatabase->setname(databaseName);
    newTempDatabase->setfilename(databaseName + ".db");
    // return value ignored (may always return false because file does not exists before!)
    newTempDatabase->Initialize();
    driver->getDatabaseManager()->addDatabase(newTempDatabase);

    return true;
}

bool SQLDropDatabaseAction::execute()
{
    if (driver->getCurrentDatabase() != 0 &&
            driver->getCurrentDatabase()->getname() == databaseName) {
        driver->addWarningMessage("Currently used database is set to NULL.");
        driver->setCurrentDatabase(0);
    }
    bool dbExist = driver->getDatabaseManager()->removeDatabaseByName(databaseName);
    if (!dbExist) {
        driver->addWarningMessage("Database " + databaseName + " does not exist.");
    }
    return true;
}


bool SQLUseDatabaseAction::execute()
{
    Database* base = driver->getDatabaseManager()->getDatabaseByName(databaseName);
    if (base == NULL) {
        driver->addErrorMessage("Database " + databaseName + " does not exist.");
        return false;
    }
    driver->setCurrentDatabase(base);
    return true;
}

bool SQLShowDatabasesAction::execute()
{
    SQLResult* result = new SQLResult(3);
    result->addTitleField("Database ID");
    result->addTitleField("Name");
    result->addTitleField("File Location");
    int idx = 0;
    while (true) {
        Database* now = driver->getDatabaseManager()->getDatabase(idx);
        if (!now) break;
        result->addNew();
        result->setData(0, UIC::inttostring(idx + 1));
        result->setData(1, now->getname());
        result->setData(2, now->getfilename());
        ++ idx;
    }
    driver->setResult(result);
    return true;
}

bool SQLCreateTableAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when creating table "
                                + this->tableName);
        return false;
    }

    if (handler->getTableByName(tableName) != NULL) {
        driver->addErrorMessage("Table " + tableName + " already exists in database "
                                + handler->getname());
        return false;
    }

    // Check Variable Types.
    bool isVariableTable = false;
    for (SQLType* type : *fieldList) {
        if (type->type[0] == 'V') {
            isVariableTable = true;
            break;
        }
    }

    Table* newTable = NULL;
    if (isVariableTable)
        newTable = new FlexibleTable();
    else
        newTable = new FixedSizeTable();

    newTable->setfilename(handler->getname() + "_" + this->tableName + ".tb");
    newTable->setname(this->tableName);

    vector<string> clname;
    vector<DataBaseType*> cltype;
    int primaryIndex = -1;
    int currentIndex = 0;

    for (SQLType* type : *fieldList) {
        // TODO: CREATE INDEX FOR PRIMARY TYPE
        // TODO: PRIMARY KEY NOT UNIQUE.
        if (type->primaryType) continue;
        if (type->isCheck) {
            // Add constraints (conditions) to table
            for (SQLCheck* c : *type->checkGroup) {
                DataBaseType* foundDBType = 0;
                for (unsigned dbi = 0; dbi < clname.size(); ++ dbi) {
                    if (clname[dbi] == c->selector->tableName) {
                        foundDBType = cltype[dbi];
                        break;
                    }
                }
                if (foundDBType == 0) {
                    driver->addWarningMessage("Check target not in previous fields.");
                    continue;
                }
                char foundDBTypeStr = foundDBType->getType()[6];
                if (c->isChoice) {
                    unsigned long choiceListSize = c->choiceList->size();
                    string* conds = new string[choiceListSize + 1];
                    conds[0] = "CHOI";
                    int conds_id = 1;
                    for (SQLValue* sqc : *c->choiceList) {
                        if (!QueryCondition::typeComparable(sqc->type, foundDBTypeStr)) {
                            driver->addErrorMessage("Type mismatch in check choice clause.");
                            return false;
                        }
                        conds[conds_id++] = sqc->content;
                    }
                    foundDBType->readcondition(conds);
                    delete conds;
                    continue;
                }
                // Judge Literal values.
                if (c->operand == SQLOperand::LIKE) {
                    driver->addErrorMessage("LIKE comparator is not supported in check clause.");
                    return false;
                }
                if (!QueryCondition::typeComparable(c->value.type, foundDBTypeStr)) {
                    driver->addErrorMessage("Type mismatch in check clause.");
                    return false;
                }
                if (c->operand == SQLOperand::NOT_EQUAL) {
                    string* conds = new string[2];
                    conds[0] = "NTEQ";
                    conds[1] = c->value.content;
                    foundDBType->readcondition(conds);
                    delete conds;
                    continue;
                } else {
                    // TODO: obtain a literal type max and min.
                }
            }
            continue;
        }
        clname.push_back(type->identifier);
        DataBaseType* dbType = UIC::reconvert(type->type, type->length, type->canNull);
        cltype.push_back(dbType);
        ++ currentIndex;
    }

    newTable->createTable(clname, cltype);

    bool initResult = newTable->Initialize();
    if (!initResult) {
        driver->addErrorMessage("Failed to initialize table " + this->tableName);
        return false;
    }

    handler->addTable(newTable);
    return true;
}


bool SQLDropTableAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when dropping table "
                                + this->tableName);
        return false;
    }
    bool tableExist = handler->removeTableByName(tableName);
    if (!tableExist) {
        driver->addWarningMessage("Table " + tableName + " does not exist.");
    }
    return true;
}

bool SQLDescAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when showing schema of table "
                                + this->tableName);
        return false;
    }
    Table* myTable = handler->getTableByName(tableName);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + tableName + " does not exist.");
        return false;
    }
    // Field, Type, Null, Key, Default, Extra
    SQLResult* result = new SQLResult(6);
    result->addTitleField("Field");
    result->addTitleField("Type");
    result->addTitleField("Null");
    result->addTitleField("Key");
    result->addTitleField("Default");
    result->addTitleField("Extra");

    for (int i = 0; i < myTable->getcolumncount(); ++ i) {
        result->addNew();
        DataBaseType* thisColType = myTable->getcolumn(i);
        result->setData(0, myTable->getcolumnname(i));
        result->setData(1, thisColType->getType());
        result->setData(2, (thisColType->getisNull()) ? "YES" : "NO");
        result->setData(3, myTable->getmultivalue(i) ? "" : "PRI");
        result->setData(4, "NULL");
        result->setData(5, "");
    }
    driver->setResult(result);
    return true;
}

bool SQLShowTablesAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when showing tables.");
        return false;
    }
    SQLResult* result = new SQLResult(3);
    result->addTitleField("Table ID");
    result->addTitleField("Name");
    result->addTitleField("File Location");
    int idx = 0;
    while (true) {
        Table* now = handler->getTable(idx);
        if (!now) break;
        result->addNew();
        result->setData(0, UIC::inttostring(idx + 1));
        result->setData(1, now->getname());
        result->setData(2, now->getfilename());
        ++ idx;
    }
    driver->setResult(result);
    return true;
}


bool SQLInsertAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when inserting into table "
                                + this->identifier);
        return false;
    }
    Table* myTable = handler->getTableByName(identifier);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + identifier + " does not exist.");
        return false;
    }

    // TODO: efficiency considerations of getrecord.
    Record* record = RecordFactory::getrecord(myTable);
    for (int i = 0; i < valueGroupList->size(); ++ i) {
        int thisSize = valueGroupList->at(i)->size();
        if (thisSize != record->getcolumncount()) {
            driver->addErrorMessage("Size mismatch in value field of table " + identifier);
            return false;
        }
        for (int j = 0; j < thisSize; ++ j) {
            SQLValue* sigValue = valueGroupList->at(i)->at(j);
            if (!QueryCondition::typeComparable(sigValue->type, record->getcolumns()[j]->getType()[6])
                || !record->setAt(j, sigValue->content, sigValue->type == SQLValue::NUL)) {
                driver->addErrorMessage("Type mismatch when inserting value " +
                                        sigValue->content + " into table " + identifier);
                return false;
            }  
        }
        record->update();
        int dummy;
        myTable->FastAllInsert(dummy, dummy, record);
    }
    delete record;
    return true;
}

bool SQLDeleteAction::execute()
{
    // TODO: For where clause: needing type judge.
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when inserting into table "
                                + this->identifier);
        return false;
    }
    Table* myTable = handler->getTableByName(identifier);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + identifier + " does not exist.");
        return false;
    }
    /**
     * Support only following conditions:
     *      1. in one table
     *      2. one condition
     *      3. right value is numerical.
     */
    SQLCondition* sqlCondition = conditionGroup->at(0);
    if (conditionGroup->size() != 1) {
        driver->addErrorMessage("Too many conditions in where clauses.");
        return false;
    }
    if (sqlCondition->type != SQLCondition::VALUE) {
        driver->addErrorMessage("Right value in a condition must be literal.");
        return false;
    }
    int whereColumnID = myTable->getColumnIndexByName(sqlCondition->lValue.tableName);
    if (whereColumnID == -1) {
        driver->addErrorMessage("No such column in where clause.");
        return false;
    }
    // TODO: Check type match.
    Iterator* currentIterator = IteratorFactory::getiterator(myTable);
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
    }

    return true;
}

bool SQLUpdateAction::execute()
{
    cout << "============================" << endl;
    cout << "Update " << identifier << " where ";
    for (SQLCondition* condition : *conditionGroup) {
        condition->dump();
    }
    cout << " Set " << endl;
    for (SQLSet* set : *setGroup) {
        set->dump();
    }
    return true;
}

bool SQLSelectAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when querying data.");
        return false;
    }
    bool prepareSucceeded = driver->getQueryExecuter()->setQuery(fromGroup, selectorGroup, conditionGroup);
    if (!prepareSucceeded) return false;
    return driver->getQueryExecuter()->executeQuery();
}

bool SQLGroupSelectAction::execute() {
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when doing group selections.");
        return false;
    }
    Table* myTable = handler->getTableByName(tableName);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + tableName + " does not exist.");
        return false;
    }
    GroupHandler* groupHandler = new GroupHandler(driver);
    bool prepareSucceeded = groupHandler->prepareQuery(myTable, selectorGroup, groupByGroup);
    if (prepareSucceeded) driver->setResult(groupHandler->executeQuery());
    delete groupHandler;
    return prepareSucceeded;
}

bool SQLIndexAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when operating indexes.");
        return false;
    }
    currentTable = handler->getTableByName(tableName);
    if (currentTable == 0) {
        driver->addErrorMessage("Table " + tableName + " does not exist.");
        return false;
    }
    columnID = currentTable->getColumnIndexByName(columnName);
    if (columnID == -1) {
        driver->addErrorMessage("Column " + columnName + " does not exist in table "
                                + tableName);
        return false;
    }
    return true;
}

bool SQLCreateIndexAction::execute()
{
    if (!SQLIndexAction::execute())
        return false;
    if (currentTable->getindexes()[columnID] != 0) {
        driver->addErrorMessage("Index for " + columnName + " already exists.");
        return false;
    }
    currentTable->createemptyindex(columnID);
    // TODO: Insert everything into this new index.
    //currentTable->getindexes()[columnID]->insert();
    return true;
}

bool SQLDropIndexAction::execute()
{
    if (!SQLIndexAction::execute())
        return false;
    if (currentTable->getindexes()[columnID] == 0) {
        driver->addWarningMessage("Index for " + columnName + " does not exist!");
        return true;
    }
    return true;
}


/* Below are destructors */

SQLCreateTableAction::~SQLCreateTableAction()
{
    for (SQLType* type : *fieldList) {
        delete type;
    }
    delete fieldList;
}


SQLInsertAction::~SQLInsertAction()
{
    for (SQLValueGroup* valueGroup : *valueGroupList) {
        for (SQLValue* value : *valueGroup) {
            delete value;
        }
        delete valueGroup;
    }
    delete valueGroupList;
}

SQLUpdateAction::~SQLUpdateAction()
{
    for (SQLCondition* condition : *conditionGroup) {
        delete condition;
    }
    delete conditionGroup;
    for (SQLSet* set : *setGroup) {
        delete set;
    }
    delete setGroup;
}


SQLSelectAction::~SQLSelectAction()
{
    for (SQLCondition* condition : *conditionGroup) {
        delete condition;
    }
    delete conditionGroup;
    delete selectorGroup;
    delete fromGroup;
}

SQLDeleteAction::~SQLDeleteAction()
{
    for (SQLCondition* condition : *conditionGroup) {
        delete condition;
    }
    delete conditionGroup;
}

SQLGroupSelectAction::~SQLGroupSelectAction() {
    delete selectorGroup;
    if (groupByGroup) delete groupByGroup;
}
