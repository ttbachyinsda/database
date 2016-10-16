#ifndef DATABASETYPE_H
#define DATABASETYPE_H
#include <iostream>
#include <bitset>
using namespace std;
class DataBaseType
{
public:
    DataBaseType();
    char* getdata();
    void printdata(string testinfo);
    virtual bool checkRight(string input)=0;
    virtual bool checkRightAndChange(string input)=0;
    virtual bool checkRight(char* input,int size)=0;
    virtual bool checkRightAndChange(char* input,int size)=0;
    virtual int getSize()=0;
    virtual string getType()=0;
    virtual ~DataBaseType();
    virtual string output()=0;
protected:
    int size;
    char* data;
};

#endif // DATABASETYPE_H
