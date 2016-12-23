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
#include "../queryhandler/modifyhandler.h"
#include "../queryhandler/checkhelper.h"
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
    bool isVariableTable = true;
//    for (SQLType* type : *fieldList) {
//        if (type->type[0] == 'V') {
//            isVariableTable = true;
//            break;
//        }
//    }
    // TODO: Hash table support: This time must exist primary type.
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
    SQLCheckGroup* checkGroup = 0;

    for (SQLType* type : *fieldList) {
        if (type->primaryType) {
            if (primaryIndex != -1) {
                driver->addErrorMessage("Multiple primary types when creating table.");
                return false;
            } else {
                for (unsigned int i = 0; i < clname.size(); ++ i) {
                    if (type->identifier == clname[i]) {
                        primaryIndex = i;
                        break;
                    }
                }
            }
            continue;
        }
        if (type->isCheck) {
            checkGroup = type->checkGroup;
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

    if (checkGroup != 0) {
        if (!CheckHelper::addCheckCondition(clname, cltype, newTable, checkGroup)) {
            driver->addErrorMessage("Invalid Check conditions.");
            return false;
        }
    }

    if (primaryIndex != -1) {
        // Create empty index for primary type and disable multivalue.
        newTable->setmultivalue(primaryIndex, false);
        newTable->setmajornum(primaryIndex);

        vector<int> idxVec;
        idxVec.push_back(primaryIndex);
        newTable->createindex(idxVec);
    } else {
        driver->addWarningMessage("Current table does not have a primary key.");
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

    Record* record = RecordFactory::getrecord(myTable);
    Iterator* priKeyCompiler = IteratorFactory::getiterator(myTable);
    // Build Choice Cache for check clause.
    vector<vector<string> > choiceCache((unsigned long) myTable->getcolumncount());
    for (auto s = myTable->gettablecondition()->begin(); s != myTable->gettablecondition()->end(); ++ s) {
        if (s->second.first == CheckHelper::choiceCode) {
            choiceCache[s->first] = UIC::stringSplit(s->second.second, "\"");
        }
    }

    int majorRowNum = myTable->getmajornum();
    db_index* tablePrimaryIndex = myTable->getindexes()[majorRowNum];
    if (tablePrimaryIndex == 0) {
        driver->addWarningMessage("Current table does not have a primary key.");
    }

    for (unsigned int i = 0; i < valueGroupList->size(); ++ i) {
        int thisSize = (int) valueGroupList->at(i)->size();
        if (thisSize != record->getcolumncount()) {
            driver->addErrorMessage("Size mismatch in value field of table " + identifier);
            return false;
        }
        // 1. Type constraint (structural)
        for (unsigned int j = 0; j < thisSize; ++ j) {
            SQLValue* sigValue = valueGroupList->at(i)->at(j);
            if (!QueryCondition::typeComparable(sigValue->type, record->getcolumns()[j]->getType()[6])
                || !record->setAt(j, sigValue->content, sigValue->type == SQLValue::LiteralType::NUL)) {
                driver->addErrorMessage("Type mismatch when inserting value " +
                    ((sigValue->type == SQLValue::LiteralType::NUL) ? "<NULL>" : sigValue->content) + " into table " + identifier);
                return false;
            }  
        }
        // 2. Check clause constraint
        if (myTable->gettablecondition()->size() != 0 &&
                !CheckHelper::satisfy(myTable, valueGroupList->at(i), choiceCache)) {
            driver->addErrorMessage("Value inserted at position " + to_string(i + 1) +
                                    " does not satisfy check constraint.");
            return false;
        }
        // 3. Primary Key constraint.
        if (tablePrimaryIndex != 0) {
            vector<pair<int, int> > priKeyRes;
            cout << "Search: " << priKeyCompiler->compile(valueGroupList->
                                                          at(i)->at(majorRowNum)->content, majorRowNum) << endl;
            tablePrimaryIndex->findAll(SQLOperand::EQUAL,
                                       priKeyCompiler->compile(valueGroupList->
                                               at(i)->at(majorRowNum)->content, majorRowNum), &priKeyRes);
            if (priKeyRes.size() != 0) {
                driver->addErrorMessage("Duplicated primary key: " +
                                                valueGroupList->at(i)->at(majorRowNum)->content);
                return false;
            }
        }
        // 4. TODO: Outer link constraint
        record->update();
        int dummy;
        myTable->FastAllInsert(dummy, dummy, record);
    }
    delete record;
    return true;
}

bool SQLDeleteAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when deleting from table "
                                + this->identifier);
        return false;
    }
    Table* myTable = handler->getTableByName(identifier);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + identifier + " does not exist.");
        return false;
    }
    ModifyHandler* modifyHandler = new ModifyHandler(driver);
    bool prepareSucceeded = modifyHandler->prepareTable(myTable, conditionGroup);
    if (prepareSucceeded) modifyHandler->executeDeleteQuery();
    delete modifyHandler;
    return prepareSucceeded;
}

bool SQLUpdateAction::execute()
{
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when updating table "
                                + this->identifier);
        return false;
    }
    Table* myTable = handler->getTableByName(identifier);
    if (myTable == 0) {
        driver->addErrorMessage("Table " + identifier + " does not exist.");
        return false;
    }
    ModifyHandler* modifyHandler = new ModifyHandler(driver);
    bool tablePrepareSucceed = modifyHandler->prepareTable(myTable, conditionGroup);
    if (!tablePrepareSucceed) {
        delete modifyHandler;
        return false;
    }
    bool setPrepareSucceed = modifyHandler->prepareSetClause(setGroup);
    if (setPrepareSucceed) modifyHandler->executeUpdateQuery();
    delete modifyHandler;
    return setPrepareSucceed;
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
        driver->addWarningMessage("Index for " + columnName + " already exists.");
        return true;
    }
    std::vector<int> targetCol;
    targetCol.push_back(columnID);
    currentTable->createindex(targetCol);
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
