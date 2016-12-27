//
// Created by jameshuang on 16-10-19.
//

#include <sstream>
#include <iostream>
#include <unistd.h>
#include "sqldriver.h"

const std::string SQLDriver::systemName = "top";

SQLDriver::SQLDriver() {
//    initialize();
}

SQLDriver::~SQLDriver() {
    clearPreviousSession();
    // current database will be deleted by the manager
    if (databaseManager) delete databaseManager;
    delete queryExecuter;
}

/**
 * Execute a SQL command and returns whether it succeeded.
 * @param sqlStr
 * @return success or not
 */
bool SQLDriver::execute(const std::string& sqlStr) {
    clearPreviousSession();

    std::istringstream* sstream = new std::istringstream(sqlStr);
    sqlLexer = new yy::SQLLexer(sstream, this);
    sqlParser = new yy::SQLParser(*sqlLexer, *this);

    lastSucceeded = (sqlParser->parse() == 0);

    if (!lastSucceeded) return false;

    delete sstream;

    for (SQLAction* it : allActions) {
        it->setDriver(this);
        // Execute everthing before error prompt.
        lastSucceeded = it->execute();
        if (!lastSucceeded) return false;
    }

    return lastSucceeded;
}

void SQLDriver::clearPreviousSession() {
    if (sqlLexer)  delete sqlLexer;
    if (sqlParser) delete sqlParser;
    if (result) delete result;
    result = 0;
    sqlLexer = 0;
    sqlParser = 0;
    warningMessages.clear();
    errorMessages.clear();
    for (std::vector<SQLAction*>::iterator it = allActions.begin();
         it != allActions.end(); ++ it) {
        delete (*it);
    }
    allActions.clear();
    lastAffectedRows = 0;
    lastHasResult = false;
}

void SQLDriver::initialize()
{
    sqlLexer  = 0;
    sqlParser = 0;
    lastSucceeded = false;
    lastHasResult = false;
    lastAffectedRows = 0;
    currentDatabase = 0;
    result = 0;

    // May consider lazy init.
    databaseManager = new DatabaseManager();
    databaseManager->setname(SQLDriver::systemName);
    databaseManager->setfilename(SQLDriver::systemName + ".tdb");
    // If file not exist, new file will be created.
    databaseManager->Initialize();

    queryExecuter = new QueryExecutor(this);
}

SQLDriver::SQLDriver(const string &workingDir) {
    int chdirRes = chdir(workingDir.c_str());
    if (chdirRes == -1) {
        cout << "Fatal: " << workingDir << " : Permission denined." << endl;
        exit(0);
    }
    initialize();
}

void SQLDriver::setWorkingDir(const std::string &workingDir) {
    clearPreviousSession();
    // current database will be deleted by the manager
    if (databaseManager) delete databaseManager;
    delete queryExecuter;
    int chdirRes = chdir(workingDir.c_str());
    if (chdirRes == -1) {
        cout << "Fatal: " << workingDir << " : Permission denined." << endl;
        exit(0);
    }
    initialize();
}
