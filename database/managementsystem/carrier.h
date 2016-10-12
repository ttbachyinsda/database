#ifndef CARRIER_H
#define CARRIER_H

#include <cstring>
#include <string>
using namespace std;
class carrier
{
public:
    carrier();
    carrier(char* data,int length);
    carrier(int length);
    int getsize();
    unsigned int* getdata();
    char* getconvertresult();
    char* GCR();
    void beginconvert();
    ~carrier();
private:
    unsigned int* data=0;
    char* convertresult=0;
    int size;
};

#endif // CARRIER_H
