#ifndef VIRTUALITERATOR_H
#define VIRTUALITERATOR_H

#include "iterator.h"
#include "../databasehandler/virtualtable.h"
#include "../recordhandler/flexiblerecord.h"

class VirtualIterator : public Iterator
{
public:
    VirtualIterator(Table *table);
    bool nextrow();
    bool access(int pagenum, int rownum);
    bool getdata(char* output, int& outputsize);
    bool getdata(Record *rec);
    bool deletedata();
    bool insertdata(Record* rec);
    bool available();
    void getbegin();
    int getcurrentsize();

private:
    int getThisRowSize();
    void updaterownum();
};

#endif // VIRTUALITERATOR_H
