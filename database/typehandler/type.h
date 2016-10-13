#ifndef TYPE_H
#define TYPE_H
#include <iostream>
#include <bitset>
using namespace std;
class type
{
public:
    type();
    char* getdata();
    void printdata(string testinfo);
    virtual bool checkRight(string input)=0;
    virtual bool checkRightAndChange(string input)=0;
    virtual bool checkRight(char* input,int size)=0;
    virtual bool checkRightAndChange(char* input,int size)=0;
    virtual int getSize()=0;
    virtual string getType()=0;
    virtual ~type();
    virtual string output()=0;
protected:
    int size;
    char* data;
};

#endif // TYPE_H
