#ifndef FLEXIBLEITERATOR_H
#define FLEXIBLEITERATOR_H

#include "../databasehandler/flexibletable.h"
#include "../recordhandler/flexiblerecord.h"
#include "iterator.h"
class FlexibleIterator : public Iterator {
public:
    FlexibleIterator(Table* table);
    bool nextrow();
    bool access(int pagenum, int rownum);
    bool getdata(char* output, int& outputsize);
    bool getdata(Record* rec);
    bool deletedata();
    bool insertdata(Record* rec);
    bool available();
    void getbegin();
    int getcurrentsize();

private:
    int getThisRowSize();
    void updaterownum();
    int fileid;
    BufPageManager* BPM;
};

#endif // FLEXIBLEITERATOR_H
