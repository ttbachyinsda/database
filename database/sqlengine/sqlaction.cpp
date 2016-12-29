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
#include <algorithm>
using namespace std;

bool SQLCreateDatabaseAction::execute()
{
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    bool isHashTable = false;
    for (SQLType* type : *fieldList) {
        if (type->primaryType) {
            isHashTable = true;
            break;
        }
    }

    Table* newTable = NULL;
    if (isHashTable)
        newTable = new HashFlexibleTable();
    else
        newTable = new FlexibleTable();

    newTable->setfilename(handler->getname() + "_" + this->tableName + ".tb");
    newTable->setname(this->tableName);

    vector<string> clname;
    vector<DataBaseType*> cltype;
    int primaryIndex = -1;
    int currentIndex = 0;
    SQLCheckGroup* checkGroup = 0;

    vector<pair<string, int>> foreignKeyLinks;
    vector<Table*> foreignKeyTargetTables;

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
        if (type->hasForeignKey) {
            Table* linkedTable = handler->getTableByName(type->foreignKey->databaseName);
            if (linkedTable == 0) {
                driver->addErrorMessage("No such table " + type->foreignKey->databaseName + " in this database.");
                return false;
            }
            int colInTable = linkedTable->getColumnIndexByName(type->foreignKey->tableName);
            if (colInTable == -1) {
                driver->addErrorMessage("No such column " + type->foreignKey->tableName + " in table " + linkedTable->getname());
                return false;
            }
            // Judge whether foreign is primary in that table
            if (linkedTable->getindexes()[colInTable] == 0) {
                driver->addErrorMessage("Foreign key references does not have a primary key.");
                return false;
            }
            // Judge whether type is the same
            if (type->length != linkedTable->getcolumns()[colInTable]->getRealSize() ||
                    type->type[0] != linkedTable->getcolumns()[colInTable]->getType()[6]) {
                driver->addErrorMessage("Type mismatch on foreign key.");
                return false;
            }
            foreignKeyLinks.push_back(make_pair(type->foreignKey->databaseName, colInTable));
            foreignKeyTargetTables.push_back(linkedTable);
        } else {
            foreignKeyLinks.push_back(make_pair("", 0));
            foreignKeyTargetTables.push_back(0);
        }
        if (type->type[0] == 'B' && currentIndex != 1) {
            driver->addErrorMessage("Current table layout is not supported.");
            return false;
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
        driver->addWarningMessage("Current table does not have a primary key. Flexible table created.");
    }

    // Add foreign keys to this table and target tables.
    // Update is done here because error could occur when parsing.
    vector<int> idxForVec;
    for (unsigned int i = 0; i < foreignKeyLinks.size(); ++ i) {
        newTable->getforeignkeys()->at(i) = foreignKeyLinks[i];
        Table* targetTable = foreignKeyTargetTables[i];
        if (targetTable) {
            targetTable->getlinkedcolumn()->at(foreignKeyLinks[i].second).
                    push_back(make_pair(newTable->getname(), i));
            if (i != primaryIndex) idxForVec.push_back(i);
        }
    }
    newTable->createindex(idxForVec);

    handler->addTable(newTable);
    return true;
}


bool SQLDropTableAction::execute()
{
    if (!checkEncrypted()) return false;
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when dropping table "
                                + this->tableName);
        return false;
    }
    Table* currentTable = handler->getTableByName(tableName);
    if (currentTable == 0) {
        driver->addWarningMessage("Table " + tableName + " does not exist.");
        return true;
    }
    // PASS 1: Check outer reference
    for (unsigned int cid = 0; cid < currentTable->getcolumncount(); ++ cid) {
        if (currentTable->getlinkedcolumn()->at(cid).size() != 0) {
            driver->addErrorMessage("Column " + currentTable->getcolumnname(cid) +
                                    " in the current table is a foreign key of table: " +
                                    currentTable->getlinkedcolumn()->at(cid)[0].first);
            return false;
        }
    }
    // PASS 2: remove output reference
    for (unsigned int cid = 0; cid < currentTable->getcolumncount(); ++ cid) {
        const pair<string, int>& curColForeignKeyPair = currentTable->getforeignkeys()->at(cid);
        if (curColForeignKeyPair.first != "") {
            Table* outerRefTable = handler->getTableByName(curColForeignKeyPair.first);
            assert(outerRefTable != 0);
            vector<pair<string, int> >& foreignRefs = outerRefTable->
                    getlinkedcolumn()->at(curColForeignKeyPair.second);
            auto refStrain = std::find(foreignRefs.begin(), foreignRefs.end(), make_pair(currentTable->getname(), (int) cid));
            if (refStrain == foreignRefs.end()) {
                driver->addWarningMessage("Cannot find foreign key referring backs, your table maybe corrupted.");
            }
            foreignRefs.erase(refStrain);
        }
    }
    handler->removeTableByName(tableName);
    return true;
}

bool SQLDescAction::execute()
{
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
    // TODO: possible memory leak...
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
    bool hasPriKey = tablePrimaryIndex != 0 && !myTable->getmultivalue(majorRowNum);
    bool isHashFlexibleTable = (myTable->gettabletype() == "HashFlexible");
    if (!hasPriKey) {
        driver->addWarningMessage("Current table does not have a primary key.");
    }

    // Cache foreign key indexes.
    vector<db_index*> cachedDatabaseIndex;
    vector<Iterator*> foreignKeyCompilers;
    vector<int> foreignKeyColumns;
    bool needForeignKeyConstraint = false;
    for (unsigned int col = 0; col < myTable->getcolumncount(); ++ col) {
        pair<string, int> foreignKeyPair = myTable->getforeignkeys()->at(col);
        if (foreignKeyPair.first == "") {
            cachedDatabaseIndex.push_back(0);
            foreignKeyCompilers.push_back(0);
            foreignKeyColumns.push_back(0);
        } else {
            Table* refTable = handler->getTableByName(foreignKeyPair.first);
            cachedDatabaseIndex.push_back(refTable->getindexes()[foreignKeyPair.second]);
            foreignKeyCompilers.push_back(IteratorFactory::getiterator(refTable));
            foreignKeyColumns.push_back(foreignKeyPair.second);
            needForeignKeyConstraint = true;
        }
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
                                        UIC::getUserOutput(sigValue->type, sigValue->content) +
                                        " into table " + identifier);
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
        if (hasPriKey) {
            bool primaryKeyDuplicated = false;
            if (isHashFlexibleTable) {
                primaryKeyDuplicated = myTable->FastFind(record);
            } else {
                vector<pair<int, int> > priKeyRes;
                tablePrimaryIndex->findAll(SQLOperand::EQUAL,
                                           priKeyCompiler->compile(valueGroupList->
                                                   at(i)->at(majorRowNum)->content, majorRowNum), &priKeyRes);
                primaryKeyDuplicated = (priKeyRes.size() != 0);
            }
            if (primaryKeyDuplicated) {
                driver->addErrorMessage("Duplicated primary key: " +
                                                valueGroupList->at(i)->at(majorRowNum)->content);
                return false;
            }
        }
        // 4. Outer link constraint
        if (needForeignKeyConstraint) {
            for (unsigned int j = 0; j < thisSize; ++j) {
                SQLValue *sigValue = valueGroupList->at(i)->at(j);
                // NULL is always allowed;
                if (sigValue->type == SQLValue::LiteralType::NUL) continue;
                if (cachedDatabaseIndex[j] != 0) {
                    vector<pair<int, int> > forKeyRes;
                    cachedDatabaseIndex[j]->findAll(SQLOperand::EQUAL,
                                                    foreignKeyCompilers[j]->compile(
                                                            sigValue->content, foreignKeyColumns[j]),
                                                    &forKeyRes);
                    if (forKeyRes.size() == 0) {
                        driver->addErrorMessage("No such key " + sigValue->content +
                                                        " in foreign key references.");
                        return false;
                    }
                }
            }
        }
        record->update();
        int dummy;
        myTable->FastAllInsert(dummy, dummy, record);
        driver->incAffectedRows();
    }

    for (Iterator* it : foreignKeyCompilers) {
        delete it;
    }
    delete priKeyCompiler;
    delete record;
    return true;
}

bool SQLDeleteAction::execute()
{
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
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
    if (!checkEncrypted()) return false;
    Database* handler = driver->getCurrentDatabase();
    if (handler == 0) {
        driver->addErrorMessage("No database is selected when doing group selections.");
        return false;
    }
    bool isGeneralSelection = true;
    if (!selectorGroup->allMatched) {
        for (SQLSelector* s : selectorGroup->selectors) {
            if (s->groupMethod != SQLGroupMethod::BLANK) {
                isGeneralSelection = false;
                break;
            }
        }
    }
    if (isGeneralSelection) {
        bool prepareSucceeded = driver->getQueryExecuter()->setQuery(fromGroup, selectorGroup, 0);
        if (!prepareSucceeded) return false;
        return driver->getQueryExecuter()->executeQuery();
    } else {
        if (fromGroup->size() != 1) {
            driver->addErrorMessage("Group Selection could only be conducted in one single table.");
            return false;
        }
        Table* myTable = handler->getTableByName(fromGroup->at(0));
        if (myTable == 0) {
            driver->addErrorMessage("Table " + fromGroup->at(0) + " does not exist.");
            return false;
        }
        GroupHandler* groupHandler = new GroupHandler(driver);
        bool prepareSucceeded = groupHandler->prepareQuery(myTable, selectorGroup, groupByGroup);
        if (prepareSucceeded) driver->setResult(groupHandler->executeQuery());
        delete groupHandler;
        return prepareSucceeded;
    }
}

bool SQLIndexAction::execute()
{
    if (!checkEncrypted()) return false;
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
    if (currentTable->getforeignkeys()->at(columnID).first != "" ||
            currentTable->getmajornum() == columnID) {
        driver->addErrorMessage("The index at this column cannot be deleted.");
        return false;
    }
    currentTable->deleteindex(columnID);
    return true;
}


bool SQLEncryptAction::execute()
{
    if (!checkEncrypted()) return false;
    driver->encryptDatabaseManager(password);
    return true;
}

bool SQLDecryptAction::execute()
{
    if (!driver->getIsEncrypted()) {
        driver->addWarningMessage("The current database is not encrypted.");
        return true;
    }
    driver->decryptDatabaseManager(password);
    if (driver->getIsEncrypted()) {
        driver->addErrorMessage("Decrypt master key error: wrong password.");
        return false;
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
    delete fromGroup;
}

bool SQLAction::checkEncrypted()
{
    if (driver->getIsEncrypted()) {
        driver->addErrorMessage("Database is encrypted.");
        return false;
    }
    return true;
}
