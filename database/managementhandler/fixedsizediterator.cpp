#include "fixedsizediterator.h"

FixedSizedIterator::FixedSizedIterator(Table* table)
{
    this->nowtable = table;
    getbegin();
    this->nowrowsize = getRowSize();
}
int FixedSizedIterator::getRowSize()
{
    BufPageManager* BPM = this->nowtable->getBPM();
    int fileid = this->nowtable->getfileid();
    int index = 0;
    BufType b = BPM->getPage(fileid, 0, index);
    return UIC::chartoint(b + 4);
}
bool FixedSizedIterator::access(int pagenum, int rownum)
{
    this->nowpagenum = pagenum;
    this->nowpagerownum = this->nowtable->getPageRowNum(pagenum);
    if (rownum >= nowpagerownum) {
        this->nowrownum = 0;
        this->nowpageposition = 8;
        return false;
    }
    this->nowrownum = rownum;
    this->nowpageposition = 8 + this->nowrowsize * rownum;
    return true;
}
bool FixedSizedIterator::available()
{
    if (this->nowpagenum > this->nowtable->getPageNum()) return false;
    if (this->nowrownum >= this->nowpagerownum)
        return false;
    else
        return true;
}
bool FixedSizedIterator::nextrow()
{
    this->nowrownum++;
    this->nowpageposition += nowrowsize;
    if (nowrownum >= nowpagerownum) {
        this->nowpagenum++;
        this->nowrownum = 0;
        this->nowpagerownum = this->nowtable->getPageRowNum(nowpagenum);
        if (nowrownum >= nowpagerownum)
            return false;
        else
            return true;
    } else
        return true;
}

bool FixedSizedIterator::modify(Record* rec)
{
    if (!available())
        return false;
    bool can = this->nowtable->FastModify(this->nowpagenum, this->nowpageposition, rec);
    return can;
}
bool FixedSizedIterator::getdata(char* output, int& outputsize)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowpageposition, output, outputsize);
    return true;
}
bool FixedSizedIterator::getdata(Record* rec)
{
    if (!available())
        return false;
    this->nowtable->FastOutput(this->nowpagenum, this->nowpageposition,rec);
    return true;
}
bool FixedSizedIterator::insertdata(Record* rec)
{
    int temppagenum, temppageposition;
    bool can = this->nowtable->FastAllInsert(temppagenum, temppageposition, rec);
    if (can) {
        nowpagenum=temppagenum;
        nowpageposition = temppageposition;
        nowrownum = (nowpageposition - 8) / nowrowsize;
        this->nowpagerownum = this->nowtable->getPageRowNum(nowpagenum);
        return true;
    } else
        return false;
}
bool FixedSizedIterator::deletedata()
{
    if (!available())
        return false;
    this->nowtable->DeleteAt(this->nowpagenum, this->nowrownum);
    return true;
}
void FixedSizedIterator::getbegin()
{
    int maxpagenum = this->nowtable->getPageNum();
    nowrownum = 0;
    nowpagenum = 1;
    nowpageposition = 8;
    while (nowpagenum <= maxpagenum) {
        nowpagerownum = this->nowtable->getPageRowNum(nowpagenum);
        if (nowpagerownum != 0)
            break;
        nowpagenum++;
    }
}
int FixedSizedIterator::getcurrentsize()
{
    return nowrowsize;
}
