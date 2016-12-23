#ifndef ITERATOR_H
#define ITERATOR_H

#include "../databasehandler/table.h"
#include "../recordhandler/record.h"
#include "uic.h"
class Iterator {
public:
    Iterator();
    virtual bool nextrow() = 0;
    virtual ~Iterator();
    virtual bool access(int pagenum, int rownum) = 0;
    Iterator& operator++();
    virtual bool getdata(char* output, int& outputsize) = 0;
    virtual int getcurrentsize() = 0;
    virtual bool getdata(Record* rec) = 0;
    virtual bool available() = 0;
    virtual bool deletedata() = 0;
    virtual bool insertdata(Record* rec) = 0;
    virtual void getbegin() = 0;
    virtual int gethashnum()
    {
        return 0;
    }

    bool find(string input, int columnnum);
    string compile(string input, int columnnum);
    int getpagenum()
    {
        return this->nowpagenum;
    }
    int getrownum()
    {
        return this->nowrownum;
    }
    int getpagerownum()
    {
        return this->nowpagerownum;
    }

protected:
    int nowpagenum;
    int nowrownum;
    int nowrowsize;
    int nowpagerownum;
    Table* nowtable;
};

#endif // ITERATOR_H
