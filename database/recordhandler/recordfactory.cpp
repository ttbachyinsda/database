#include "recordfactory.h"

RecordFactory::RecordFactory()
{
}
Record* RecordFactory::getrecord(Table* table)
{
    string tabletype = table->gettabletype();
    if (tabletype[0] == 'F' && tabletype[1]=='i') {
        Record* temp = new FixedSizeRecord();
        DataBaseType** col = UIC::copytype(table->getcolumns(), table->getcolumncount());
        temp->Initialize(col, table->getcolumncount());
        return temp;
    } else if (tabletype[0] == 'F' && tabletype[1]=='l') {
        Record* temp = new FlexibleRecord();
        DataBaseType** col = UIC::copytype(table->getcolumns(), table->getcolumncount());
        temp->Initialize(col, table->getcolumncount());
        return temp;
    }
    return NULL;
}
