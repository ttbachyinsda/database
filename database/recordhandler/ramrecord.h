//
// Created by jameshuang on 16-12-10.
//

#ifndef DATABASE_RAMRECORD_H
#define DATABASE_RAMRECORD_H


#include "record.h"

class RamRecord : public Record {
public:
    virtual void Initialize(DataBaseType **inidata, int datasize);

    virtual void Input(char *input);

    virtual bool getAt(int num, char *returndata, int &returndatasize);

    virtual string getAt(int num);

    virtual bool set(string *input);

    virtual bool set(char **input, int *inputlen);

    virtual bool setAt(int wz, string input, bool isnull);

    virtual void update();

    virtual int getMaxSize();
};


#endif //DATABASE_RAMRECORD_H
