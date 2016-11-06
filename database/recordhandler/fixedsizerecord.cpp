#include "fixedsizerecord.h"

FixedSizeRecord::FixedSizeRecord()
{
}
/* will pass inidata to this record*/
/* can only Initialize once */
void FixedSizeRecord::Initialize(DataBaseType** inidata, int datasize)
{
    this->columns = inidata;
    this->columncount = datasize;
    this->columnsize = new int[datasize];
    memset(this->columnsize, 0, 4 * datasize);
    this->size = 0;
    for (int i = 0; i < datasize; i++) {
        this->size += inidata[i]->getSize();
        this->columnsize[i] = this->size;
    }
    this->data = new char[this->size];
    cout << "initial" << this->size << endl;
}
void FixedSizeRecord::Input(char* input)
{
    for (int i = 0; i < this->columncount; i++) {
        int position = ((i == 0) ? 0 : columnsize[i - 1]);
        //int nowsize = ((i == 0) ? columnsize[0] : columnsize[i] - columnsize[i - 1]);
        int index = 0;
        columns[i]->read(input + position,columns[i]->getSize(), index);
    }
    memcpy(this->data, input, this->size);
}
bool FixedSizeRecord::getAt(int num, char* returndata, int& returndatasize)
{
    if (num >= this->columncount)
        return false;
    int position = ((num == 0) ? 0 : columnsize[num - 1]);
    int nowsize = ((num == 0) ? columnsize[0] : columnsize[num] - columnsize[num - 1]);
    memcpy(returndata, this->data + position, nowsize);
    returndatasize = nowsize;
    return true;
}
string FixedSizeRecord::getAt(int num)
{
    if (num >= this->columncount)
        return "";
    return columns[num]->output();
}
bool FixedSizeRecord::set(string* input)
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
bool FixedSizeRecord::set(char** input, int* inputlen)
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
bool FixedSizeRecord::setAt(int wz,string input,bool isnull)
{
    if (wz>=this->columncount) return false;
    bool can=columns[wz]->checkRight(input,isnull);
    if (!can)
        return false;
    columns[wz]->checkRightAndChange(input,isnull);
    return true;
}

void FixedSizeRecord::update()
{
    for (int i = 0; i < this->columncount; i++) {
        int position = ((i == 0) ? 0 : columnsize[i - 1]);
        int nowsize = ((i == 0) ? columnsize[0] : columnsize[i] - columnsize[i - 1]);
        memcpy(this->data + position, columns[i]->getdata(), nowsize);
    }
}
