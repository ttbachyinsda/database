#ifndef RECORD_H
#define RECORD_H

#include "typehandler/databasetype.h"
#include <cstring>
#include <cstdlib>
class Record
{
public:
    Record();
    virtual void Initialize(DataBaseType **inidata,int datasize)=0;
    virtual void Input(char* input)=0;
    virtual bool getAt(int num,char *returndata,int &returndatasize)=0;
    virtual string getAt(int num)=0;
    virtual bool set(string* input)=0;
    virtual bool set(char** input)=0;
    char* getData();
    int getSize();
    virtual ~Record();
protected:
    char* data;
    int size;
    DataBaseType** columns;
    int columncount;
    int* columnsize;
};

#endif // RECORD_H
