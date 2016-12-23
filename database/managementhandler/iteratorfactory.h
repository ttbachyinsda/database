#ifndef ITERATORFACTORY_H
#define ITERATORFACTORY_H

#include "fixedsizediterator.h"
#include "flexibleiterator.h"
#include "hashflexibleiterator.h"
#include "iterator.h"
#include "virtualiterator.h"
class IteratorFactory {
public:
    IteratorFactory();
    static Iterator* getiterator(Table* table);
};

#endif // ITERATORFACTORY_H
