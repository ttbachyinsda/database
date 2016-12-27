//
// Created by jameshuang on 16-10-20.
//

#ifndef DATABASE_SQLACTION_H
#define DATABASE_SQLACTION_H

#include <string>
#include <vector>
#include "sqlstruct.h"

class SQLDriver;
class Table;

class SQLAction
{
protected:
    SQLDriver* driver;
public:
    virtual bool execute() = 0;
    virtual ~SQLAction() {}
    void setDriver(SQLDriver* d) { driver = d; }
};

/**
 * @brief The SQLDatabaseAction class
 * @protected databaseName
 *
 * Classes handling database actions:
 *  - CreateDatabaseAction
 *  - DropDatabaseAction
 *  - UseDatabaseAction
 */
class SQLDatabaseAction : public SQLAction
{
protected:
    std::string databaseName;
public:
    SQLDatabaseAction(const std::string& databaseName)
    { this->databaseName = databaseName; }

    virtual ~SQLDatabaseAction() {}
};

class SQLCreateDatabaseAction : public SQLDatabaseAction
{
public:
    SQLCreateDatabaseAction(const std::string& databaseName)
      : SQLDatabaseAction(databaseName) {}
    ~SQLCreateDatabaseAction() {}
    bool execute();
};

class SQLDropDatabaseAction : public SQLDatabaseAction
{
public:
    SQLDropDatabaseAction(const std::string& databaseName)
      : SQLDatabaseAction(databaseName) {}
    ~SQLDropDatabaseAction() {}
    bool execute();
};

class SQLUseDatabaseAction : public SQLDatabaseAction
{
public:
    SQLUseDatabaseAction(const std::string& databaseName)
      : SQLDatabaseAction(databaseName) {}
    ~SQLUseDatabaseAction() {}
    bool execute();
};

/**
 * @brief The SQLShowDatabasesAction class
 */
/* Show databases != database action! */
class SQLShowDatabasesAction : public SQLAction
{
public:
    SQLShowDatabasesAction() {}
    ~SQLShowDatabasesAction() {}
    bool execute();
};

/**
 * @brief The SQLTableAction class
 * @protected tableName
 *
 * Classes handling database actions:
 *  - CreateTableAction
 *  - DropTableAction
 *  - DescAction
 */
class SQLTableAction : public SQLAction
{
protected:
    std::string tableName;
public:
    SQLTableAction(const std::string& tableName)
    { this->tableName = tableName; }

    virtual ~SQLTableAction() {}
};

class SQLCreateTableAction : public SQLTableAction
{
    std::vector<SQLType*>* fieldList;
public:
    SQLCreateTableAction(const std::string& tableName, std::vector<SQLType*>* fList)
      : SQLTableAction(tableName), fieldList(fList) {}
    ~SQLCreateTableAction();
    bool execute();
};

class SQLDropTableAction : public SQLTableAction
{
public:
    SQLDropTableAction(const std::string& tableName)
      : SQLTableAction(tableName) {}
    ~SQLDropTableAction() {}
    bool execute();
};

class SQLDescAction : public SQLTableAction
{
public:
    SQLDescAction(const std::string& tableName)
      : SQLTableAction(tableName) {}
    ~SQLDescAction() {}
    bool execute();
};

/**
 * @brief The SQLShowTablesAction class
 */
/* Show tables != table action! */
class SQLShowTablesAction : public SQLAction
{
public:
    SQLShowTablesAction() {}
    ~SQLShowTablesAction() {}
    bool execute();
};

/**
 * @brief The SQLInsertAction class
 */
class SQLInsertAction : public SQLAction
{
    std::string identifier;
    std::vector<SQLValueGroup*>* valueGroupList;
public:
    SQLInsertAction(const std::string& identifier, std::vector<SQLValueGroup*>* vList)
        : identifier(identifier), valueGroupList(vList) {}
    ~SQLInsertAction();
    bool execute();
};

/**
 * @brief The SQLDeleteAction class
 */
class SQLDeleteAction : public SQLAction
{
    std::string identifier;
    SQLConditionGroup* conditionGroup;
public:
    SQLDeleteAction(const std::string& identifier, SQLConditionGroup* cList)
        : identifier(identifier), conditionGroup(cList) {}
    ~SQLDeleteAction();
    bool execute();
};


/**
 * @brief The SQLUpdateAction class
 */
class SQLUpdateAction : public SQLAction
{
    std::string identifier;
    SQLConditionGroup* conditionGroup;
    SQLSetGroup* setGroup;
public:
    SQLUpdateAction(const std::string& identifier, SQLConditionGroup* cList,
                    SQLSetGroup* sList)
        : identifier(identifier), conditionGroup(cList), setGroup(sList) {}
    ~SQLUpdateAction();
    bool execute();
};

class SQLSelectAction : public SQLAction
{
    SQLTableGroup* fromGroup;
    SQLSelectorGroup* selectorGroup;
    SQLConditionGroup* conditionGroup;
public:
    SQLSelectAction(SQLTableGroup* tList, SQLSelectorGroup* sList, SQLConditionGroup* cList)
        : fromGroup(tList), selectorGroup(sList), conditionGroup(cList) {}
    ~SQLSelectAction();
    bool execute();
};

class SQLGroupSelectAction : public SQLAction
{
    SQLSelectorGroup* selectorGroup;
    SQLTableGroup* groupByGroup;
    SQLTableGroup* fromGroup;
public:
    SQLGroupSelectAction(SQLSelectorGroup *selectorGroup, SQLTableGroup *groupByGroup,
                         SQLTableGroup* tList) : selectorGroup(selectorGroup),
                                                 groupByGroup(groupByGroup),
                                                 fromGroup(tList) {}

    ~SQLGroupSelectAction();
    bool execute();
};

/**
 * @brief The SQLIndexAction class
 */
class SQLIndexAction : public SQLAction
{
protected:
    std::string tableName;
    std::string columnName;
    Table* currentTable;
    int columnID;
public:
    SQLIndexAction(const std::string& tident, const std::string& cident)
        : tableName(tident), columnName(cident) {}
    ~SQLIndexAction() {}
    virtual bool execute();
};

class SQLCreateIndexAction : public SQLIndexAction
{
public:
    SQLCreateIndexAction(const std::string& tident, const std::string& cident)
        : SQLIndexAction(tident, cident) {}
    bool execute();
};

class SQLDropIndexAction : public SQLIndexAction
{
public:
    SQLDropIndexAction(const std::string& tident, const std::string& cident)
        : SQLIndexAction(tident, cident) {}
    bool execute();
};

#endif //DATABASE_SQLACTION_H
