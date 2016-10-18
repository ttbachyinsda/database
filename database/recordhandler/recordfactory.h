#ifndef RECORDFACTORY_H
#define RECORDFACTORY_H

#include "databasehandler/table.h"
#include "databasehandler/fixedsizetable.h"
#include "recordhandler/record.h"
#include "recordhandler/fixedsizerecord.h"
class RecordFactory
{
public:
    RecordFactory();
    static Record* getrecord(Table* table);
};

#endif // RECORDFACTORY_H
