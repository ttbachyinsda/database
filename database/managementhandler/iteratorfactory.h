#ifndef ITERATORFACTORY_H
#define ITERATORFACTORY_H

#include "iterator.h"
#include "fixedsizediterator.h"
class IteratorFactory
{
public:
    IteratorFactory();
    static Iterator* getiterator(Table* table);
};

#endif // ITERATORFACTORY_H
