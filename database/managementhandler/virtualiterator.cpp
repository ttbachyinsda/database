#include "virtualiterator.h"

VirtualIterator::VirtualIterator(Table* table)
{
    this->nowtable = table;
    getbegin();
    this->nowrowsize = getThisRowSize();
}
int VirtualIterator::getThisRowSize()
{
    this->nowrowsize = this->nowtable->getRowSize(this->nowrownum);
    return this->nowrowsize;
}
bool VirtualIterator::access(int pagenum, int rownum)
{
    this->nowpagenum = pagenum;
    this->nowrownum = rownum;
    this->nowpagerownum = this->nowtable->getPageRowNum(pagenum);
    if (this->nowrownum < this->nowpagerownum)
        return true;
    else
        return false;
}
bool VirtualIterator::available()
{
    getThisRowSize();
    char* temp = (char*)malloc(this->nowrowsize);
    int tempsize;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum, temp, tempsize);
    if (temp != NULL)
        free(temp);
    if (tempsize == 0)
        return false;
    else
        return true;
}
bool VirtualIterator::nextrow()
{
    this->nowrownum++;
    bool can = available();
    if (!can)
        while (this->nowrownum < this->nowtable->getPageRowNum(0)) {
            this->nowrownum++;
            if (available()) {
                can = true;
                break;
            }
        }
    return can;
}

bool VirtualIterator::getdata(char* output, int& outputsize)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum, output, outputsize);
    return true;
}
bool VirtualIterator::getdata(Record* rec)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowrownum, rec);
    return true;
}
bool VirtualIterator::insertdata(Record* rec)
{
    int temppagenum, temprownum;
    bool can = this->nowtable->FastAllInsert(temppagenum, temprownum, rec);
    if (can) {
        this->nowpagenum = temppagenum;
        this->nowrownum = temprownum;
        return true;
    } else
        return false;
}
bool VirtualIterator::deletedata()
{
    if (!available())
        return false;
    this->nowtable->DeleteAt(this->nowpagenum, this->nowrownum);
    return true;
}
void VirtualIterator::getbegin()
{
    this->nowrownum = 0;
    this->nowpagenum = 0;
    if (!available())
        nextrow();
}
int VirtualIterator::getcurrentsize()
{
    return getThisRowSize();
}
void VirtualIterator::updaterownum()
{
    this->nowpagerownum = this->nowtable->getPageRowNum(0);
}
