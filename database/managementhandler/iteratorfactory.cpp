#include "iteratorfactory.h"

IteratorFactory::IteratorFactory()
{
}
Iterator* IteratorFactory::getiterator(Table* table)
{
    string tabletype = table->gettabletype();
    if (tabletype[0] == 'F') {
        Iterator* temp = new FixedSizedIterator(table);
        return temp;
    }
    return NULL;
}
