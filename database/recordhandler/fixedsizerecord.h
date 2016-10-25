#ifndef FIXEDSIZERECORD_H
#define FIXEDSIZERECORD_H

#include "record.h"
class FixedSizeRecord : public Record {
public:
    FixedSizeRecord();
    void Initialize(DataBaseType** inidata, int datasize);
    void Input(char* input);
    bool getAt(int num, char* returndata, int& returndatasize);
    string getAt(int num);
    bool set(string* input);
    bool set(char** input,int*inputlen);
    void update();
};

#endif // FIXEDSIZERECORD_H
