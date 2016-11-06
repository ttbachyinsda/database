#include "flexiblerecord.h"

FlexibleRecord::FlexibleRecord()
{

}
void FlexibleRecord::Initialize(DataBaseType** inidata, int datasize)
{
    this->columns = inidata;
    this->columncount = datasize;
    this->columnsize = NULL;
    this->data = NULL;
    cout << "initial" << this->size << endl;
}
void FlexibleRecord::Input(char* input)
{
    this->size = UIC::chartoint(input);
    if (this->data!=NULL) delete[] this->data;
    this->data = new char[this->size];
    int index=4;
    for (int i = 0; i < this->columncount; i++) {
        int inputlen=UIC::chartoint(input+index);
        index += 4;
        columns[i]->read(input + index, inputlen,index);
    }
    memcpy(this->data, input, this->size);
}
bool FlexibleRecord::getAt(int num, char* returndata, int& returndatasize)
{
    if (num >= this->columncount)
        return false;
    string temp=columns[num]->output();
    returndatasize=temp.length();
    memcpy(returndata,temp.data(),returndatasize);
    return true;
}
string FlexibleRecord::getAt(int num)
{
    if (num >= this->columncount)
        return "";
    return columns[num]->output();
}
bool FlexibleRecord::set(string* input)
{
    for (int i = 0; i < this->columncount; i++) {
        bool can = columns[i]->checkRight(input[i]);
        if (!can)
            return false;
    }
    for (int i = 0; i < this->columncount; i++) {
        columns[i]->checkRightAndChange(input[i]);
    }
    update();
    return true;
}
bool FlexibleRecord::set(char** input, int* inputlen)
{
    for (int i = 0; i < this->columncount; i++) {
        bool can = columns[i]->checkRightc(input[i], inputlen[i]);
        if (!can)
            return false;
    }
    for (int i = 0; i < this->columncount; i++) {
        columns[i]->checkRightAndChangec(input[i], inputlen[i]);
    }
    update();
    return true;
}
bool FlexibleRecord::setAt(int wz,string input,bool isnull)
{
    if (wz>=this->columncount) return false;
    bool can=columns[wz]->checkRight(input,isnull);
    if (!can)
        return false;
    columns[wz]->checkRightAndChange(input,isnull);
    return true;
}

void FlexibleRecord::update()
{
    int index=4; int totallen=4;
    for (int i = 0; i < this->columncount; i++) {
        totallen += 4+columns[i]->getSize();
    }
    this->size=totallen;
    if (this->data!=NULL) delete[] this->data;
    this->data = new char[this->size];
    UIC::inttochar(totallen,this->data);
    for (int i=0;i<this->columncount;i++)
    {
        int nowsize=columns[i]->getSize();
        UIC::inttochar(nowsize,this->data+index);
        index += 4;
        memcpy(this->data+index,columns[i]->getdata(),nowsize);
        index += nowsize;
    }
    if (index!=totallen) cout<<"ERROR LEN"<<endl;
}
int FlexibleRecord::getMaxSize()
{
    int totallen=4;
    for (int i = 0; i < this->columncount; i++) {
        totallen += 4+columns[i]->getMaxSize();
    }
    return totallen;
}
