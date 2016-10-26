//
// Created by jameshuang on 16-10-20.
//

#include "sqlaction.h"
#include <iostream>
using namespace std;

bool SQLCreateDatabaseAction::execute()
{
    cout << "============================" << endl;
    std::cout << "Database " << this->databaseName << " Created!" << std::endl;
    return true;
}

bool SQLDropDatabaseAction::execute()
{
    cout << "============================" << endl;
    std::cout << "Database " << this->databaseName << " Dropped!" << std::endl;
    return true;
}


bool SQLUseDatabaseAction::execute()
{
    cout << "============================" << endl;
    return true;
}

bool SQLShowDatabasesAction::execute()
{
    cout << "============================" << endl;
    return true;
}

bool SQLCreateTableAction::execute()
{
    cout << "============================" << endl;
    std::cout << "Create Table " << this->tableName << std::endl;
    for (SQLType* type : *fieldList) {
        type->dump();
    }
    return true;
}


bool SQLDropTableAction::execute()
{
    cout << "============================" << endl;
    return true;
}

bool SQLDescAction::execute()
{
    cout << "============================" << endl;
    return true;
}

bool SQLShowTablesAction::execute()
{
    cout << "============================" << endl;
    return true;
}


bool SQLInsertAction::execute()
{
    cout << "============================" << endl;
    std::cout << "Inserted Into " << this->identifier << std::endl;
    for (SQLValueGroup* valueGroup : *valueGroupList) {
        std::cout << "=================GRP===============" << std::endl;
        for (SQLValue* value : *valueGroup) {
            value->dump();
        }
    }
    return true;
}

bool SQLDeleteAction::execute()
{
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
    cout << "============================" << endl;
    cout << "Select ";
    selectorGroup->dump();
    cout << " From ";
    for (std::string str : *fromGroup) {
        cout << str << ' ';
    }
    cout << " where \n";
    for (SQLCondition* condition : *conditionGroup) {
        condition->dump();
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
