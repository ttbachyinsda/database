#ifndef FLEXIBLERECORD_H
#define FLEXIBLERECORD_H

#include "record.h"
#include "assert.h"
#include "../managementhandler/uic.h"
class FlexibleRecord : public Record
{
public:
    FlexibleRecord();
    void Initialize(DataBaseType** inidata, int datasize);
    void Input(char* input);
    bool getAt(int num, char* returndata, int& returndatasize);
    string getAt(int num);
    bool set(string* input);
    bool set(char** input, int* inputlen);
    bool setAt(int wz,string input,bool isnull);
    void update();
    int getMaxSize();
private:
    int maxsize;
};

#endif // FLEXIBLERECORD_H
