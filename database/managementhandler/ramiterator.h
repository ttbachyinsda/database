//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_RAMITERATOR_H
#define DATABASE_RAMITERATOR_H


#include "iterator.h"

class RamIterator : public Iterator{
public:
    virtual bool nextrow();

    virtual bool access(int pagenum, int rownum);

    virtual bool getdata(char *output, int &outputsize);

    virtual int getcurrentsize();

    virtual bool getdata(Record *rec);

    virtual bool available();

    virtual bool deletedata();

    virtual bool insertdata(Record *rec);

    virtual void getbegin();
};


#endif //DATABASE_RAMITERATOR_H
