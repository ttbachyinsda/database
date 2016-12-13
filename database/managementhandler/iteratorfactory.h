#ifndef ITERATORFACTORY_H
#define ITERATORFACTORY_H

#include "fixedsizediterator.h"
#include "flexibleiterator.h"
#include "virtualiterator.h"
#include "iterator.h"
class IteratorFactory {
public:
    IteratorFactory();
    static Iterator* getiterator(Table* table);
};

#endif // ITERATORFACTORY_H
