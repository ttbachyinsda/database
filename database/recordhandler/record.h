#ifndef RECORD_H
#define RECORD_H

#include "../typehandler/databasetype.h"
#include <cstdlib>
#include <cstring>
class Record {
public:
    Record();
    virtual void Initialize(DataBaseType** inidata, int datasize) = 0;
    virtual void Input(char* input) = 0;
    virtual bool getAt(int num, char* returndata, int& returndatasize) = 0;
    virtual string getAt(int num) = 0;
    virtual bool getIsNull(int num);
    virtual bool set(string* input) = 0;
    virtual bool set(char** input, int* inputlen) = 0;
    virtual bool setAt(int wz, string input, bool isnull) = 0;
    virtual void update() = 0;
    char* getData();
    int getSize();
    virtual int getMaxSize() = 0;
    DataBaseType** getcolumns();
    int getcolumncount();
    int* getcolumnsize();
    virtual ~Record();

protected:
    char* data;
    int size;
    DataBaseType** columns;
    int columncount;
    int* columnsize;
};

#endif // RECORD_H
