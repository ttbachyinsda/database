#ifndef ITERATOR_H
#define ITERATOR_H

#include "databasehandler/table.h"
#include "uic.h"
#include "recordhandler/record.h"
class Iterator
{
public:
    Iterator();
    virtual bool nextrow()=0;
    virtual ~Iterator();
    virtual bool access(int pagenum,int rownum)=0;
    Iterator& operator++();
    virtual bool getdata(char* output,int& outputsize)=0;
    virtual int getcurrentsize()=0;
    virtual Record* getdata()=0;
    virtual bool available()=0;
    virtual bool modify(Record* rec)=0;
    virtual bool deletedata()=0;
    virtual bool insertdata(Record* rec)=0;
    virtual void getbegin()=0;
protected:
    int nowpagenum;
    int nowrownum;
    int nowpageposition;
    int nowrowsize;
    int nowpagerownum;
    Table* nowtable;
};

#endif // ITERATOR_H
