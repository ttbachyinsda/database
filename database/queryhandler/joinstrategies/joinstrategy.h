//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_JOINSTRATEGY_H
#define DATABASE_JOINSTRATEGY_H

#include "../../databasehandler/table.h"
#include "../../sqlengine/sqlstruct.h"
#include "../../managementhandler/iterator.h"

// Notice: In this database only inner join is implemented.
// Result Table should be deleted inside
class JoinStrategy {
protected:
    int driverTableConditionColumnID;
    int passengerTableConditionColumnID;
    SQLOperand operand;

    Table* driverTable;
    Table* passengerTable;
    Table* resultTable;

    Iterator* driverIterator;
    Record* driverRecord;

    Iterator* passengerIterator;
    Record* passengerRecord;

    Record* resultRecord;

    DataBaseType* copyType(DataBaseType* oriType);
    void addToResultIfMatch();
public:
    JoinStrategy();
    virtual ~JoinStrategy();
    void setCondition(int did, int pid, SQLOperand op);
    void prepareTable(Table* dTable, Table* pTable);
    virtual Table* join() = 0;
    virtual std::string getType() = 0;
};


#endif //DATABASE_JOINSTRATEGY_H
