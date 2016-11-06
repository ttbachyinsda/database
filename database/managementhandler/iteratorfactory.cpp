#include "iteratorfactory.h"

IteratorFactory::IteratorFactory()
{
}
Iterator* IteratorFactory::getiterator(Table* table)
{
    string tabletype = table->gettabletype();
    if (tabletype[0] == 'F' && tabletype[1] == 'i') {
        Iterator* temp = new FixedSizedIterator(table);
        return temp;
    } else if (tabletype[0] == 'F' && tabletype[1] == 'l') {
        Iterator* temp = new FlexibleIterator(table);
        return temp;
    }
    return NULL;
}
