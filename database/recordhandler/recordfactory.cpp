#include "recordfactory.h"

RecordFactory::RecordFactory()
{
}
Record* RecordFactory::getrecord(Table* table)
{
    string tabletype = table->gettabletype();
    if (tabletype[0] == 'F') {
        Record* temp = new FixedSizeRecord();
        DataBaseType** col = UIC::copytype(table->getcolumns(), table->getcolumncount());
        temp->Initialize(col, table->getcolumncount());
        return temp;
    }
    return NULL;
}
