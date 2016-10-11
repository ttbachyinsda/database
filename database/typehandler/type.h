#ifndef TYPE_H
#define TYPE_H

#include <bitset>
using namespace std;
class type
{
public:
    type();
    unsigned int* convertToBufType();
    virtual bool checkRight(string input)=0;
    virtual bool checkRightAndChange(string input)=0;
    virtual int getSize()=0;
    virtual string getType()=0;
protected:
    int size;
    char* data;
};

#endif // TYPE_H
