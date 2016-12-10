//
// Created by jameshuang on 16-12-10.
//

#include "joinstrategy.h"
#include "../../recordhandler/recordfactory.h"
#include "../../managementhandler/iteratorfactory.h"
#include "../../databasehandler/ramtable.h"
#include "../querycondition.h"

void JoinStrategy::setCondition(int did, int pid, SQLOperand op) {
    this->driverTableConditionColumnID = did;
    this->passengerTableConditionColumnID = pid;
    this->operand = op;
}

void JoinStrategy::prepareTable(Table *dTable, Table *pTable) {
    this->driverTable = dTable;
    this->passengerTable = pTable;

    resultTable = new RamTable();
    resultTable->setname(this->getType() + "_JOIN_TEMP");

    // Create Target Table.
    // Every field is written because these fields may be used later.
    vector<string> clname;
    vector<DataBaseType*> cltype;

    for (int i = 0; i < driverTable->getcolumncount(); ++ i) {
        clname.push_back(driverTable->getname() + "." + driverTable->getcolumnname(i));
        cltype.push_back(copyType(driverTable->getcolumn(i)));
    }

    for (int i = 0; i < passengerTable->getcolumncount(); ++ i) {
        clname.push_back(passengerTable->getname() + "." + passengerTable->getcolumnname(i));
        cltype.push_back(copyType(passengerTable->getcolumn(i)));
    }

    resultTable->createTable(clname, cltype);
    resultTable->Initialize();

    // Iterate over driver table. use index in inner conditions.
    driverIterator = IteratorFactory::getiterator(driverTable);
    driverRecord = RecordFactory::getrecord(driverTable);

    passengerIterator = IteratorFactory::getiterator(passengerTable);
    passengerRecord = RecordFactory::getrecord(passengerTable);

    resultRecord = RecordFactory::getrecord(resultTable);
}

DataBaseType *JoinStrategy::copyType(DataBaseType *oriType) {
    string type = oriType->getType();
    int size = oriType->getSize();
    bool canNull = oriType->getNullable();
    return UIC::reconvert(type, size, canNull);
}

JoinStrategy::JoinStrategy() {
    driverTable = 0;
    passengerTable = 0;
    resultTable = 0;

    driverIterator = 0;
    driverRecord = 0;

    passengerIterator = 0;
    passengerRecord = 0;

    resultRecord = 0;
}

JoinStrategy::~JoinStrategy() {
    if (driverIterator) delete driverIterator;
    if (driverRecord) delete driverRecord;

    if (passengerIterator) delete passengerIterator;
    if (passengerRecord) delete passengerRecord;

    if (resultRecord) delete resultRecord;
}

void JoinStrategy::addToResultIfMatch() {
    char cmpType = driverRecord->getcolumns()[driverTableConditionColumnID]->getType()[6];

    std::string driverValue = driverRecord->getAt(driverTableConditionColumnID);
    bool driverValueIsNull = driverRecord->getIsNull(driverTableConditionColumnID);

    std::string passengerValue = passengerRecord->getAt(passengerTableConditionColumnID);
    bool passengerValueIsNull = passengerRecord->getIsNull(passengerTableConditionColumnID);

    bool matchResult = QueryCondition::match(this->operand, cmpType, driverValue, driverValueIsNull,
                                             passengerValue, passengerValueIsNull);

    if (matchResult) {
        for (int i = 0; i < driverRecord->getcolumncount(); ++ i) {
            resultRecord->setAt(i, driverRecord->getAt(i), driverRecord->getIsNull(i));
        }
        int base = driverRecord->getcolumncount();
        for (int j = 0; j < passengerRecord->getcolumncount(); ++ j) {
            resultRecord->setAt(base + j, passengerRecord->getAt(j), passengerRecord->getIsNull(j));
        }
        resultRecord->update();
        int dum;
        resultTable->FastAllInsert(dum, dum, resultRecord);
    }

}
