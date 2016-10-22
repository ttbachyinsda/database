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

class SQLDriver {

    int lastAffectedRows;
    bool lastSucceeded;
    yy::SQLLexer*  sqlLexer;
    yy::SQLParser* sqlParser;

    std::vector<std::string> warningMessages;
    std::vector<std::string> errorMessages;

    std::vector<SQLAction*> allActions;

    void clearPreviousSession();

public:

    bool execute(const std::string& sqlStr);

    const std::vector<std::string> &getErrorMessages() const { return errorMessages; }

    const std::vector<std::string> &getWarningMessages() const { return warningMessages; }

    int getLastAffectedRows() const { return lastAffectedRows; }

    bool getLastSucceeded() const { return lastSucceeded; }

    void addWarningMessage(const std::string& warnMsg)
    { warningMessages.push_back(warnMsg); }

    void addErrorMessage(const std::string& errMsg)
    { errorMessages.push_back(errMsg); }

    void addAction(SQLAction* const action)
    { allActions.push_back(action); }

    SQLDriver();
    ~SQLDriver();

};


#endif //DATABASE_SQLDRIVER_H
