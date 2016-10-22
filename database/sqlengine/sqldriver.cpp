//
// Created by jameshuang on 16-10-19.
//

#include <sstream>
#include <iostream>
#include "sqldriver.h"

SQLDriver::SQLDriver() {
    sqlLexer  = 0;
    sqlParser = 0;
    lastSucceeded = false;
    lastAffectedRows = 0;
}

SQLDriver::~SQLDriver() {
    clearPreviousSession();
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
        // Execute everthing before error prompt.
        lastSucceeded = it->execute();
        if (!lastSucceeded) return false;
    }

    return lastSucceeded;
}

void SQLDriver::clearPreviousSession() {
    if (sqlLexer)  delete sqlLexer;
    if (sqlParser) delete sqlParser;
    warningMessages.clear();
    errorMessages.clear();
    for (std::vector<SQLAction*>::iterator it = allActions.begin();
         it != allActions.end(); ++ it) {
        delete (*it);
    }
    allActions.clear();
    lastAffectedRows = 0;
}

