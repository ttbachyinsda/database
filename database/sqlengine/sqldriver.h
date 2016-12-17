//
// Created by jameshuang on 16-10-19.
//

#ifndef DATABASE_SQLDRIVER_H
#define DATABASE_SQLDRIVER_H

#include <string>
#include <vector>
#include "sqlparser.hpp"
#include "sqllexer.h"
#include "sqlaction.h"
#include "../databasehandler/database.h"
#include "../layer/databasemanager.h"
#include "../queryhandler/queryexecuter.h"

class SQLDriver {

    // Define the top-level manager name.
    const static std::string systemName;

    int lastAffectedRows;
    bool lastSucceeded;
    bool lastHasResult;
    SQLResult* result;

    yy::SQLLexer*  sqlLexer;
    yy::SQLParser* sqlParser;

    std::vector<std::string> warningMessages;
    std::vector<std::string> errorMessages;

    std::vector<SQLAction*> allActions;

    DatabaseManager* databaseManager;
    Database* currentDatabase;
    QueryExecutor* queryExecuter;

    void clearPreviousSession();

public:

    bool execute(const std::string& sqlStr);

    const std::vector<std::string> &getErrorMessages() const { return errorMessages; }

    const std::vector<std::string> &getWarningMessages() const { return warningMessages; }

    int getLastAffectedRows() const { return lastAffectedRows; }

    bool getLastSucceeded() const { return lastSucceeded; }

    bool hasResult() const { return lastHasResult; }

    void addWarningMessage(const std::string& warnMsg)
    { warningMessages.push_back(warnMsg); }

    void addErrorMessage(const std::string& errMsg)
    { errorMessages.push_back(errMsg); }

    void addAction(SQLAction* const action)
    { allActions.push_back(action); }

    void setCurrentDatabase(Database* db) { currentDatabase = db; }
    Database* getCurrentDatabase() const { return currentDatabase; }
    DatabaseManager* getDatabaseManager() const { return databaseManager; }

    QueryExecutor* getQueryExecuter() const { return queryExecuter; }

    void setResult(SQLResult* r) { if (result) delete result; result = r; lastHasResult = true; }

    SQLResult* getResult() const { return result; }

    SQLDriver();
    ~SQLDriver();

};


#endif //DATABASE_SQLDRIVER_H
