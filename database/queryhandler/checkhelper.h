//
// Created by jameshuang on 16-12-23.
//

#ifndef DATABASE_CHECKHELPER_H
#define DATABASE_CHECKHELPER_H


#include "../databasehandler/table.h"

class CheckHelper {
public:
    // should be different from any other SQLOperands.
    static const int choiceCode;
    static bool addCheckCondition(const vector<string>& clname,
                                  const vector<DataBaseType*>& ctypes,
                                  Table* tbl,
                                  SQLCheckGroup* checkGroup);
    static bool satisfy(Table* tbl, SQLValueGroup* const,
                        const vector<vector<string> >& choiceListCache);
};


#endif //DATABASE_CHECKHELPER_H
