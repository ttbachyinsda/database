#ifndef RECORDFACTORY_H
#define RECORDFACTORY_H

#include "databasehandler/fixedsizetable.h"
#include "databasehandler/table.h"
#include "recordhandler/fixedsizerecord.h"
#include "recordhandler/record.h"
class RecordFactory {
public:
    RecordFactory();
    static Record* getrecord(Table* table);
};

#endif // RECORDFACTORY_H
