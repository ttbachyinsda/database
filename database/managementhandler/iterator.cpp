#include "iterator.h"

Iterator::Iterator()
{

}

Iterator::~Iterator()
{

}
Iterator& Iterator::operator++()
{
    nextrow();
    return *this;
}
