#include "fixedsizerecord.h"

FixedSizeRecord::FixedSizeRecord()
{

}
/* will pass inidata to this record*/
/* can only Initialize once */
void FixedSizeRecord::Initialize(DataBaseType **inidata, int datasize)
{
    this->columns=inidata;
    this->columncount=datasize;
    this->columnsize=new int[datasize];
    memset(this->columnsize,0,4*datasize);
    this->size=0;
    for (int i=0;i<datasize;i++)
    {
        this->size += inidata[i]->getSize();
        this->columnsize[i] = this->size;
    }
    this->data=new char[this->size];
}
void FixedSizeRecord::Input(char *input)
{
    for (int i=0;i<this->columncount;i++)
    {
        int position=((i==0)?0:columnsize[i-1]);
        int nowsize=((i==0)?columnsize[0]:columnsize[i]-columnsize[i-1]);
        columns[i]->checkRightAndChange(input+position,nowsize);
    }
    memcpy(this->data,input,this->size);
}
bool FixedSizeRecord::getAt(int num, char *returndata, int &returndatasize)
{
    if (num>=this->columncount) return false;
    int position=((num==0)?0:columnsize[num-1]);
    int nowsize=((num==0)?columnsize[0]:columnsize[num]-columnsize[num-1]);
    memcpy(returndata,this->data+position,nowsize);
    returndatasize = nowsize;
    return true;
}
string FixedSizeRecord::getAt(int num)
{
    if (num>=this->columncount) return "";
    int position=((num==0)?0:columnsize[num-1]);
    int nowsize=((num==0)?columnsize[0]:columnsize[num]-columnsize[num-1]);
    string temp(this->data+position,nowsize);
    return temp;
}
bool FixedSizeRecord::set(string* input)
{
    for (int i=0;i<this->columncount;i++)
    {
        int position=((i==0)?0:columnsize[i-1]);
        int nowsize=((i==0)?columnsize[0]:columnsize[i]-columnsize[i-1]);
        int datalength=input[i].length();
        if (datalength<nowsize)
        {
            memcpy(this->data+position,input[i].data(),datalength);
            memset(this->data+position+datalength,0,nowsize-datalength);
        }
        else
            memcpy(this->data+position,input[i].data(),nowsize);
        columns[i]->checkRightAndChange(input[i]);
    }
    return true;
}
bool FixedSizeRecord::set(char** input)
{
    for (int i=0;i<this->columncount;i++)
    {
        int position=((i==0)?0:columnsize[i-1]);
        int nowsize=((i==0)?columnsize[0]:columnsize[i]-columnsize[i-1]);
        memcpy(this->data+position,input[i],nowsize);
        columns[i]->checkRightAndChange(input[i],nowsize);
    }
    return true;
}
