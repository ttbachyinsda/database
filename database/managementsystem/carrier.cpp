#include "carrier.h"

carrier::carrier()
{
    size=0;
    data=NULL;
    convertresult=NULL;
}
carrier::~carrier()
{
    if (data!=NULL) delete data;
    if (convertresult!=NULL) delete convertresult;
}

int carrier::getsize()
{
    return size;
}
unsigned int* carrier::getdata()
{
    return data;
}

carrier::carrier(char *data, int length)
{
    this->data = new unsigned int[(length+1)>>1];
    this->size = length;
    strncpy((char*)this->data,data,length);
}
carrier::carrier(int length)
{
    this->data = new unsigned int[(length+1)>>1];
}

void carrier::beginconvert()
{
    if (convertresult!=NULL) delete convertresult;
    convertresult = new char[size];
    strncpy(convertresult,(char*)this->data,size);
}
char* carrier::getconvertresult()
{
    return convertresult;
}
char* carrier::GCR()
{
    return convertresult;
}
