//
// Created by jameshuang on 16-10-20.
//

#include "sqlaction.h"
#include <iostream>

bool SQLCreateDatabaseAction::execute()
{
    std::cout << "Database " << this->databaseName << " Created!" << std::endl;
    return true;
}

bool SQLDropDatabaseAction::execute()
{
    std::cout << "Database " << this->databaseName << " Dropped!" << std::endl;
    return true;
}


bool SQLUseDatabaseAction::execute()
{
    return true;
}

bool SQLShowDatabasesAction::execute()
{
    return true;
}


SQLCreateTableAction::~SQLCreateTableAction()
{
    for (SQLType* type : *fieldList) {
        delete type;
    }
    delete fieldList;
}

bool SQLCreateTableAction::execute()
{
    std::cout << "Create Table " << this->tableName << std::endl;
    for (SQLType* type : *fieldList) {
        type->dump();
    }
    return true;
}


bool SQLDropTableAction::execute()
{
    return true;
}

bool SQLDescAction::execute()
{
    return true;
}

bool SQLShowTablesAction::execute()
{
    return true;
}

SQLInsertAction::~SQLInsertAction()
{
    for (SQLValue* value : *valueList) {
        delete value;
    }
    delete valueList;
}

bool SQLInsertAction::execute()
{
    std::cout << "Inserted Into " << this->identifier << std::endl;
    for (SQLValue* value : *valueList) {
        value->dump();
    }
    return true;
}
