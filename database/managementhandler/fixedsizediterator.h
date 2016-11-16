#ifndef FIXEDSIZEDITERATOR_H
#define FIXEDSIZEDITERATOR_H

#include "iterator.h"
#include "../recordhandler/fixedsizerecord.h"
class FixedSizedIterator : public Iterator {
public:
    FixedSizedIterator(Table* table);
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
    int getRowSize();
    int fileid;
    BufPageManager* BPM;
};

#endif // FIXEDSIZEDITERATOR_H
