#include "record.h"

Record::Record()
{
    this->data=NULL;
    this->columncount=0;
    this->columns=NULL;
    this->columnsize=NULL;
    this->size=0;
}
char* Record::getData()
{
    return this->data;
}
int Record::getSize()
{
    return this->size;
}
Record::~Record()
{
    if (this->data!=NULL) delete[] this->data;
    if (this->columnsize!=NULL) delete[] this->columnsize;
    if (this->columns!=NULL)
    {
        for (int i=0;i<columncount;i++)
            if (columns[i]!=NULL)
                delete columns[i];
        delete[] columns;
    }
    columncount=0;
    size=0;
}
