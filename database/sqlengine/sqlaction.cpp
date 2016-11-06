//
// Created by jameshuang on 16-10-20.
//

#include "sqlaction.h"
#include "sqldriver.h"
#include "databasehandler/database.h"
#include "databasehandler/fixedsizetable.h"
#include "recordhandler/record.h"
#include "recordhandler/recordfactory.h"
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

    for (SQLType* type : *fieldList) {
        // TODO: CREATE INDEX FOR PRIMARY TYPE
        // TODO: PRIMARY KEY NOT UNIQUE.
        if (type->primaryType) continue;
        if (type->isCheck) continue;
        clname.push_back(type->identifier);
        // TODO: WHAT IS CONDITION?
        DataBaseType* dbType = UIC::reconvert(type->type, type->length, type->canNull);
        cltype.push_back(dbType);
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
    cout << "DESC" << endl;
    return true;
}

bool SQLShowTablesAction::execute()
{
    // TODO: implemented only for fun.
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when showing tables.");
        return false;
    }
    cout << "==========ALL tbs in " << handler->getname() << "===========" << endl;
    int idx = 0;
    while (true) {
        Table* now = handler->getTable(idx);
        if (!now) break;
        cout << idx << ". " << now->getname() << " (stored in) " << now->getfilename() << endl;
        ++ idx;
    }
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

    // TODO: efficiency condiderations of getrecord.
    Record* record = RecordFactory::getrecord(myTable);
    for (int i = 0; i < valueGroupList->size(); ++ i) {
        int thisSize = valueGroupList->at(i)->size();
        if (thisSize != record->getcolumncount()) {
            driver->addErrorMessage("Size mismatch in value field of table " + identifier);
            return false;
        }
        for (int j = 0; j < thisSize; ++ j) {
            SQLValue* sigValue = valueGroupList->at(i)->at(j);
            if (!sigValue->typeFitChar(record->getcolumns()[j]->getType()[6]) ||
                    !record->setAt(j, sigValue->content, sigValue->type == SQLValue::NUL)) {
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
    cout << "============================" << endl;
    cout << "Delete from table: " << identifier << " where ";
    for (SQLCondition* condition : *conditionGroup) {
        condition->dump();
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
    // TODO: For where clause: needing type judge.
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when querying data.");
        return false;
    }
    bool prepareSucceeded = driver->getQueryExecuter()->setQuery(fromGroup, selectorGroup, conditionGroup);
    if (!prepareSucceeded) return false;
    return driver->getQueryExecuter()->executeQuery();
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
