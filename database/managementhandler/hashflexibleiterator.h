#ifndef HASHFLEXIBLEITERATOR_H
#define HASHFLEXIBLEITERATOR_H

#include "../databasehandler/flexibletable.h"
#include "../recordhandler/flexiblerecord.h"
#include "iterator.h"

class HashFlexibleIterator : public Iterator {
public:
    HashFlexibleIterator(Table* table);
    bool nextrow();
    bool access(int pagenum, int rownum);
    bool getdata(char* output, int& outputsize);
    bool getdata(Record* rec);
    bool deletedata();
    bool insertdata(Record* rec);
    bool available();
    void getbegin();
    int getcurrentsize();
    int gethashnum();

private:
    int nowhashnum;
    int jumppagenum;
};

#endif // HASHFLEXIBLEITERATOR_H
